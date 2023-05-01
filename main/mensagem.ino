#include <LiquidCrystal_I2C.h>

extern String lastMsg;

void mensagem(String msg) {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);

  if (msg.length() > 16) {
    delay(500);
    for (int i = 0; i < msg.length() - 15; i++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
    lcd.setCursor(0, 0); 
  }
  lastMsg = "";
}

void mensagem2(String msg) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);

  if (msg.length() > 16) {
    delay(500);
    for (int i = 0; i < msg.length() - 15; i++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
    lcd.setCursor(0, 0); 
  }
  delay(2000);
  lcd.clear();
  lastMsg = "";
}
