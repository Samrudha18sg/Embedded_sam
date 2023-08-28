#include "petches.h"

const int sensor_PIN = D1; // Arduino pin connected to button's pin
const int BUZZER_PIN = D6; // Arduino pin connected to Buzzer's pin

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, 
  NOTE_A3, NOTE_G3, 0, NOTE_B3,
  NOTE_C4,NOTE_B4,NOTE_B4

};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 16, 16, 
  18, 8, 8, 
  8, 16, 16, 8
};

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(sensor_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
}

void loop() {
  int sensorState = digitalRead(sensor_PIN); // read new state

  if (sensorState == HIGH){ // button is pressed
    Serial.println("The button is being pressed");
  buzzer();
  }
}

void buzzer() {
  // iterate over the notes of the melody:
  int size = sizeof(noteDurations) / sizeof(int);

  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
 }
}
