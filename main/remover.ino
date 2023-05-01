extern const int led_verde;
extern const int led_vermelho;
extern const int led_amarelo;
extern void buzzer_pi();
extern void buzzer_pi2();

void removerDigital() {
    //Serial.println("Modo de remover digital ativado");
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Modo remover");
    digitalWrite(led_amarelo, HIGH);
    buzzer_pi2();
    delay(1200);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Insira o ID da digital que deseja remover: ");
    buzzer_pi();
    //Serial.print("Insira o ID da digital que deseja remover: ");
    while (!Serial.available()) { // aguarda entrada no serial
    }
    int id = Serial.parseInt();
    //Serial.print("Removendo digital do ID ");
    //Serial.println(id);
    int r = finger.deleteModel(id);
    if (r != FINGERPRINT_OK) {
        //Serial.print("Erro ao remover digital: ");
        //Serial.println("finger.errorCode");
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Erro ao remover digital");
        digitalWrite(led_amarelo, LOW);
        falha();
        delay(1000);
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Insira a Digital");
    } else {
        //Serial.println("Digital removida com sucesso!");
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Digital ") && lcd.print(id);
        lcd.setCursor(1,1);
        lcd.print("Removida com sucesso!");
        digitalWrite(led_verde, HIGH);
        digitalWrite(led_amarelo, LOW);
        buzzer_pi3();
        delay(1000);
        digitalWrite(led_verde, LOW);
        lcd.clear();
        lcd.print("Insira a Digital");
    }
    delay(1500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Insira a Digital");
}
