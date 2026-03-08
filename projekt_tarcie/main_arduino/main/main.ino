const int treshold = 20;
const int hallPin = A1;
const unsigned long interval = 15000;

volatile unsigned long pulses = 0;

bool aboveTreshold = false;
unsigned long lastTime = 0;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  
  Serial.println("czas_ms, voltage, rpm");
}

void loop(){
  unsigned long now = millis();

  int pot = analogRead(A0);
  int pwm = map(pot, 0, 1023, 0, 255);
  analogWrite(3, pwm);

  int hallValue = analogRead(hallPin);
  float voltage = 5.0 * pot / 1023.0;

  bool valid_range = (hallValue < 510 - treshold || hallValue > 510 + treshold);
  if (valid_range && !aboveTreshold){
    pulses++;
    aboveTreshold = true;
  }
  
  if(!valid_range){
    aboveTreshold = false;
  }

  if (now - lastTime >= interval){
    unsigned long count = pulses;
    pulses = 0;

    float rpm = count * 4;
    Serial.print(now);
    Serial.print(",");
    Serial.print(voltage);
    Serial.print(",");
    Serial.println(rpm);
    
    lastTime = now;
  }
}