#include <Arduino.h>

//pinRele  = led_verde
//rele = rele
//pinLed = led_vermelho
//led amarelo = led_amarelo

//const int pinRele = A0;
//extern const int pinRele;
extern const int buzzer;
extern const int led_verde;
extern const int led_vermelho;
extern const int rele;
extern const int led_amarelo;

extern void buzzer_pi3();
extern void buzzer_pi2();
extern void buzzer_pi();


  void autorizado(){
    digitalWrite(led_verde, HIGH);
    digitalWrite(rele, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acesso Permitido");
    buzzer_pi();
    mensagem2("Acesso Permitido");
    delay(100);
    digitalWrite(led_verde, LOW);
    digitalWrite(rele, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void nao_autorizado(){
    digitalWrite(led_vermelho, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acesso Negado");
    buzzer_pi();
    mensagem2("Acesso Negado"); 
    delay(100);
    digitalWrite(led_vermelho, LOW);
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
    mensagem2("Sem correspodencia");
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
    mensagem2("Digital nao encontrada");
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
    mensagem2("Erro de comunicacao");
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
    mensagem2("Imagem muito confusa");
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
    mensagem2("Erro desconhecido");
    delay(100);
    digitalWrite(led_amarelo, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }
