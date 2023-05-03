extern const int led_verde;
extern const int led_vermelho;
extern const int led_amarelo;
extern void buzzer_pi();
extern void buzzer_pi2();

void removerDigital() {
    lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("MODO REMOVER");
    digitalWrite(led_amarelo, HIGH);
    buzzer_pi2();
    delay(1200);
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("Insira o ID da");
    lcd.setCursor(5,2);
    lcd.print("digital que");
    lcd.setCursor(2,3);
    lcd.print(" deseja remover:");
    buzzer_pi();
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
        lcd.setCursor(3,1);
        lcd.print("ERRO AO REMOVER");
        lcd.setCursor(6,2);
        lcd.print("A DIGITAL");
        digitalWrite(led_amarelo, LOW);
        falha();
        delay(1000);
        bem_vindo();
    } else {
        //Serial.println("Digital removida com sucesso!");
        lcd.clear();
        lcd.setCursor(5,1);
        lcd.print("A DIGITAL") && lcd.print(id);
        lcd.setCursor(4,2);
        lcd.print("FOI REMOVIDA");
        lcd.setCursor(5,3);
        lcd.print("COM SUCESSO");
        digitalWrite(led_verde, HIGH);
        digitalWrite(led_amarelo, LOW);
        buzzer_pi3();
        delay(1000);
        digitalWrite(led_verde, LOW);
        bem_vindo();
    }
    delay(1500);
    bem_vindo();
}
