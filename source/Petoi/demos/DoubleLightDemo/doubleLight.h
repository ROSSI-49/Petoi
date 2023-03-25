#define LIGHT1 A2
#define LIGHT2 A3
#define BUZZER 5
#define READING_COUNT 30

#define IN1 LIGHT1
#define IN2 LIGHT2
#define MAX_READING 1024

int meanA = 0, meanB = 0, diffA_B = 0;
int tolerance = 20;

void readSensor(int * result) {
  int a = analogRead(IN1) - meanA;
  int b = analogRead(IN2) - meanB;
  int offset = b - a;
  result[0] = max(a, b);
  result[1] = min(max(offset, -60), 60);
  //  Serial.print(MAX_READING);
  //  Serial.print('\t');
  //  Serial.print(0);
  //  Serial.print('\t');
  //  Serial.print(a);
  //  Serial.print('\t');
  //  Serial.print(b);
  //  Serial.print('\t');
  //  Serial.print(offset);
  //  Serial.println();
  delayMicroseconds(50);
  //  return result;
}

void sensorSetup() {
  // put your setup code here, to run once:
  for (int i = 0; i < READING_COUNT; i++) {
    int a = analogRead(IN1);
    int b = analogRead(IN2);
    meanA += (a / READING_COUNT);
    meanB += (b / READING_COUNT);
    diffA_B += (a - b) / READING_COUNT;
    delay(1);
  }

  //  resetReading();
}

//void loop() {
//  bool con = readSensor(READING_COUNT);
//  //  Serial.println(con);
//  //  con ? beep(10, 200) : beep(20, 200);
//}
