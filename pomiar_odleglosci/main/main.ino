
const int BUTTON = 8;
const int LED = 9;
const int TRIG_PIN = 11;
const int ECHO_PIN = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void loop()
{
  if (digitalRead(BUTTON) == LOW)  // wciśnięty
  {
    float Time;
    float Distance;

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    Time = pulseIn(ECHO_PIN, HIGH);
    Distance = Time / 58;

    Serial.print("dystans: ");
    Serial.print(Distance);
    Serial.println("cm");
    digitalWrite(LED, HIGH);
    delay(100);
  } 
  else
  {
    digitalWrite(LED, LOW);
  }
}