extern const int led_verde;
extern const int led_vermelho;
extern const int led_amarelo;

extern void buzzer_pi3();
extern void buzzer_pi();
extern void buzzer_pi2();
extern void erro_comunicacao();
extern void erro_desconhecido();
extern void imagem_confusa();
extern void sucesso();
extern void falha();
extern void erro_na_comunicacao_1();
extern void erro_na_imagem_1();
extern void erro_desconhecido_1();
extern void imagem_baguncada();
extern void erro_na_comunicacao_2();
extern void nao_encontrou_digital_2();
extern void erro_desconhecido_2();


void adicionarDigital() {

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Cadastro de digital");
  digitalWrite(led_amarelo, HIGH);
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
      sucesso();
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
        erro_na_comunicacao_1();
        break;
      case FINGERPRINT_IMAGEFAIL:
        erro_na_imagem_1();
        break;
      default:
        erro_desconhecido_1();
        break;
    }
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      imagem_baguncada();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      erro_na_comunicacao_2();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      nao_encontrou_digital_2();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      nao_encontrou_digital_2();
      return p;
    default:
      erro_desconhecido_2();
      return p;
  }

  Serial.println("Retire o dedo");
      sucesso();
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Retire o dedo");

  delay(1300);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Coloque o mesmo dedo novamente");
      sucesso();
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
        erro_na_comunicacao_1();
        break;
      case FINGERPRINT_IMAGEFAIL:
        erro_na_imagem_1();
        break;
      default:
        erro_desconhecido_1();
        break;
    }
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      imagem_baguncada();
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      erro_na_comunicacao_2();
      return p;
    case FINGERPRINT_FEATUREFAIL:
      nao_encontrou_recurso();
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      nao_encontrou_recurso();
      return p;
    default:
      erro_desconhecido_2();
      return p;
  }

  Serial.print("Criando modelo para ID #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Digitais conferem!");

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    erro_na_comunicacao_2();
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      Serial.println("Digitais nao batem!");
      lcd.clear();
      lcd.print("Digitais nao batem!");
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
    return p;
  } else {
    erro_desconhecido_2();
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Armazenado com sucesso!");
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Armazenado com sucesso!");
      digitalWrite(led_verde, HIGH);
      digitalWrite(led_amarelo, LOW);
      buzzer_pi3();
      delay(1000);
      digitalWrite(led_verde, LOW);
      lcd.clear();
      lcd.print("Insira a Digital");

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      erro_na_comunicacao_2();
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
      Serial.println("Nao é possível guardar nesse local");
      lcd.clear();
      lcd.print("Nao é possível guardar nesse local");
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
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
      Serial.println("Erro ao gravar no flash");
      lcd.clear();
      lcd.print("Erro ao gravar no flash");
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
    return p;
  } else {
      erro_desconhecido_2();
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