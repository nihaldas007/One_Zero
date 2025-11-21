# 🍽️ Tokenless Dining Management System  
### **Team Name:** One_Zero  
### **Date:** November 2025  

---

## 1. Introduction

The **Tokenless Dining Management System** automates dining operations without the need for physical tokens.  
It uses **PIN authentication**, **RFID card access**, and **IR-based presence detection** to provide secure, efficient, and power-saving dining management.

### **Key Features**
- Multi-user PIN authentication  
- RFID card–based access  
- IR presence detection  
- Automatic deep sleep for power saving  
- LED notifications for feedback  
- Optional OLED/TFT display for UI  

**Image Placeholder:**  
`![Overview](images/overview.jpg)`

---

## 2. System Components

- ESP32 / Arduino microcontroller  
- 2×2 Keypad  
- MFRC522 RFID Reader  
- PIR / IR Presence Sensor  
- LEDs for status indication  
- Optional OLED/TFT display  
- Power supply system  

**Image Placeholder:**  
`![Block Diagram](images/block_diagram.png)`

---

## 3. Module 1: Multi-Person PIN System

A simple 2×2 keypad allows multiple users to enter unique PINs.  
Each PIN corresponds to a specific registered user.  
LED feedback is provided for successful or failed authentication.

**Image Placeholder:**  
`![PIN Module](images/pin_module.png)`

---

## 4. Module 2: IR Sensor with ESP32-CAM & Deep Sleep

The IR sensor detects user presence.  
When no movement is detected for a set duration, the system enters **deep sleep** to conserve power.  
Motion automatically wakes the system back up.

**Image Placeholder:**  
`![IR Module](images/ir_sleep.png)`

---

## 5. Module 3: RFID Access System

The MFRC522 RFID reader allows users to scan their cards for quick access validation.  
Authorized UIDs are pre-registered, and the system provides LED feedback for granted or denied access.

**Image Placeholder:**  
`![RFID Module](images/rfid.png)`

---

## 6. Workflow

1. IR sensor detects presence → ESP32 wakes up  
2. User enters PIN or scans RFID card  
3. System validates identity  
4. LED indicates success or failure  
5. If no interaction is detected, system returns to deep sleep  

**Image Placeholder:**  
`![Workflow](images/workflow.png)`

---

## 7. Conclusion

This project demonstrates a secure, tokenless, and energy-efficient dining access system.  
It can be expanded to include:

- Cloud-based logging  
- Face recognition  
- Mobile app integration  
- Automatic attendance tracking  

---

## 👥 Developed By  
**Team One_Zero**

