const int numReadings = 10;    // the number of fringes are counted every 100 readings 
const int threshold = 89;       // voltage value above this threshold would considered to be the peak voltage (i.e. 1 cycle of fringe).
                                // One peak = one cycle of fringe. 
const int wavelength = 532;     // in nanometers

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int distance = 0;               // in nanometers

int inputPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  if (analogRead(inputPin) > threshold){
    // 1 = there is a fringe
    readings[readIndex] = 1;
  }
  if (analogRead(inputPin) < threshold){
    // 0 = there is no fringe
    readings[readIndex] = 0;
  }  

  //readings[readIndex] = analogRead(inputPin);
  
  // add the reading to the total (i.e. total number of cycles of fringe):
  total = total + readings[readIndex];
  //calculate distance 
  distance = total * wavelength / 2;
  
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  
  // send it to the computer as ASCII digits
  Serial.println(distance);
  //delay(1);        // delay in between reads for stability
}
