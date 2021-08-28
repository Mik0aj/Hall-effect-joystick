const int commonPin = 2;
const int buttonPins[] = {4,5,6,7};
unsigned long lastFire = 0;
int tolerance=20;
const int axisPins[] = {A0,A1,A2,A3};
int joystickValues[sizeof(axisPins)];


void setup() {
  configureCommon(); // Setup pins for interrupt

  attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

  Serial.begin(9600);
}

void pressInterrupt() { // ISR
  if (millis() - lastFire < 200) { // Debounce
    return;
  }
  lastFire = millis();

  configureDistinct(); // Setup pins for testing individual buttons

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) { // Test each button for press
    if (!digitalRead(buttonPins[i])) {
      press(i);
    }
  }

  configureCommon(); // Return to original state
}

void configureCommon() {
  pinMode(commonPin, INPUT_PULLUP);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], OUTPUT);
    digitalWrite(buttonPins[i], LOW);
  }
}

void configureDistinct() {
  pinMode(commonPin, OUTPUT);
  digitalWrite(commonPin, LOW);

  for (int i = 0; i < sizeof(buttonPins) / sizeof(int); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void press(int button) { // Our handler
  Serial.println(button + 1);
}

void loop() {
  for (int i = 0; i < sizeof(axisPins) / sizeof(int); i++) {
    int old=joystickValues[i];
    joystickValues[i]=analogRead(axisPins[i]);
    int diff = abs(joystickValues[i] - old);
    if(diff > tolerance)
    {
        old = joystickValues[i]; // only save if the val has changed enough to avoid slowly drifting
        // and so on
       Serial.print("axis on pin ");
       Serial.print(axisPins[i]);
       Serial.print(" ");
       Serial.println(joystickValues[i]);
    }     
  }
}
