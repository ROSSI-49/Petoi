/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>
#include "pitches.h"

#define BUZZER 5
#define IR_RECEIVE_PIN 4

IRrecv irrecv(IR_RECEIVE_PIN);

decode_results results;

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
};

void setup() {

  Serial.begin(115200);

  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xFFA25D: tone(BUZZER, notes[0], 200); break;
      case 0xFF22DD: tone(BUZZER, notes[1], 200); break;
      case 0xFFE01F: tone(BUZZER, notes[2], 200); break;
      case 0xFF6897: tone(BUZZER, notes[3], 200); break;
      case 0xFF30CF: tone(BUZZER, notes[4], 200); break;
      case 0xFF10EF: tone(BUZZER, notes[5], 200); break;
      case 0xFF42BD: tone(BUZZER, notes[6], 200); break;
      
      case 0xFF629D: tone(BUZZER, notes[7], 200); break;
      case 0xFF02FD: tone(BUZZER, notes[8], 200); break;
      case 0xFFA857: tone(BUZZER, notes[9], 200); break;
      case 0xFF9867: tone(BUZZER, notes[10], 200); break;
      case 0xFF18E7: tone(BUZZER, notes[11], 200); break;
      case 0xFF38C7: tone(BUZZER, notes[12], 200); break;
      case 0xFF4AB5: tone(BUZZER, notes[13], 200); break;

    }

    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
