/*
  Pitch follower

  Plays a pitch that changes based on a changing analog input

  circuit:
  - 8 ohm speaker on digital pin 9
  - photoresistor on analog 0 to 5V
  - 4.7 kilohm resistor on analog 0 to ground

  created 21 Jan 2010
  modified 31 May 2012
  by Tom Igoe, with suggestion from Michael Flynn

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/tonePitchFollower
*/

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(115200);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A2);
  // print the sensor reading so you know its range
  Serial.print(sensorReading);
  // map the analog input range (in this case, 400 - 1000 from the photoresistor)
  // to the output pitch range (120 - 1500Hz)
  // change the minimum and maximum input numbers below depending on the range
  // your sensor's giving:
  int thisPitch = map(sensorReading, 400, 1000, 120, 1500);

  // play the pitch:
  tone(5, thisPitch, 100);
  Serial.print('\t');
  Serial.print(0);
  Serial.print('\t');
  Serial.println(1024);
  delay(50);        // delay in between reads for stability
}
