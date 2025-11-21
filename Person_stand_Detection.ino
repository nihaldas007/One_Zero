/*
 * ESP32-CAM IR Sensor Interrupt Wake-up System
 * * HARDWARE CONNECTIONS:
 * - IR Sensor Signal -> GPIO 14
 * - IR Sensor VCC    -> 3.3V or 5V (Check your sensor specs)
 * - IR Sensor GND    -> GND
 * - Flash LED        -> GPIO 4 (Built-in)
 *
 * LOGIC:
 * - Active: LED ON.
 * - Idle (5s): LED OFF -> Enter Deep Sleep.
 * - Wakeup: Hardware Interrupt (EXT0) on Pin 14 wakes chip immediately.
 */

#include "esp_camera.h"
#include "driver/rtc_io.h"

// --- PIN DEFINITIONS ---
#define SENSOR_PIN GPIO_NUM_14
#define LED_PIN    GPIO_NUM_4

// --- TIMING CONFIGURATION ---
#define IDLE_TIMEOUT_MS 5000  // 5 Seconds wait before sleep

// --- SENSOR LOGIC ---
// Most IR Obstacle sensors are LOW when object detected, HIGH when clear.
// If your sensor is opposite, swap these two values.
#define SENSOR_ACTIVE_LEVEL LOW 
#define SENSOR_IDLE_LEVEL   HIGH

unsigned long lastActivityTime = 0;

void setup() {
  Serial.begin(115200);
  
  // 1. CRITICAL: Disable GPIO hold if it was enabled during previous sleep
  // This releases the lock on Pin 4 so we can turn it ON again.
  gpio_hold_dis(LED_PIN); 
  gpio_deep_sleep_hold_dis();

  // 2. Initialize Pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP); // Pullup ensures signal is stable

  // 3. Initial State Check
  // If we just woke up or just powered on, turn LED ON immediately
  digitalWrite(LED_PIN, HIGH);
  
  // Reset timer
  lastActivityTime = millis();

  // Debug Print
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println(">>> WOKE UP via IR INTERRUPT! <<<");
  } else {
    Serial.println(">>> Normal Power On <<<");
  }
}

void loop() {
  int sensorState = digitalRead(SENSOR_PIN);

  // --- MOVEMENT DETECTED ---
  if (sensorState == SENSOR_ACTIVE_LEVEL) {
    // Reset the sleep timer
    lastActivityTime = millis();
    
    // Ensure LED is ON
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motion Detected: Active");
  } 
  
  // --- NO MOVEMENT (IDLE) ---
  else {
    unsigned long currentMillis = millis();
    
    // Check if 5 seconds have passed
    if (currentMillis - lastActivityTime >= IDLE_TIMEOUT_MS) {
      enterSleepMode();
    }
  }
  
  delay(50); // Short delay to prevent CPU spamming
}

void enterSleepMode() {
  Serial.println("Idle timeout reached. Engaging Interrupt System & Sleep...");

  // 1. Turn OFF the Flash LED
  digitalWrite(LED_PIN, LOW);

  // 2. Setup the Wake-up Interrupt (EXT0)
  // logic: If sensor is Active LOW, we wake up when pin is 0.
  // 0 = Wake on Low, 1 = Wake on High
  int wakeLogic = (SENSOR_ACTIVE_LEVEL == LOW) ? 0 : 1;
  
  // Validates that the pin is an RTC pin (GPIO 14 is valid for RTC)
  if (rtc_gpio_is_valid_gpio(SENSOR_PIN)) {
    esp_sleep_enable_ext0_wakeup(SENSOR_PIN, wakeLogic);
    Serial.println("Interrupt Configured on Pin 14.");
  } else {
    Serial.println("Error: Pin 14 is not a valid RTC pin on this board variant!");
  }

  // 3. Optional: Hold LED LOW during sleep to prevent faint glowing
  gpio_hold_en(LED_PIN);

  // 4. Go to Deep Sleep
  Serial.println("Sleeping...");
  Serial.flush();
  esp_deep_sleep_start();
}