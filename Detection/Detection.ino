int nopress = 0; 
// int dn2 = 0; 
const int lightpin = 2;
// int relaypin = 10;  
int lightpin_input = 10; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(lightpin, OUTPUT);
digitalWrite(lightpin, LOW); 
//pinMode(relaypin, OUTPUT);
//digitalWrite(relaypin, LOW);
pinMode(lightpin_input, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(10);
  Serial.println(sensorValue); 
  delay(200); 

  if (sensorValue <= 5) {
    nopress = nopress + 1; 
    //Serial.println(nopress);
  } 

   
  if (nopress >= 10) {
  //Serial.println("I'm awake!"); 
  delay(200); 
  digitalWrite(lightpin,HIGH);
 // digitalWrite(relaypin,HIGH); 
//  dn2 = 0; 
  }
  if (nopress < 10) {
 // Serial.println("I'm still asleep.");
  delay(200);  
  digitalWrite(lightpin,LOW);
 }   

//  if (dn >= 10 && sensorValue != 0)  {
//  dn2 = dn2 + 1; 
//  Serial.println(dn2); 
// }
//  if (dn2 >= 10) {
//  Serial.println("I'm still asleep."); 
//  digitalWrite(lightpin,LOW); 
//  dn = 0; 
//  } 
    
}

