// This code configures on Esp32 to connect to Wi-fi, read RFID tags and send the tag data to a server

#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

// Configurações da sua rede Wi-Fi
const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_SUA_REDE";

// URL da sua API (onde o servidor está rodando)
const char* serverName = "http://seu-servidor.com/api/registrar-passagem";
const String id_sensor = "Sensor_Entrada_Principal";

// Definição dos pinos do RFID
#define SS_PIN 5
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  
  // Inicia o SPI e o Leitor RFID
  SPI.begin();
  rfid.PCD_Init();
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à rede Wi-Fi com sucesso!");
}

void loop() {
  // Verifica se há uma nova tag próxima
  if (!rfid.PICC_IsNewCardPresent()) return;
  
  // Tenta ler o código da tag
  if (!rfid.PICC_ReadCardSerial()) return;

  // Monta a string com o código UID da tag
  String uidDaTag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidDaTag += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidDaTag += String(rfid.uid.uidByte[i], HEX);
  }
  uidDaTag.toUpperCase();
  
  Serial.println("Tag lida: " + uidDaTag);
  
  // Envia os dados para a API
  enviarParaAPI(uidDaTag);
  
  // Pausa o leitor por um momento para não ler a mesma tag 1000 vezes por segundo
  rfid.PICC_HaltA();
  delay(2000); 
}

void enviarParaAPI(String tagID) {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    // Inicia a conexão com a URL
    http.begin(serverName);
    
    // Diz que estamos enviando dados no formato JSON
    http.addHeader("Content-Type", "application/json");
    
    // Monta o pacote JSON com a Tag e o ID do Sensor
    String jsonPayload = "{\"tag_id\":\"" + tagID + "\", \"sensor_id\":\"" + id_sensor + "\"}";
    
    // Envia a requisição via método POST
    int httpResponseCode = http.POST(jsonPayload);
    
    if(httpResponseCode > 0){
      String response = http.getString();
      Serial.println("Código HTTP: " + String(httpResponseCode));
      Serial.println("Resposta do Servidor: " + response);
    } else {
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }
    
    // Libera os recursos
    http.end();
  } else {
    Serial.println("Erro: Wi-Fi desconectado.");
  }
}