#include <Arduino.h>

extern const int pinRele = A0;
extern const int buzzer = A1;
extern void buzzer_pi3();
extern void buzzer_pi2();
extern void buzzer_pi();

  void autorizado(){
    digitalWrite(pinRele, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acesso Permitido");
    buzzer_pi();
    mensagem2("Acesso Permitido");
    delay(100);
    digitalWrite(pinRele, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void nao_autorizado(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Acesso Negado");
    buzzer_pi();
    mensagem2("Acesso Negado"); 
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void sem_correspodencia(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sem correspodencia");
    buzzer_pi();
    mensagem2("Sem correspodencia");
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
  }

  void nao_encontrou_digital(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Digital nao encontrada");
    buzzer_pi2();
    mensagem2("Digital nao encontrada");
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void erro_comunicacao(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Erro de comunicacao");
    buzzer_pi2();
    mensagem2("Erro de comunicacao");
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void imagem_confusa(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imagem muito confusa");
    buzzer_pi2();
    mensagem2("Imagem muito confusa");
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }

  void erro_desconhecido(){
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Erro desconhecido");
    buzzer_pi2();
    mensagem2("Erro desconhecido");
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(200);
    mensagem("Insira a Digital");
    return finger.fingerID;
  }
