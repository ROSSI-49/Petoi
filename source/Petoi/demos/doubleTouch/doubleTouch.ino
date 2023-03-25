#define IR_PIN    4   // Signal Pin of IR receiver to Arduino Digital Pin 4
#define BUZZER    5


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(digitalRead(6));
  Serial.print('\t');
  Serial.print(digitalRead(7));
  Serial.print('\t');
  //  Serial.print(digitalRead(6));

  //  Serial.print('\t');
  //  Serial.print(0);
  //  Serial.print('\t');
  //  Serial.print(1024);

  Serial.println();
  delay(2);
}
