#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myServo;
const int TRIG_PIN = 11;
const int ECHO_PIN = 10;
const int BUZZER_PIN = 8;
unsigned long lastBeep = 0;
void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
}

unsigned long pomiar() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long time = pulseIn(ECHO_PIN, HIGH);
  unsigned long  distance = time / 58;
  return distance;
}

void beep(unsigned long distance) {
  if (distance < 20) distance = 20;
  if (distance > 200) distance = 200;

  unsigned long interval = map(distance, 20, 200, 50, 500);
  if (millis() - lastBeep >=interval){
  if (distance > 100) {
    noTone(BUZZER_PIN);
  }  
  
  else {
    tone(BUZZER_PIN, map(distance, 20, 150, 2000, 500));
    delay(30);
    noTone(BUZZER_PIN);
  }
  lastBeep = millis();
  }
}  

void loop() {
  for (int i = 0; i < 180; i++) {
    delay(15);
    myServo.write(i);
    unsigned long dist = pomiar();
    beep(dist);
  }
  for (int i = 181; i > 0; i--) {
    delay(15);
    myServo.write(i);
    unsigned long dist = pomiar();
    beep(dist);
  }
}

