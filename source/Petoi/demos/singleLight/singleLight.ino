#define IR_PIN    4   // Signal Pin of IR receiver to Arduino Digital Pin 4
#define BUZZER    5


//Sensitivity and saturation
//Threshold and binarization
//Analog and digital data
//DigitalRead(): analog pins allow digital read
//Changes in the environment
//Patterns: rock scissors cloth
//Scanning

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading1 = analogRead(A2);
  int reading2 = digitalRead(A2);
  Serial.print(reading1);
  Serial.print('\t');
  Serial.print(reading2);
  Serial.print('\t');
  //  Serial.print(digitalRead(6));

//  Serial.print('\t');
//  Serial.print(0);
//  Serial.print('\t');
//  Serial.print(1024);
//  Serial.print('\t');
//  if (reading > 10)
//    Serial.print("1\tbright");
//  else
//    Serial.print("0\tdark");

  Serial.println();
  delay(2);
}
