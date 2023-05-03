#include <Arduino.h>

extern void buzzer_pi3();
extern void buzzer_pi2();
extern void buzzer_pi();
extern const int buzzer;
extern const int led_verde;
extern const int led_vermelho;
extern const int rele;
extern const int led_amarelo;
extern void falha();

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

void erro_na_comunicacao_1(){
  Serial.println("Erro na comunicacao");
  lcd.clear();
  lcd.print("Erro na comunicacao");
  falha();
  delay(1500);
  lcd.clear();
  lcd.print("Aguardando digital para cadastro #");
}

void erro_na_imagem_1(){
  Serial.println("Erro na Imagem");
  lcd.clear();
  lcd.print("Erro na Imagem");
  falha();
  delay(1500);
  lcd.clear();
  lcd.print("Aguardando digital para cadastro #");
}

void erro_desconhecido_1(){
  Serial.println("Erro Desconhecido");
  lcd.clear();
  lcd.print("Erro Desconhecido");
  falha();
  delay(1500);
  lcd.clear();
  lcd.print("Aguardando digital para cadastro #");
}

void imagem_baguncada(){
  Serial.println("Image muito baguncada");
  lcd.clear();
  lcd.print("Imagem muito baguncada");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro Falhou");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.print("Insira a Digital");
}

void erro_na_comunicacao_2(){
  Serial.println("Erro na comunicacao");
  lcd.clear();
  lcd.print("Erro na comunicacao");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro Falhou");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.print("Insira a Digital");
}

void nao_encontrou_digital_2(){
  Serial.println("Nao foi possivel encontrar recursos de impressao digital");
  lcd.clear();
  lcd.print("Nao foi possivel encontrar recursos de impressao digital");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro Falhou");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.print("Insira a Digital"); 
}

void erro_desconhecido_2(){
  Serial.println("Erro Desconhecido");
  lcd.clear();
  lcd.print("Erro Desconhecido");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro Falhou");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.print("Insira a Digital");
}

void nao_encontrou_recurso(){
  Serial.println("Nao foi possivel encontrar recursos de impressão digital");
  lcd.clear();
  lcd.print("Nao foi possivel encontrar recursos de impressão digital");
  falha();
  delay(1000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro Falhou");
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  buzzer_pi3();
  delay(1000);
  digitalWrite(led_vermelho, LOW);
  lcd.clear();
  lcd.print("Insira a Digital");
}
