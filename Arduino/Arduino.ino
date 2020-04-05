// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
}

float wheelDiam = 0.000622;
bool sensorFound = false;
float totalMileage = 0;
long rotations = 0;

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(voltage);
  updateMileageTest(voltage);
}

void updateMileageTest(float voltage) {
  // Check if the sensor was previously found and if the current voltage is >0.5 and < 2 i.e. sensed
  if((voltage >= 3.1) && sensorFound == false) {
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

  if (voltage < 3.1) {
    // If voltage < 0.5 then the sensor isn't present and therefore no rotations
    // have taken place since the last time it was checked and therefore no maths is required
    sensorFound = false;
  }
}

void updateMileage(float voltage) {
  // Check if the sensor was previously found and if the current voltage is >0.5 and < 2 i.e. sensed
  if((voltage >= 0.5 && voltage < 2) && sensorFound == false) {
    // A single rotation has taken place since the last rotation
    sensorFound = true;
    totalMileage += wheelDiam;
  }

  if (voltage < 0.5) {
    // If voltage < 0.5 then the sensor isn't present and therefore no rotations
    // have taken place since the last time it was checked and therefore no maths is required
    sensorFound = false;
  }
}
