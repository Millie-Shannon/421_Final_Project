#include <Adafruit_CircuitPlayground.h>
int nopress = 0;
int lightpin = 2;
int mode;   
int tsit = 0;
int tsleep  =  0;
int sleepdur = 0;
int relaypin = 9;  


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
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
  if (mode == 1 && tsit >= 10) { // every 10 seconds of continuous sitting delivers notification 
    Serial.println("Get up and go stretch");
  }   
  if (mode == 1 && sensorValue < 100) {
    delay(1000);
    tsit = 0;    
  }
  Serial.println(tsit);
}
