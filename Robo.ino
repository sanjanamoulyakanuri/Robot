#include <SoftwareSerial.h>
#include <Servo.h>

Servo head;
Servo rh1;
Servo rh2;
Servo rh3;

Servo lh1;
Servo lh2;
Servo lh3;

// Define the RX and TX pins for the HC-05 module
const int BT_RX = 0;  // RX pin of HC-05 connected to pin 10 of Arduino
const int BT_TX = 1;  // TX pin of HC-05 connected to pin 11 of Arduino

// Create a SoftwareSerial object to communicate with the HC-05 module
SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Initialize SoftwareSerial communication with the HC-05 module
  BTSerial.begin(9600);

  Serial.println("Bluetooth Serial Initialized");

  // Attach servo motors to pins
  head.attach(13);
  rh1.attach(9);
  rh2.attach(10);
  rh3.attach(11);

  lh1.attach(5);
  lh2.attach(6);
  lh3.attach(7);
}

void loop() {
  // Check if data is available to read from the HC-05 module
  if (BTSerial.available()) {
    // Read the incoming byte from the HC-05 module
    String voice = BTSerial.readStringUntil('\n'); // Read the complete string until newline character

    // Print the received string to the Serial Monitor
    Serial.print("Received: ");
    Serial.println(voice);

    // Check the received string and perform actions accordingly
    if (voice.equals("hello")) {
      say_hi();
    } else if (voice.equals("shake hand")) {
      shake_hand();
    } else if (voice.equals("hands up")) {
      hands_up();
    } else if (voice.equals("hands down")) {
      hands_down();
    }
  }
}

void say_hi() {
  for (int i = 0; i <= 180; i++) {
    rh1.write(0 + i);
    if (i <= 90) {
      rh2.write(0 + i);
    }
    if (i <= 40) {
      rh3.write(20 + i);
    }
    delay(10);
  }
  for (int i = 1; i <= 3; i++) {
    for (int i = 0; i <= 60; i++) {
      rh3.write(60 + i);
      delay(10);
    }
    for (int i = 0; i <= 60; i++) {
      rh3.write(120 - i);
      delay(10);
    }
  }
  for (int i = 0; i <= 180; i++) {
    rh1.write(180 - i);
    if (i <= 90) {
      rh2.write(90 - i);
    }
    if (i <= 40) {
      rh3.write(60 - i);
    }
    delay(10);
  }
}

void hands_up() {
  for (int i = 0; i <= 180; i++) {
    rh1.write(0 + i);
    lh1.write(180 - i);
    delay(10);
  }
}

void hands_down() {
  for (int i = 0; i <= 180; i++) {
    rh1.write(180 - i);
    lh1.write(0 + i);
    delay(10);
  }
}

void shake_hand() {
  for (int i = 0; i <= 40; i++) {
    rh1.write(0 + i);
    delay(10);
  }
  for (int i = 0; i <= 3; i++) {
    for (int i = 0; i <= 30; i++) {
      rh1.write(40 + i);
      delay(10);
    }
    for (int i = 0; i <= 30; i++) {
      rh1.write(70 - i);
      delay(10);
    }
  }
  for (int i = 0; i <= 40; i++) {
    rh1.write(40 - i);
    delay(10);
  }
}