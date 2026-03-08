int jasnosc = 5;
int krok = 5;

void setup() {
  pinMode(9, OUTPUT); // Używamy pinu 9
}

void loop() {
  analogWrite(9, jasnosc);
  jasnosc = jasnosc + krok;

  if (jasnosc <= 0 || jasnosc >= 255) {
    krok = -krok; // Zmiana znaku (np. z 5 na -5)
  }
  
  // put your main code here, to run repeatedly:
delay(3);
  }
