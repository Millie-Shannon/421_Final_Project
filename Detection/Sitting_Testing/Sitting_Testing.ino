#include <Adafruit_CircuitPlayground.h>
// define variables
int nopress = 0;
int lightpin = 2;
int mode;   
int tsit = 0;
int tsleep  =  0;
int sleepdur = 0;
int relaypin = 9;  
int ledState = 0;
int x = 0; 
int sleepArray[7] ;
int n = 1;
int state = 0; 
int i;
int inByte = 0;
int nosit = 0; 

//tones for sitting use case alarm
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();
pinMode(lightpin, OUTPUT);
digitalWrite(lightpin, LOW); 
pinMode(relaypin, OUTPUT);
digitalWrite(relaypin, LOW);
}

void loop() {
  int sensorValue = analogRead(A10);        // pressure sensor input

  mode = CircuitPlayground.slideSwitch();   // mode defines use case (+ is sitting, - is sleeping)


//Slide Switch + (Mode 1): Sitting Case 
  if (mode == 1 && sensorValue > 100) {     // when presence is detected, begin counting
    delay(1000); // detects for presence every 1 second
    tsit = tsit + 1;
    nosit = 0; 
  }
  
  if (mode == 1 && sensorValue < 100) {     // resets counter when user has gotten up
    delay(1000);
    nosit = nosit + 1; 
 //   tsit = 0;    
  }

  if (mode == 1 && nosit > 5 && sensorValue < 100) {
    tsit = 0; 
  }

Serial.println("Tsit");
Serial.println(tsit);
Serial.println("Nosit");
Serial.println(nosit);
// notification system that user has been sitting for too long
  if (mode == 1 && tsit > 5 && ledState == 0 && sensorValue > 100) {     // if seated for too long,
    CircuitPlayground.setPixelColor(0,200,200,0);   // lights on circuit playground will blink
    CircuitPlayground.setPixelColor(2,150,250,50);    // (if lights off, they will turn on)
    CircuitPlayground.setPixelColor(4,100,100,100);
    CircuitPlayground.setPixelColor(6,50,20,170);
    CircuitPlayground.setPixelColor(8,0,100,250);
    delay(500);   
    ledState = 1; 
  } 
  if (mode == 1 && tsit > 5 && ledState == 1 && sensorValue > 100) {     // (if lights on, they will turn off)
    CircuitPlayground.clearPixels();
    ledState = 0;
    delay(100); 
  }
  
x = tsit % 5;                                       // after every 5 cycles of blinking lights
  if (mode == 1 && x == 0 && tsit > 10 && sensorValue > 100) {           // tones will play serving as an alarm
    CircuitPlayground.playTone(NOTE_C4, 1100);      
    //delay(100);
    CircuitPlayground.playTone(NOTE_E4, 1100);
    //delay(100);
    CircuitPlayground.playTone(NOTE_G4, 1100);
    //delay(5000);
  }
  //Serial.println(ledState);
  //Serial.println(tsit);
} 
