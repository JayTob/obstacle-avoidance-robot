// CODE BY BOSH MACSIS & DR. SURESAN PARETH (Updated by ChatGPT)
#include <IRremote.h>  // For IRremote v3.x and later

#define IR_RECEIVE_PIN 6

void setupPins() {
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  setupPins();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Robot Ready...");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Received Code: ");
    Serial.println(code, HEX);  // Use HEX to match actual remote values
    handleIRCommand(code);
    IrReceiver.resume();
  }
}

void handleIRCommand(unsigned long code) {
  switch (code) {
    case 0x00FFA25D:  // Example: FORWARD
      Forward();
      break;
    case 0x00FF22DD:  // Example: BACK
      Back();
      break;
    case 0x00FF02FD:  // Example: LEFT
      Left();
      break;
    case 0x00FFC23D:  // Example: RIGHT
      Right();
      break;
    case 0x00FF629D:  // Example: STOP
      Stop();
      break;
    default:
      Serial.println("Unknown code");
      break;
  }
}

void Forward() {
  digitalWrite(3, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
  Serial.println("Moving Forward");
}

void Back() {
  digitalWrite(3, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  Serial.println("Moving Backward");
}

void Left() {
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(600);
  Stop();
  Serial.println("Turning Left");
}

void Right() {
  digitalWrite(3, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  delay(600);
  Stop();
  Serial.println("Turning Right");
}

void Stop() {
  digitalWrite(3, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  Serial.println("Stopped");
}
