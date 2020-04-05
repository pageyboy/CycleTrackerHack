// the setup routine runs once when you press reset:

float wheelDiam = 0.000622;
bool sensorFound = false;
float totalMileage = 0;
long rotations = 0;
const int buttonPin = 2;
const int ledPin =  13; 

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int buttonState = digitalRead(buttonPin);
  updateMileageTest(buttonState);
}

void updateMileageTest(int buttonState) {

  if(buttonState == HIGH && sensorFound == false) {
    // A single rotation has taken place since the last rotation
    sensorFound = true;
    totalMileage += wheelDiam;
    rotations++;
    char str[6];
    Serial.print(dtostrf(totalMileage, 5, 4, str));
    Serial.print(" km ");
    Serial.print(rotations);
    Serial.println(" rotations");
  }

  if (buttonState == LOW) {
     sensorFound = false;
  }
}
