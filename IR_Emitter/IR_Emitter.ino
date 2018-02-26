#include <IRLibAll.h>

const long PWR = 0x40be629d;
const long MENU = 0x40bee21d;
const long ZERO = 0x40be00ff;
const long DOWN = 0x40be00ff;
const long UP = 0x40be12ed;

const long LEFT = 0x40be728d;
const long RIGHT = 0x40be926d;
const long OK = 0x40be52ad;


const int BUTTON = 5;

IRsendNEC mySender;
int buttonState = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(BUTTON, INPUT);
  

}

void loop() {
  buttonState = digitalRead(BUTTON);

  if (buttonState == HIGH) {
    flipHeight();
  }
}

void flipHeight() {
  Serial.println("sending signal");
  mySender.send(MENU);

  for (int i = 0; i < 4; i++) {
    mySender.send(0xffffffff);
    mySender.send(ZERO);
  }
  mySender.send(0xffffffff);
  mySender.send(UP);
  mySender.send(0xffffffff);
  mySender.send(OK);
  mySender.send(0xffffffff);
  for (int i = 0; i < 5; i++) {
    mySender.send(0xffffffff);
    mySender.send(UP);
  }
  mySender.send(0xffffffff);
  mySender.send(OK);
  mySender.send(0xffffffff);
  mySender.send(UP);
  mySender.send(0xffffffff);
  mySender.send(LEFT);
  mySender.send(0xffffffff);
  mySender.send(OK);

  for (int i = 0; i < 4; i++) {
    mySender.send(0xffffffff);
    mySender.send(MENU);
  }
  mySender.send(0xffffffff);
  Serial.println("done sending signal");
}

