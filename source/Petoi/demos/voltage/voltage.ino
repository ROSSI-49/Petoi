#define VOLTAGE_DETECTION_PIN A7 //voltage detector
#define IR_PIN    4   // Signal Pin of IR receiver to Arduino Digital Pin 4
#define BUZZER    5

//Multimeter and oscilloscope
//AnalogRead()
//Sampling method and sampling rate

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int voltage = analogRead(VOLTAGE_DETECTION_PIN);
  Serial.print(voltage);

  //  Serial.print('\t');
  //  Serial.print(voltage / 99.0);
  //  Serial.print('V');
  Serial.print('\t');
  Serial.print(0);
  Serial.print('\t');
  Serial.print(1024);

  Serial.println();
  delay(10);

}
