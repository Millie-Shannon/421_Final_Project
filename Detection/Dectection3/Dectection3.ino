#include <Adafruit_CircuitPlayground.h>
int nopress = 0;
int lightpin = 2;
int mode;   
int tsit = 0;
int tsleep  =  0;
int sleepdur = 0;
int relaypin = 9;  
int ledState = 0;
int x = 0; 
int sleepArray[6] = {1,2,3,4,5,6};
int Analogue0 = 100;
int Analogue1 = 100;
int Analogue2 = 10;
int Analogue3 = 50;
int Analogue4 = 100;
int Analogue5 = 255;
int n = 0;
int state = 0; 
int i;
int inByte = 0;


#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
CircuitPlayground.begin();
establishContact();
pinMode(lightpin, OUTPUT);
digitalWrite(lightpin, LOW); 
pinMode(relaypin, OUTPUT);
digitalWrite(relaypin, LOW);
}

void loop() {
  int sensorValue = analogRead(A10);
  //Serial.println(sensorValue);
  // put your main code here, to run repeatedly:
  mode = CircuitPlayground.slideSwitch();
  delay(200);

//SlideSwitch - (Mode 0)> Sleeping Case
  if (mode == 0 && sensorValue < 100 && state ==0) {
    nopress = nopress + 1;
    //Serial.println(nopress);
  }
  if (mode == 0 && sensorValue > 100) {
    tsleep = tsleep + 1;
    //Serial.println(tsleep);
    state = 0; 
  }
  if (mode == 0 &&  nopress > 10 && state == 0) {
    //Serial.println("I'm awake!"); 
    delay(200); 
    digitalWrite(lightpin,HIGH);
    digitalWrite(relaypin,HIGH);
    CircuitPlayground.setPixelColor(0,200,200,0);
    sleepdur = tsleep/2; //3600 seconds in an hour
                          //counts duration of sleep in hours
    //Serial.println(sleepdur);
  }

 /* if (mode == 0 && nopress == 10) {
    sleepArray[n] = sleepdur;
    n = n+1;
  }
    //Serial.println(sleepdur); 
*/
 // if (CircuitPlayground.rightButton() == 1) { 
    if (Serial.available() > 0) {
     // get incoming byte:
     inByte = Serial.read();
    //for (i = 0; i < 3; i++) {
    // Serial.write(sleepArray[i]);
    //  }
     Serial.write(Analogue0 );
     Serial.write(Analogue1 );
     Serial.write(Analogue2 );
     Serial.write(Analogue3 );
     Serial.write(Analogue4 );
     Serial.write(Analogue5 );
    }
 // }

  if (CircuitPlayground.leftButton() == 1 || CircuitPlayground.rightButton() == 1) {
    digitalWrite(lightpin,LOW);
    digitalWrite(relaypin,LOW);
    nopress = 0;    
    tsleep = 0; 
    state = 1; 
  }


//Slide Switch + (Mode 1): Sitting Case 
  if (mode == 1 && sensorValue > 100) {
    delay(1000); // detects for presence every 1 second
    tsit = tsit + 1;
  }
  if (mode == 1 && tsit >= 5) { // every 10 seconds of continuous sitting delivers notification 
    //Serial.println("Get up and go stretch");
  }   
  if (mode == 1 && sensorValue < 100) {
    delay(1000);
    tsit = 0;    
  }

  if (mode == 1 && tsit > 5 && ledState == 0) {
    CircuitPlayground.setPixelColor(0,200,200,0);
    CircuitPlayground.setPixelColor(2,150,250,50);
    CircuitPlayground.setPixelColor(4,100,100,100);
    CircuitPlayground.setPixelColor(6,50,20,170);
    CircuitPlayground.setPixelColor(8,0,100,250);
    delay(500);   
    ledState = 1; 
  } 
  if (mode == 1 && tsit > 5 && ledState == 1) {
    CircuitPlayground.clearPixels();
    ledState = 0;
    delay(100); 
  }
x = tsit % 5; 
  if (mode == 1 && x == 0 && tsit > 10) {
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

