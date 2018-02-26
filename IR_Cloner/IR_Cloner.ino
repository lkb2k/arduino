#include "IRLibAll.h"

//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(3);

//Create a decoder object 
IRdecode myDecoder;   

void setup() {
  Serial.begin(9600);  
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));

}

void loop() {

  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(false);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  }
}





