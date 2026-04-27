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
//  Serial.print("UID da tag :");
  String conteudo= "";

  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " ")); 
     conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
  }

//  Serial.println(conteudo);

  Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "f2 b1 ae 20") //UID 1 - Chaveiro
  {
    Serial.println("Chaveiro");
  }
  else if (conteudo.substring(1) == "42 36 5a 1a") //UID 2 - Cartao
  {
    Serial.println("Cartão");
  }
  else
  {
    Serial.println("Não registrada");
  }
}











