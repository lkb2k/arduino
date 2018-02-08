#include <TrinketKeyboard.h>

#define PIN_BUTTON_CAPITAL_A 0
int led = 1;
bool wasPressed = false;

void setup() {
  pinMode(PIN_BUTTON_CAPITAL_A, INPUT);
  digitalWrite(PIN_BUTTON_CAPITAL_A, HIGH);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll();
  bool isPressed = digitalRead(PIN_BUTTON_CAPITAL_A) == LOW;

  if (isPressed && !wasPressed) {
    wasPressed = true;
    digitalWrite(led, HIGH);
    TrinketKeyboard.pressKey(KEYCODE_MOD_RIGHT_GUI, KEYCODE_BACKSLASH);
    TrinketKeyboard.pressKey(0, 0);
  }

  if (!isPressed) {
    wasPressed = false;
    digitalWrite(led, LOW);
  }

}
