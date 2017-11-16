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

#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(lightpin, OUTPUT);
digitalWrite(lightpin, LOW); 
pinMode(relaypin, OUTPUT);
digitalWrite(relaypin, LOW);
CircuitPlayground.begin();
}

void loop() {
  int sensorValue = analogRead(A10);
  //Serial.println(sensorValue);
  // put your main code here, to run repeatedly:
  mode = CircuitPlayground.slideSwitch();
  delay(200);

//SlideSwitch - (Mode 0)> Sleeping Case
  if (mode == 0 && sensorValue < 100) {
    nopress = nopress + 1;
    //Serial.println(nopress);
  }
  if (mode == 0 && sensorValue > 100) {
    tsleep = tsleep + 1;
    //Serial.println(tsleep);
  }
  if (mode == 0 &&  nopress > 10) {
    Serial.println("I'm awake!"); 
    delay(200); 
    digitalWrite(lightpin,HIGH);
    digitalWrite(relaypin,HIGH);
    sleepdur = tsleep/10; //3600 seconds in an hour
                          //counts duration of sleep in hours
    //Serial.println(sleepdur);
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
  Serial.println(ledState);
  //Serial.println(tsit);

}

