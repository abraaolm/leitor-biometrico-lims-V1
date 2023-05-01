extern void buzzer_pi3();
extern void buzzer_pi();
extern void buzzer_pi2();
extern void erro_comunicacao();
extern void erro_desconhecido();
extern void imagem_confusa();

void adicionarDigital() {

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro de digital");
  buzzer_pi3();
  Serial.println("\nCadastro de digital");
  Serial.println("Digite o ID # (entre 1 e 127) da digital que vai gravar...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Digite o ID # (entre 1 e 127) da digital que vai gravar...");
  buzzer_pi();


  id = readnumberadd();
  if (id == 0) {
    return;
  }
  Serial.print("Cadastrando ID #");
  Serial.println(id);
  delay(500);
  
  while (!  getFingerprintEnroll() );
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Aguardando digital para cadastro #"); Serial.println(id);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Aguardando digital para cadastro #");
      buzzer_pi();
      delay(500);
 

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        lcd.clear();
        lcd.print("Communication error");
        buzzer_pi2();
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        lcd.clear();
        lcd.print("Imaging error");
        buzzer_pi2();
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
      default:
        Serial.println("Unknown error");
        lcd.clear();
        lcd.print("Unknown error");
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
    }
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.clear();
      lcd.print("Image too messy");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Communication error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
  }

  Serial.println("Retire o dedo");
      buzzer_pi();
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Retire o dedo");
      delay(500);
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Coloque o mesmo dedo novamente");
      buzzer_pi();
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Coloque o mesmo dedo novamente");
      delay(500);

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        lcd.clear();
        lcd.print("Communication error");
        buzzer_pi2();
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        lcd.clear();
        lcd.print("Imaging error");
        buzzer_pi2();
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
      default:
        Serial.println("Unknown error");
        lcd.clear();
        lcd.print("Unknown error");
        buzzer_pi2();
        delay(1500);
        lcd.clear();
        lcd.print("Aguardando digital para cadastro #");
        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.clear();
      lcd.print("Image too messy");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Communication error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
      return p;
  }

  Serial.print("Criando modelo para ID #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Digitais conferem!");
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Erro de comunicação");
      lcd.clear();
      lcd.print("Erro de comunicação");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      Serial.println("Digitais nao batem!");
      lcd.clear();
      lcd.print("Digitais nao batem!");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  } else {
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Armazenado com sucesso!");
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Armazenado com sucesso!");
      buzzer_pi3();
      delay(1000);
      lcd.clear();
      lcd.print("Insira a Digital");

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Erro de comunicação");
      lcd.clear();
      lcd.print("Erro de comunicação");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
      Serial.println("Could not store in that location");
      lcd.clear();
      lcd.print("Could not store in that location");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
      Serial.println("Error writing to flash");
      lcd.clear();
      lcd.print("Error writing to flash");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  } else {
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      buzzer_pi2();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Cadastro Falhou");
      buzzer_pi();
      delay(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Insira a Digital");
    return p;
  }

  return true;
}

uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}