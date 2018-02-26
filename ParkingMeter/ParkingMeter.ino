/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define RX_PIN 2 // Arduino receive   GREEN WIRE   labeled TX on printer
#define TX_PIN 3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define GD_PIN 4 // use for ground

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

int ledPin = 13; // choose the pin for the LED
boolean buttonStates[7] = {0,0,0,0,0,0,0};


String places[7]  = {
  "Coyote Point $1.00",
  "The Lodge $7",
  "Montreal $4",
  "Halifax NS $10",
  "Sydney AU $5.00",
  "Colma BART $11",
  "Passport Office $15"
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
      pinMode(i + 5, INPUT);
  }
  
  pinMode(GD_PIN, OUTPUT); 
  digitalWrite(GD_PIN, LOW);

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)

  pinMode(ledPin, OUTPUT);  // declare LED as output

  sendToPrinter("Where do you want to go?");
  resetPrinter();
}

void loop() {
  bool allOff = true;
  for (int i = 0; i < 7; i++) {
    int buttonState = digitalRead(i + 5);
    
    if (buttonState == HIGH && !buttonStates[i]) {
      buttonStates[i] = true;
      Serial.print("button pressed: ");
      Serial.println(i);
      digitalWrite(ledPin, HIGH);
      sendToPrinter(places[i]);
      printBarcode("OLIVERK");
      resetPrinter();
      allOff = false;
      break;
    }else{
      buttonStates[i] = false;
    }
  }

  if (allOff) {
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}



void sendToPrinter(String line) {
  Serial.println(line);
  printer.boldOn();
  printer.setSize('L');
  printer.justify('L');
  printer.println(line);

}

void printBarcode(String line) {

  printer.setDefault(); // Restore printer to defaults
  //  printer.setBarcodeHeight(100);
  printer.printBarcode("OLIVERK", CODE39);

}

void resetPrinter() {

  printer.feed(4);
  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}

