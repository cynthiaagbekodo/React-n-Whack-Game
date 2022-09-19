#include <IRremote.hpp>

const int RECV_PIN = 6;
float pressed = 0;

void setup(){
  Serial.begin(9600);
  IrReceiver.begin( RECV_PIN, true );
}

void loop(){
  if (IrReceiver.decode()){
        pressed = IrReceiver.decodedIRData.decodedRawData;
        Serial.println("Hello ");
        Serial.println(pressed);
        IrReceiver.resume();
  }
}
//  0=3910598400.00
//  1=4077715200.00
//  2=3877175040.00
//  3=2707357440.00
//  4=4144561920.00
