#include <Keypad.h>

#define LED_PIN 4
#define LIGHT_TIME 3000

// --- 2x2 KEYPAD ---
const byte ROWS = 2;
const byte COLS = 2;

char keys[ROWS][COLS] = {
  {'1','2'},
  {'4','5'}
};

byte rowPins[ROWS] = {12, 13};
byte colPins[COLS] = {14, 15};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- PASSWORDS ---
String passPiyal   = "1245";
String passOrpon   = "2514";
String passNihal   = "4152";

String input = "";     // store pressed keys

void resetInput() {
  input = "";
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== MULTI PERSON PASSWORD SYSTEM ===");
  Serial.println("Enter 4 keys...");
}

void loop() {
  char key = keypad.getKey();

  if (key) {

    // show only "*"
    Serial.print("*");

    input += key;

    // যদি ভুল digit আসে
    if (key!='1' && key!='2' && key!='4' && key!='5') {
      Serial.println("\n❌ Wrong Key! Resetting...");
      resetInput();
      return;
    }

    // যদি ৪টা digit সম্পূর্ণ হয়
    if (input.length() == 4) {

      Serial.println(); // line break

      if (input == passPiyal) {
        Serial.println("✔ Piyal Access Granted");
      }
      else if (input == passOrpon) {
        Serial.println("✔ Orpon Access Granted");
      }
      else if (input == passNihal) {
        Serial.println("✔ Nihal Access Granted");
      }
      else {
        Serial.println("❌ Wrong Password! Enter your right Password: ");
        resetInput();
        return;
      }

      // LED ON
      digitalWrite(LED_PIN, HIGH);
      delay(LIGHT_TIME);
      digitalWrite(LED_PIN, LOW);

      resetInput();
    }
  }

  delay(20);
}
