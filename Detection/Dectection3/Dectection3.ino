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

//tones for sitting use case alarm
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392

void setup() {
Serial.begin(9600);
CircuitPlayground.begin();
establishContact();
pinMode(lightpin, OUTPUT);
digitalWrite(lightpin, LOW); 
pinMode(relaypin, OUTPUT);
digitalWrite(relaypin, LOW);
}

void loop() {
  int sensorValue = analogRead(A10);        // pressure sensor input

  mode = CircuitPlayground.slideSwitch();   // mode defines use case (+ is sitting, - is sleeping)
  delay(200);

//SlideSwitch - (Mode 0)> Sleeping Case
  if (mode == 0 && sensorValue < 100 && state ==0) {
    nopress = nopress + 1;                  // counts relative duration of no sleep presence
  }
  
  if (mode == 0 && sensorValue > 100) {
    tsleep = tsleep + 1;                    // counts relative duration of sleep presence
    state = 0;                              // state 0 is actived sensor
                                            // state 1 is inactived sensor (used for resetting purposes) 
  }
  
  if (mode == 0 &&  nopress > 10 && state == 0) {   // when no presence is detected for a significant duration
    delay(200); 
    digitalWrite(lightpin,HIGH);            // turn lights on
    digitalWrite(relaypin,HIGH);          
    CircuitPlayground.setPixelColor(0,200,200,0);
    sleepdur = tsleep/2;                    //3600 seconds in an hour
                                            //counts duration of sleep in hours
    //Serial.println(sleepdur);
  }

  if (mode == 0 && nopress == 11 && n != 9) {    // store our new sleep duration to new index in vector 
    sleepArray[n-1] = sleepdur;
    n = n+1;
  }

    
  if (mode == 0 && nopress == 11 && n == 9) {   // once the vector is full, shift current duration values 
                                                // into previous index and add new duration value
    sleepArray[0] = sleepArray[1];
    sleepArray[1] = sleepArray[2];
    sleepArray[2] = sleepArray[3];
    sleepArray[3] = sleepArray[4];
    sleepArray[4] = sleepArray[5];
    sleepArray[5] = sleepArray[6];
    sleepArray[6] = sleepdur;
//    sleepArray[7] = sleepArray[8];
//    sleepArray[8] = sleepdur;
  }
    //Serial.println(sleepdur); 

 // if (CircuitPlayground.rightButton() == 1) { 
    if (Serial.available() > 0) {             // send duration array to Processing
     // get incoming byte:
     inByte = Serial.read();
     Serial.write(sleepArray[0]);
     Serial.write(sleepArray[1]);
     Serial.write(sleepArray[2]);
     Serial.write(sleepArray[3]);
     Serial.write(sleepArray[4]);
     Serial.write(sleepArray[5]);
     Serial.write(sleepArray[6]);
//     Serial.write(sleepArray[7]); 
    }

  if (CircuitPlayground.leftButton() == 1 || CircuitPlayground.rightButton() == 1) {
                                            // pressing button resets system
    digitalWrite(lightpin,LOW);             // turns off lights
    digitalWrite(relaypin,LOW);             // turns off kettle or relay switch
    nopress = 0;                            // resets counters
    tsleep = 0; 
    state = 1;                              // doesn't allow reactivation until presence is re-detected
  }

//Slide Switch + (Mode 1): Sitting Case 
  if (mode == 1 && sensorValue > 100) {     // when presence is detected, begin counting
    delay(1000); // detects for presence every 1 second
    tsit = tsit + 1;
  }
  
  if (mode == 1 && sensorValue < 100) {     // resets counter when user has gotten up
    delay(1000);
    tsit = 0;    
  }

// notification system that user has been sitting for too long
  if (mode == 1 && tsit > 5 && ledState == 0) {     // if seated for too long,
    CircuitPlayground.setPixelColor(0,200,200,0);   // lights on circuit playground will blink
    CircuitPlayground.setPixelColor(2,150,250,50);    // (if lights off, they will turn on)
    CircuitPlayground.setPixelColor(4,100,100,100);
    CircuitPlayground.setPixelColor(6,50,20,170);
    CircuitPlayground.setPixelColor(8,0,100,250);
    delay(500);   
    ledState = 1; 
  } 
  if (mode == 1 && tsit > 5 && ledState == 1) {     // (if lights on, they will turn off)
    CircuitPlayground.clearPixels();
    ledState = 0;
    delay(100); 
  }
  
x = tsit % 5;                                       // after every 5 cycles of blinking lights
  if (mode == 1 && x == 0 && tsit > 10) {           // tones will play serving as an alarm
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

void establishContact() {
 while (Serial.available() <= 0) {
 Serial.write('A'); // send a capital A
 delay(300);
 }
}

