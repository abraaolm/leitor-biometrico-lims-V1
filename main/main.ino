#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define pinRx 8
#define pinTx 7

const int led_verde = 10;
const int led_vermelho = 9;
const int rele = 11;
const int led_amarelo = 12;
const int buzzer = A1;

extern const int buzzer;

extern void removerDigital();
extern void adicionarDigital();
extern void sem_correspodencia();
extern void nao_encontrou_digital();
extern void erro_comunicacao();
extern void imagem_confusa();
extern void erro_desconhecido();
extern void autorizado();
extern void mensagem();
extern void mensagem1();
extern void mensagem2();
extern void buzzer_pi3();

LiquidCrystal_I2C lcd(0x20,16,2);

#define pinButton 2
#define pinButton2 3

bool grava = false; 

SoftwareSerial mySerial(pinTx, pinRx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup() {

  Serial.begin(9600);
  delay(100);
  finger.begin(57600);

  lcd.init();
  lcd.backlight(); 
  pinMode(led_verde, OUTPUT);
  digitalWrite(led_verde, LOW);

  pinMode(led_amarelo, OUTPUT);
  digitalWrite(led_amarelo, LOW);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

    pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  
  pinMode(led_vermelho , OUTPUT);
  digitalWrite(led_vermelho, LOW);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);

  if (finger.verifyPassword()) {

    lcd.setCursor(3,0);
    lcd.print("Iniciando...");
    lcd.clear();
    lcd.print("Tudo Pronto");
    lcd.setCursor(2,0);
    digitalWrite(led_verde, HIGH);
    buzzer_pi3();
    delay(1000);
    lcd.setCursor(0,1); 
    //lcd.print("Versao cod. 1.5");
    digitalWrite(led_verde, LOW);
    lcd.clear();
    mensagem("Insira a Digital");

}
  else {
    digitalWrite(led_amarelo, HIGH);
    Serial.println("Sensor não encontrado, verifique a ligação");
    mensagem("Sensor nao encontrado, verifique a ligacao");
    while (1) { 
      delay(1);
    }
  }
  if (grava) {
    while (  getFingerprintEnroll() == -1 );
  }
}

String lastMsg = "";

void loop() {

  if (digitalRead(pinButton) == LOW) {
    removerDigital();
  }
  if (digitalRead(pinButton2) == LOW) {
    adicionarDigital();
  } 
  byte leitura = getFingerprintID();
}

uint8_t readnumberadd(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem capturada");
      break;
    case FINGERPRINT_NOFINGER:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro na comunnicacao");
      erro_comunicacao();
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro na imagem");
      return p;
    default:
      Serial.println("Erro desconhecido");
      erro_desconhecido();
      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem Convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem muito confusa");
      imagem_confusa();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro na comunicacao");
      erro_comunicacao();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Nao foi possive encontrar digital");
          nao_encontrou_digital();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Nao foi possive encontrar digital");
          nao_encontrou_digital();
      return p;
    default:
      Serial.println("Erro desconhecido");
      erro_desconhecido();
      return p;
  }

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Impressao compativel");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro de comunicacao");
    erro_comunicacao();
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Sem correspodencia");
    sem_correspodencia();
    return p;
  } else {
    Serial.println("Erro Desconhecido");
    erro_desconhecido();
    return p;
  }
  autorizado();
}