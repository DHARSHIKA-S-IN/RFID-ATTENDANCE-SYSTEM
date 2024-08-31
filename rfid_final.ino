
#include <SPI.h>
#include <MFRC522.h>
#include<stdio.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>

//-----------------------------------------------------------------------------------------------------

constexpr uint8_t RST_PIN = D3;    
constexpr uint8_t SS_PIN = D4;
#define Buzzer D8
#define LED D0    

//-----------------------------------------------------------------------------------------------------

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

//-----------------------------------------------------------------------------------------------------

String tag;
String s1,s2,s3,s4,s5;
String nam;
int blockNum = 2;  
byte bufferLen = 18;
byte readBlockData[18];
String card_holder_name;
const String sheet_url = "https://script.google.com/macros/s/AKfycbwxDrMpR3dgbZvD8e3oXEfb3gpPsFJuuXFzPiG38cxCN2N6tBIM1Ei35uI6InYHumGY5A/exec?name=";
bool i[5]={0,0,0,0,0};
//-----------------------------------------------------------------------------------------------------

const uint8_t fingerprint[20] = {0xA3, 0x4E, 0xA3, 0x86, 0x10, 0xDA, 0x6C, 0xD1, 0x8C, 0x73, 0x54, 0xAB, 0xE6, 0x8F, 0x7D, 0x21, 0x72, 0x2C, 0xB4, 0xD5};
//A3 4E A3 86 10 DA 6C D1 8C 73 54 AB E6 8F 7D 21 72 2C B4 D5
//-----------------------------------------------------------------------------------------------------
#define WIFI_SSID "Aswin's Galaxy M31s"
#define WIFI_PASSWORD "skullcrusher"
//-----------------------------------------
LiquidCrystal_I2C lcd(0x3F, 16, 2);


void setup() {
  Serial.begin(9600);
  pinMode(Buzzer,OUTPUT);   
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  lcd.begin();
  lcd.backlight();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  lcd.print("WIFI CONNECTED");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.println("RC 522");
  rfid.PCD_DumpVersionToSerial();  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  lcd.clear();
  lcd.print("Scan your card:");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
   
    for (byte i = 0; i < 4; i++) {
      tag.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      tag.concat(String(rfid.uid.uidByte[i], HEX));
    }
   
     s1=" 07 b0 52 9a";
     s2 =" 57 57 f0 90";
     s3 =" f7 5f bb 92";
     s4 =" 47 25 59 9a";
     s5=" e3 68 9b b6";
    if(s1 == tag)
    {
        digitalWrite(Buzzer,HIGH);
        digitalWrite(LED,HIGH);
        delay(200);
        digitalWrite(Buzzer,LOW);
        digitalWrite(LED,LOW);
        nam="ASWIN.S";
        Serial.println(nam);
    }
    else if(s2 == tag)
    {
        digitalWrite(Buzzer,HIGH);
        digitalWrite(LED,HIGH);
        delay(200);
        digitalWrite(Buzzer,LOW);
        digitalWrite(LED,LOW);
        nam="ASHVATHAN.V.M";
        Serial.println(nam);
    }
    else if(s3 == tag)
    {
         digitalWrite(Buzzer,HIGH);
        digitalWrite(LED,HIGH);
        delay(200);
        digitalWrite(Buzzer,LOW);
        digitalWrite(LED,LOW);
        nam="DHARSHIKA.S";
        Serial.println(nam);
    }
    else if(s4 == tag)
    {
       digitalWrite(Buzzer,HIGH);
        digitalWrite(LED,HIGH);
        delay(200);
        digitalWrite(Buzzer,LOW);
        digitalWrite(LED,LOW);
        nam="GOKUL.S";
        Serial.println(nam);
              
    }  
    else if(s5 == tag)
    {
       digitalWrite(Buzzer,HIGH);
        digitalWrite(LED,HIGH);
        delay(200);
        digitalWrite(Buzzer,LOW);
        digitalWrite(LED,LOW);
        nam="SANTHOSH";
        Serial.println(nam); 
              
    }  
     
    else
    {
        digitalWrite(Buzzer,HIGH);
        delay(1000);
        digitalWrite(Buzzer,LOW);
        nam="No Match Found";
        Serial.println(nam);
    }

    Serial.println(tag);
       tag = "";
       lcd.clear();
       lcd.print(nam);
       delay(2000);
       lcd.clear();
       Serial.println();

 
  if (WiFi.status() == WL_CONNECTED) {
    
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    
    client->setFingerprint(fingerprint);
    card_holder_name = sheet_url +nam;
    card_holder_name.trim();
    Serial.println(card_holder_name);
    HTTPClient https;
    Serial.print(F("[HTTPS] begin...\n"));

    if (https.begin(*client, (String)card_holder_name)){
      Serial.print(F("[HTTPS] GET...\n"));
      int httpCode = https.GET();
      if (httpCode > 0) {
        
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        
      }
      else 
      {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
      https.end();
      delay(1000);
    }
    else {
      Serial.printf("[HTTPS} Unable to connect\n");
    }
  }

}
 lcd.print("Scan your card:");
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}