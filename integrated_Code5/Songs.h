#pragma once

#include <Arduino.h>
#include <Buzzer.h>

namespace Songs {
  void playStarWarsTheme(Buzzer& buzzer) {
    buzzer.begin(10);

    buzzer.sound(NOTE_A3, 500); 
    buzzer.sound(NOTE_A3, 500);
    buzzer.sound(NOTE_A3, 500);
    buzzer.sound(NOTE_F3, 375);
    buzzer.sound(NOTE_C4, 125);

    buzzer.sound(NOTE_A3, 500);
    buzzer.sound(NOTE_F3, 375);
    buzzer.sound(NOTE_C4, 125);
    buzzer.sound(NOTE_A3, 1000);

    buzzer.sound(NOTE_E4, 500); 
    buzzer.sound(NOTE_E4, 500);
    buzzer.sound(NOTE_E4, 500);
    buzzer.sound(NOTE_F4, 375);
    buzzer.sound(NOTE_C4, 125);

    buzzer.sound(NOTE_GS3, 500);
    buzzer.sound(NOTE_F3, 375);
    buzzer.sound(NOTE_C4, 125);
    buzzer.sound(NOTE_A3, 1000);

    buzzer.end(100);
  }

  void playMarioTheme(Buzzer& buzzer) {
    buzzer.begin(100);

    buzzer.sound(NOTE_E7, 80);
    buzzer.sound(NOTE_E7, 80);
    buzzer.sound(0, 80);
    buzzer.sound(NOTE_E7, 80);
    buzzer.sound(0, 80);
    buzzer.sound(NOTE_C7, 80);
    buzzer.sound(NOTE_E7, 80);
    buzzer.sound(0, 80);
    buzzer.sound(NOTE_G7, 80);
    buzzer.sound(0, 240);
    buzzer.sound(NOTE_G6, 80);
    buzzer.sound(0, 240);
  
    buzzer.end(100);
  }
};