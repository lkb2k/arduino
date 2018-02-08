#include <TrinketKeyboard.h>

const int LED_PIN = 1;

const int interval = 1000 * 20;
unsigned long last;

void setup() {
  last = millis();
  pinMode(LED_PIN, OUTPUT);
  TrinketKeyboard.begin();
  
  randomSeed(analogRead(0));

}

void loop() {
    TrinketKeyboard.poll();
    
    if(last+interval < millis()) {
      digitalWrite(LED_PIN, HIGH); 

      // 1/15 chance of cockassballs
      switch(random(1,15)) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            randomChar();             
            break;
        case 10:
            cockAssBalls();     
            break;          
        default:
          altTab();
          break;         
      }
      last = millis();
    }
    delay(5);
    digitalWrite(LED_PIN, LOW); 
}


void randomChar() {
  TrinketKeyboard.typeChar((char)random(33, 122));  
}

void cockAssBalls() {
  TrinketKeyboard.println("Cock Ass Balls!");
}


void altTab() {
    //WINDOWS
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_TAB);
  TrinketKeyboard.pressKey(0, 0); // release keys

  //OSX
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_TAB);
  TrinketKeyboard.pressKey(0, 0); // release keys

}

