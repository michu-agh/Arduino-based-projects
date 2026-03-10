#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myServo;
const int TRIG_PIN = 11;
const int ECHO_PIN = 10;
const int BUZZER_PIN = 8;
unsigned long lastBeep = 0;

int current_angle = 0;
int direction = 1;
int max_angle = 180;
int min_angle = 0;
unsigned long last_dist;
unsigned long lastUpdate = 0;
int lcd_interval = 1000;

LiquidCrystal lcd(12, 3, 4, 5, 6, 7);

enum Mode {
  TRACK,
  SEARCH
};

Mode mode = SEARCH;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
}

unsigned long pomiar() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
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

void wyswietlanie (unsigned long distance){
  if (millis() - lastUpdate >= lcd_interval){
    lcd.setCursor(0 ,0);
    lcd.print("                           ");
    lcd.setCursor(0, 0);
    lcd.print("                ");

    if (mode == SEARCH) {
      lcd.setCursor(0, 0);
      lcd.print("Searching. . . ");
      lcd.setCursor(0, 1);
      lcd.print(distance);
      lcd.print("cm");

    }  
    else if (mode == TRACK) {
      lcd.setCursor(0, 0);
      lcd.print("MAM!!!");
      lcd.setCursor(0, 1);
      lcd.print(distance);
      lcd.print("cm");
      lcd.print("  Kat:  ");
      lcd.print(current_angle);

    }
  lastUpdate = millis();
  }
  
}
void poruszanie(unsigned long dist, unsigned long last_dist) {
  myServo.write(current_angle);

  if (mode == SEARCH) {
    max_angle = 180;
    min_angle = 0;
    if (dist < 50) {
      mode = TRACK;
    
    }
    else if (current_angle >= max_angle || current_angle <= min_angle){
      direction *= -1;
    }
  }
  else if (mode == TRACK){
    if (dist >= 50) {
      mode = SEARCH;
    }

    else{
      if ((last_dist + 2) < dist) {
        direction *= -1;

      }
    }
  }
  current_angle += direction;
  current_angle = constrain(current_angle, 0, 180);
  
  if (current_angle > 180) current_angle = 180;
  if (current_angle < 0) current_angle = 0;
}

void loop(){
  unsigned long dist = pomiar();
  beep(dist);
  poruszanie(dist, last_dist);
  last_dist = dist;
  wyswietlanie(dist);
  delay(15);
}


