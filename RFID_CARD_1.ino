#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 2
#define RST_PIN 12
#define LED_PIN 4       // LED Pin
#define LED_TIME 4000   // LED ON time in ms

MFRC522 rfid(SS_PIN, RST_PIN);

// --- Users' Card UID ---
String uid_Piyal = "61:EE:EE:00";   // Change to Piyal card UID
String uid_Nihal = "37:79:0E:05";   // Change to Nihal card UID

void setup() {
  Serial.begin(115200);
  SPI.begin(14, 13, 15);  // SCK, MISO, MOSI
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== RFID Access System with LED ===");
  Serial.println("Scan your card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String UID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) UID += "0";
    UID += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) UID += ":";
  }
  UID.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(UID);

  // --- Check Users ---
  if (UID == uid_Piyal) {
    Serial.println("✔ Piyal Access Granted");
    digitalWrite(LED_PIN, HIGH);
    delay(LED_TIME);
    digitalWrite(LED_PIN, LOW);
  }
  else if (UID == uid_Nihal) {
    Serial.println("✔ Nihal Access Granted");
    digitalWrite(LED_PIN, HIGH);
    delay(LED_TIME);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Serial.println("❌ Access Denied (Unknown Card)");
  }

  rfid.PICC_HaltA();
}
