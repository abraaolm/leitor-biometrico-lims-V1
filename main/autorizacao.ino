#include <Arduino.h>

extern void buzzer_pi3();
extern void buzzer_pi2();
extern void buzzer_pi();
extern const int buzzer;
extern const int led_verde;
extern const int led_vermelho;
extern const int rele;
extern const int led_amarelo;

void autorizado(){        
  digitalWrite(led_verde, HIGH);
  digitalWrite(rele, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Acesso Permitido");
  buzzer_pi();
  //mensagem1("Acesso Permitido");
  delay(700);
  digitalWrite(rele, LOW);
  delay(700);
  digitalWrite(led_verde, LOW);
  delay(200);
  mensagem("Insira a Digital");
  return finger.fingerID;
}

void sem_correspodencia(){
  digitalWrite(led_vermelho, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sem correspodencia");
  buzzer_pi();
  mensagem1("Sem correspodencia");
  delay(100);
  digitalWrite(led_vermelho, LOW);
  delay(200);
  mensagem("Insira a Digital");
}

void nao_encontrou_digital(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Digital nao encontrada");
  buzzer_pi2();
  mensagem1("Digital nao encontrada");
  delay(100);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  mensagem("Insira a Digital");
  return finger.fingerID;
}

void erro_comunicacao(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Erro de comunicacao");
  buzzer_pi2();
  mensagem1("Erro de comunicacao");
  delay(100);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  mensagem("Insira a Digital");
  return finger.fingerID;
}

void imagem_confusa(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Imagem muito confusa");
  buzzer_pi2();
  mensagem1("Imagem muito confusa");
  delay(100);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  mensagem("Insira a Digital");
  return finger.fingerID;
}

void erro_desconhecido(){
  digitalWrite(led_amarelo, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Erro desconhecido");
  buzzer_pi2();
  mensagem1("Erro desconhecido");
  delay(100);
  digitalWrite(led_amarelo, LOW);
  delay(200);
  mensagem("Insira a Digital");
  return finger.fingerID;
}