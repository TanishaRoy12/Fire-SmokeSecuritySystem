#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);
#define FAN 9
#define smokepin A1
const int ledpin=13;
const int buzpin=11;
const int flamepin=A2;
//const int smokepin=A1;
const int threshold=500;// sets threshold value for flame sensor
int flamesensvalue=0; // initialize flamesensor reading
//int sensorValue=0; 
float sensorValue;

void setup() {
Serial.begin(9600);
mySerial.begin(9600);

pinMode(ledpin,OUTPUT);
pinMode(flamepin,INPUT);
pinMode(smokepin,INPUT);
pinMode(buzpin,OUTPUT);
pinMode(FAN, OUTPUT);
Serial.println("MQ2 warming up!");
delay(20000); // allow the MQ2 to warm up
}

void loop() {
  Serial.print("smoke Sensor Value: ");
  Serial.println(analogRead(smokepin));
  Serial.print("flame Sensor Value: ");
  Serial.println(analogRead(flamepin));
flamesensvalue=analogRead(flamepin); 
noTone(buzpin);
if (flamesensvalue<=threshold) { 
digitalWrite(ledpin,HIGH); 
digitalWrite(buzpin, HIGH);
//delay(1000); //stops program for 1 second
SendCall();
delay(1000);
}

else{
digitalWrite(ledpin,LOW); //turns led off led and buzzer
noTone(buzpin);
}
//sensorValue = analogRead(smokepin);
noTone(buzpin);
  //Serial.println(sensorValue);
//if (sensorValue > 300)
if((analogRead(smokepin)>250))
{
  //tone(buzpin,100);  
  digitalWrite(buzpin, HIGH);
  //analogWrite(buzpin, 100);
  //digitalWrite(ledpin,HIGH);
  analogWrite(FAN, 100);
  SendMessage();  
  delay(2000); // wait 2s for next reading
}

else
{
  //analogWrite(buzpin, 0);
 // digitalWrite(ledpin,LOW);
  noTone(buzpin); 
  analogWrite(FAN, 0);    
}
delay(2000);

}

void SendMessage()
{
  Serial.println("initializing...");  //Message sent to Mobile
  //digitalWrite(flasher1, HIGH);
  //digitalWrite(flasher2, HIGH);
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+918777218032\""); // Replace x with mobile number
  updateSerial();
  mySerial.println("Smoke is detected");// The SMS text you want to send
  updateSerial();
  mySerial.write(26);

}

void SendCall()
{
  Serial.println("initializing...");  //Message sent to Mobile
  //digitalWrite(flasher1, HIGH);
  //digitalWrite(flasher2, HIGH);
  delay(1000);
  mySerial.println("AT");    //Sets the GSM Module in Text Mode
  updateSerial();
  mySerial.println("ATD+ +918777218032;"); // Replace x with mobile number
  updateSerial();
  delay(20000);
  mySerial.println("ATH");// The SMS text you want to send
  updateSerial();

}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

