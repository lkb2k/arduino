#include <TrinketKeyboard.h>

const int MINUTES = 1;
const int interval = 1000 * MINUTES;
unsigned long last;

void setup() {
  TrinketKeyboard.begin();
  randomSeed(analogRead(0));
  while (TrinketKeyboard.isConnected() == 0); //wait for connection
  TrinketKeyboard.println("Cock Ass Balls!");
}

void loop() {
    TrinketKeyboard.poll();
    
    if(last+interval < millis()) {
      altTab();          
      
      // 2/15 chance of cockassballs
      switch(random(1,15)) {
        case 2:
        case 3:
            cockAssBalls();          
            break;          
        default:
          randomChar();
          break;          
      }
      last = millis();
    }

    delay(5);
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

