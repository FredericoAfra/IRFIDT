#include <MFRC522.h>
#include <SPI.h>
#define PINO_RST 9
#define PINO_SDA 10

MFRC522 rfid(PINO_SDA, PINO_RST);

void setup() 
{
  Serial.begin(9600);

  SPI.begin();      // Inicia  SPI bus
  rfid.PCD_Init();
  
  Serial.println("Aproxime a sua tag...");
  Serial.println();
}

void loop() 
{
   //Procura nova tag
  if (!rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Seleciona uma tag
  if (!rfid.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";

  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " ")); 
     conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
  }

  Serial.println(conteudo);

//  Serial.print("UID RFID: ");
//  if (conteudo.substring(1) == "f2 b1 ae 20") //UID 1 - Chaveiro
//  {
//    Serial.println("Chaveiro");
//  }
//  else if (conteudo.substring(1) == "42 36 5a 1a") //UID 2 - Cartao
//  {
//    Serial.println("Cartão");
//  }
//  else
//  {
//    Serial.println("Não registrada");
//  }
}


// Programa: Controlando um servo motor com Arduino (servo motor arduino code) 
 
#include <Servo.h> // Inclui a biblioteca Servo para controlar servos
 
Servo meuServo; // Cria um objeto Servo para controlar o servo motor
int pos; // Declara uma variável para controlar a posição do servo motor 
 
void setup() {
    meuServo.attach(6); // Associa o servo motor ao pino digital 6 do Arduino
    meuServo.write(0); // Define a posição inicial do servo motor para 0 graus
}
 
void loop() {
    // Movimento do servo de 0 a 90 graus
    for (pos = 0; pos < 90; pos++) {
        meuServo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo movimento
 
    // Movimento do servo de 90 a 0 graus
    for (pos = 90; pos >= 0; pos--) {
        meuServo.write(pos); // Define a posição atual do servo
        delay(15); // Aguarda 15 milissegundos antes de mover para a próxima posição
    }
    delay(1000); // Aguarda 1 segundo antes de iniciar o próximo ciclo
}








