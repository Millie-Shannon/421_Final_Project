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
int sleepArray[8] ;
int n = 1;
int state = 0; 
int i;
int inByte = 0;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
CircuitPlayground.begin();
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
  delay(1000);

//SlideSwitch - (Mode 0)> Sleeping Case
  if (mode == 0 && sensorValue < 100 && state ==0) {
    nopress = nopress + 1;
    //Serial.println(nopress);
  }
  if (mode == 0 && sensorValue > 100) {
    tsleep = tsleep + 1;
    Serial.println(tsleep);
    state = 0; 
  }
  if (mode == 0 &&  nopress > 3 && state == 0) {
    //Serial.println("I'm awake!"); 
    delay(200); 
    digitalWrite(lightpin,HIGH);
    digitalWrite(relaypin,HIGH);
    CircuitPlayground.setPixelColor(0,200,200,0);
    sleepdur = tsleep; //3600 seconds in an hour
                          //counts duration of sleep in hours
    //Serial.println(sleepdur);
  }

  if (mode == 0 && nopress == 10 && n < 9) {
    sleepArray[n-1] = sleepdur;
    n = n+1;
  }
//Serial.println(n);

  if (mode == 0 && nopress == 10 && n == 9) {
    sleepArray[0] = sleepArray[1];
    sleepArray[1] = sleepArray[2];
    sleepArray[2] = sleepArray[3];
    sleepArray[3] = sleepArray[4];
    sleepArray[4] = sleepArray[5];
    sleepArray[5] = sleepArray[6];
    sleepArray[6] = sleepArray[7];
    sleepArray[7] = sleepArray[8];
    sleepArray[8] = sleepdur;
  }
/*
  if (CircuitPlayground.rightButton() == 1) {
    Serial.println("ARRAY!!");
    for(int i=0; i<8; ++i){
      Serial.println(sleepArray[i]);
    }
  }
 */

    //Serial.println(sleepdur); 



  if (CircuitPlayground.leftButton() == 1) {
    digitalWrite(lightpin,LOW);
    digitalWrite(relaypin,LOW);
    nopress = 0;    
    tsleep = 0; 
    state = 1; 
  }

}

