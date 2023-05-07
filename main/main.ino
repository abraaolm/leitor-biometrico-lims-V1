#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Password.h>
#include <Keypad.h>

const int pinRx = 50;
const int pinTx = 51;

const int led_verde = 10;
const int led_vermelho = 9;
const int rele = 11;
const int led_amarelo = 12;
const int buzzer = A1;
const int ldr = A2;
const byte LINHAS = 4;
const byte COLUNAS = 4;

int sensorValue = 0;   
int setpoint = 200; 

Password senha = Password("061723");

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//id

const byte PINOS_LINHAS[LINHAS] = {45, 43, 41, 39}; 
const byte PINOS_COLUNAS[COLUNAS] = {37, 35, 33, 31};

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado


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
extern void buzzer_pi();
extern void buzzer_pi3();
extern void buzzer_pi2();
extern void bem_vindo();

LiquidCrystal_I2C lcd(0x3F,20,4);
  
#define pinButton 2
#define pinButton2 3

bool grava = false; 

SoftwareSerial mySerial(pinTx, pinRx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

bool modo_cadastro = false;
bool modo_remover = false;
bool passapadento = false;
bool modo_livre = false;
void setup() {

  Serial.begin(115200);
  delay(100);
  finger.begin(57600);
  lcd.init();
  lcd.backlight(); 
  pinMode(led_verde, OUTPUT);
  digitalWrite(led_verde, LOW);
  pinMode(led_amarelo, OUTPUT);
  digitalWrite(led_amarelo, LOW);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  digitalWrite(buzzer, LOW);
  //O rele utilizado é invertido, ele precisa inciar em HIGH, e caso queira aciona-lo, mande um pulso LOW
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
  pinMode(led_vermelho , OUTPUT);
  digitalWrite(led_vermelho, LOW);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);

  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Leitor biometrico");
    lcd.setCursor(2,2);
    lcd.print("esta funcionando");
    lcd.setCursor(4,3);
    lcd.print("corretamente");
    digitalWrite(led_verde, HIGH);
    buzzer_pi3();
    delay(1000);
    digitalWrite(led_verde, LOW);
    bem_vindo();

}
  else {
    digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("O sensor nao");
  lcd.setCursor(2,2);
  lcd.print(" foi encontrado.");
  lcd.setCursor(0,3);
  lcd.print("Verifique a ligacao!");
    while (1) { 
      delay(1);
    }
  }
  if (grava) {
    while (  getFingerprintEnroll(id) == -1 );
  }
}

String lastMsg = "";

void loop() {

char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variável a leitura do teclado

sensorValue = analogRead(ldr);
  Serial.println(sensorValue); 
   if(sensorValue < setpoint){
 
     digitalWrite(rele, 0);
  
  } else {
	 
	 digitalWrite(rele, 1);
  
  }

if (leitura_teclas) { // Se alguma tecla foi pressionada
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);

    if (leitura_teclas == 'C') { // Caso a tecla 'C' seja pressionada
      modo_cadastro = true;
      senha.reset(); // Limpa a variável senha
      Serial.println("Modo cadastro ativado. Digite a senha e pressione A para confirmar ou B para cancelar");
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(1,2);
      lcd.print("NO MODO CADASTRO");
    } else if (leitura_teclas == 'D') { // Caso a tecla 'D' seja pressionada
      modo_remover = true;
      senha.reset(); // Limpa a variável senha
      Serial.println("Modo remover ativado. Digite a senha e pressione A para confirmar ou B para cancelar");
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(2,2);
      lcd.print("NO MODO REMOVER");
      
    } else if (leitura_teclas == 'A') { // Caso a tecla 'D' seja pressionada
      passapadento = true;
      senha.reset(); // Limpa a variável senha
      Serial.println("digita a senha pra entrar");
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(2,2);
      lcd.print("DESTRANCAR A PORTA");
      
    }
    else if (leitura_teclas == 'B') { // Caso a tecla 'D' seja pressionada
      modo_livre = true;
      senha.reset(); // Limpa a variável senha
      Serial.println("modo livre");
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("DIGITE A SENHA");
      lcd.setCursor(4,1);
      lcd.print("PARA ENTRAR");
      lcd.setCursor(3,2);
      lcd.print("NO MODO LIVRE");
      
    }else if (modo_cadastro) { // Caso estejamos no modo cadastro
      if (leitura_teclas == '#') { // Caso a tecla 'A' seja pressionada
        if (senha.evaluate()) { // Verifica se a senha digitada está correta
          Serial.println("Liberado!");
          adicionarDigital();
          //digitalWrite(led_verde, HIGH);
          //delay(500);
          //digitalWrite(led_verde, LOW);
        } else {
          Serial.println("Senha incorreta!");
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_cadastro = false;
      } else if (leitura_teclas == '*') { // Caso a tecla 'B' seja pressionada
        modo_cadastro = false;
        Serial.println("Operação cancelada");
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);

        bem_vindo();
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variável senha
      }
    } else if (modo_remover) { // Caso estejamos no modo remover
      if (leitura_teclas == '#') { // Caso a tecla 'A' seja pressionada
        if (senha.evaluate()) { // Verifica se a senha digitada está correta
          senha.reset(); // Limpa a senha
          Serial.println("Senha removida com sucesso!");
          removerDigital();
          ///digitalWrite(led_verde, HIGH);
          ///delay(500);
          //digitalWrite(led_verde, LOW);
        } else {
          Serial.println("Senha incorreta!");
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_remover = false;
      } else if (leitura_teclas == '*') { // Caso a tecla 'B' seja pressionada
        modo_remover = false;
        Serial.println("Operação cancelada");
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);

        bem_vindo();
      
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variável senha
      }
    
    }  
    else if (passapadento) { // Caso estejamos no modo remover
      if (leitura_teclas == '#') { // Caso a tecla 'A' seja pressionada
        if (senha.evaluate()) { // Verifica se a senha digitada está correta
          senha.reset(); // Limpa a senha
          Serial.println("passapadento");
          autorizado();
          ///digitalWrite(led_verde, HIGH);
          ///delay(500);
          //digitalWrite(led_verde, LOW);
        } else {
          Serial.println("Senha incorreta!");
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        passapadento = false;
      } else if (leitura_teclas == '*') { // Caso a tecla 'B' seja pressionada
        passapadento = false;
        Serial.println("Operação cancelada");
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);

        bem_vindo();
      
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variável senha
      }
    
    }
    else if (modo_livre) { // Caso estejamos no modo remover
      if (leitura_teclas == '#') { // Caso a tecla 'A' seja pressionada
        if (senha.evaluate()) { // Verifica se a senha digitada está correta
          senha.reset(); // Limpa a senha
          Serial.println("modo livre");
          buzzer_pi();
    lcd.clear();
while (true) {
  leitura_teclas = teclado_personalizado.getKey(); // Leia a tecla pressionada novamente

    // Código para ler a variável leitura_teclas

    if (leitura_teclas == 'B') {
        modo_livre = false;
                  buzzer_pi();
            digitalWrite(rele, 1);
        bem_vindo();

        break; // Sai do loop while
    }

    senha.reset(); // Limpa a senha

    lcd.setCursor(5, 1);
    lcd.print("MODO LIVRE");
    lcd.setCursor(2, 1);
    lcd.print(" ");
    delay(100);
    digitalWrite(rele, 0);
}

        } else {
          Serial.println("Senha incorreta!");
          lcd.clear();
          lcd.setCursor(3,1);
          lcd.print("SENHA INCORRETA");
          digitalWrite(led_vermelho, HIGH);
          buzzer_pi2();
          delay(700);
          digitalWrite(led_vermelho, LOW);
          bem_vindo();
        }
        modo_livre = false;
      } else if (leitura_teclas == '*') { // Caso a tecla 'B' seja pressionada
        modo_livre = false;
        Serial.println("Operação cancelada");
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("OPERACAO CANCELADA");
        buzzer_pi2();
        delay(500);

        bem_vindo();
      
      } else {
        Serial.print(leitura_teclas);
        senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variável senha
      }
    
    }else { // Caso não estejamos no modo cadastro ou remover
      Serial.println(leitura_teclas); // Exibe a tecla pressionada
    }
  }

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