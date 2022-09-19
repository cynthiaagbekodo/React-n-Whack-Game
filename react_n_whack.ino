/*
  Embedded Systems Design 
  Arduino Project
*/

#include <LiquidCrystal.h>  // library for LCD character display
#include <IRremote.h>       // IRremote library for IR remote
#include <avr/io.h>         // import avr library for registers
#include <avr/interrupt.h>  // import avr library for interrupt function

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Arduino pin numbers for LCD
const byte ledGreen_pin = 7; 
const byte ledYellow_pin = 8; 
const byte ledRed_pin = 9; 
const byte ledBlue_pin = 10; 
const byte emtpin = A0;
const byte IRreceive = 6; 
float IRpressed = 000;

bool correct = false;
int score = 0;
unsigned long refTime; 
unsigned long tempTime;
unsigned long endTime; 
unsigned long reactTime; 
const byte ledintur = 9; 

//int interrupt = 2;    // Arduino pin number for interrupts

/*******************************************************************************/
void setup() {
//  Serial.begin(9600);
  lcd.begin(16,2); // set up A 16byte x 2 LCD
  IrReceiver.begin(IRreceive, true);
  randomSeed(analogRead(emtpin));
  pinMode(ledBlue_pin, OUTPUT);
  pinMode(ledGreen_pin, OUTPUT);
  pinMode(ledYellow_pin, OUTPUT);
  pinMode(ledRed_pin, OUTPUT);

  
//  pinMode(ledintur, OUTPUT);
//  pinMode(interruptPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

//  int OCR_2sec = 31249; 
//  int OCR_4sec = 62499;            
//  int OCR_10sec = 156249;
//  /* Configure interrupt on Timer1 */
//  cli();            // disable global interrupts before configuring interrupt 
//  TCCR1A = 0;       // set TCCR1A register to 00000000
//  TCCR1B = 0;       // set TCCR1B register to 00000000
//  OCR1A = 15624;   // set compare match register
//  /*Notice: (x+1)*1/16e6*1024 = desired seconds*/
//  TCCR1B |= (1 << WGM12);             // Set WGM12 bit to 1, turns on CTC mode:
//  TCCR1B |= (1 << CS12)|(1 << CS10);  // Set CS10 and CS12 bits to 1
//  /* Notice that When CS12=1, CS11=0 and CS12=1, pre-scaler is 1024 */
//  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt:
//  sei(); // enable global interrupts after configured interrupt
  
}

//ISR(TIMER1_COMPA_vect){ 
//  digitalWrite(ledintur, !digitalRead(ledintur)); 
////  lcd.clear();
////  lcd.setCursor(0, 0);
////  lcd.print("TimeOut!");
//}

/*******************************************************************************/
void loop() {     
//  Game Selection: Uncomment to pick a mode
    reactiontimer(); 
//    whackamole();
}

/*******************************************************************************/
void reactiontimer() {
  //Code for Part 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Timer");
  delay(random(2000, 4001)); //waits for 2-4sec
  digitalWrite(ledBlue_pin, HIGH); 
  
  refTime = millis(); 
  while(IrReceiver.decode() == false) {
     tempTime = millis()-refTime;
     if (tempTime >= 10000) {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Time Out!");
       delay(3000);
       break;
     }
  } 
  
  IRpressed = IrReceiver.decodedIRData.decodedRawData;
  IrReceiver.resume();
  //  0 = 3910598400.00
  //  1 = 4077715200.00
  //  2 = 3877175040.00
  //  3 = 2707357440.00
  //  4 = 4144561920.00
  endTime = millis(); 
  reactTime = endTime-refTime;
  digitalWrite(ledBlue_pin, LOW);

  //If User Pressed 0 On Remote
  if (IRpressed == 3910598400.00) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reaction Time:");
    lcd.setCursor(0, 1);
    lcd.print(reactTime);
    delay(3000);
  }
  else if (tempTime < 10000){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong button!");
    delay(3000);
    }
}

/*******************************************************************************/
void whackamole() {
  //Code for Part 2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Whack a Mole");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Ready, ");
  delay(500);
  lcd.print("Set, ");
  delay(500);
  lcd.print("Go!");

  bool playing = true;
  score = 0;
  while(playing) {
      delay(random(2000, 5001)); 
      //Selects Random LED to Turn ON
      int ledselect = random(1,5); 
      switch (ledselect) {
        case 1:
          digitalWrite(ledGreen_pin, HIGH);
          break;
        case 2:
          digitalWrite(ledYellow_pin, HIGH);
          break;
        case 3:
          digitalWrite(ledRed_pin, HIGH);
          break;
        case 4:
          digitalWrite(ledBlue_pin, HIGH);
          break;
        }  
//      Serial.println("~~~~~~~~~");
//      Serial.println(IRpressed);
      refTime = millis(); 
      while(IrReceiver.decode() == false) {
           tempTime = millis()-refTime;
           if (tempTime >= 2000) {
             lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print("Time Out!");
             delay(3000);
             correct = false;
             break;
           }
        }
      if (tempTime < 2000) {
        IRpressed = IrReceiver.decodedIRData.decodedRawData;
//        Serial.println(IRpressed);
      }
      else {
        IRpressed = 000;
      }
//      Serial.println(IRpressed);
      IrReceiver.resume();
      //  0 = 3910598400.00
      //  1 = 4077715200.00
      //  2 = 3877175040.00
      //  3 = 2707357440.00
      //  4 = 4144561920.00
      digitalWrite(ledGreen_pin, LOW);
      digitalWrite(ledYellow_pin, LOW);
      digitalWrite(ledRed_pin, LOW);
      digitalWrite(ledBlue_pin, LOW);

  
      //Check if User Pressed Correcly
      if (IRpressed == 4077715200.00 and ledselect == 1) {
        //Green LED is ON and User Pressed 1 on Remote
        correct = true;
      }
      else if (IRpressed == 3877175040.00 and ledselect == 2) {
        //Yellow LED is ON and User Pressed 2 on Remote
        correct = true;
      }
      else if (IRpressed == 2707357440.00 and ledselect == 3) {
        //Red LED is ON and User Pressed 3 on Remote
        correct = true;
      }
      else if (IRpressed == 4144561920.00 and ledselect == 4) {
        //Blue LED is ON and User Pressed 4 on Remote
        correct = true;
      }
      else {
        correct = false;
      }
  
      //Check if we keep playing
      if (correct) {
        score++;
      }
      else {
        playing = false;
      }
  } 

  if (tempTime < 2000){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Incorrect!");
    delay(3000);
  }
  lcd.clear();
  lcd.print("Final score:");lcd.print(score);
  delay(3000);
  lcd.clear();
  lcd.print("Restarting...");
  delay(3000);
}
