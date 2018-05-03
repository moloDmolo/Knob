/*
Example project to control a X9CXXX digital potentiometer

https://github.com/GitMoDu/FastX9CXXX

modified 30 Aug 2017
by MoDu
*/

#include <FastX9CXXX.h>
#include <Servo.h>
#define X9_CS_PIN 7
#define X9_UD_PIN 8
#define X9_INC_PIN 9
#define outputA 10
#define outputB 11
FastX9CXXX Potentiometer;

int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;   
int val_mapped;
int servo_m;//
Servo myservo;
boolean blink_=false; 
 int pos = 0;   
 long heartBeatArray[] = {
    50, 100, 15, 1200};
int hbeatIndex = 1;   // this initialization is important or it starts on the "wrong foot"
long prevMillis;

int LEDpin = 13;
void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(2, INPUT);
  myservo.attach(12); 
  Serial.begin(9600);
  Serial.println();
  Serial.print(F("X9C104 Digital Potentiometer setup..."));
  randomSeed(analogRead(0));
  //Potentiometer.Begin();
  Potentiometer.Setup(X9_CS_PIN, X9_UD_PIN, X9_INC_PIN);
  Serial.println(F(" complete."));

}

void loop() {
  
 val = analogRead(potPin);
 Serial.println(val);
 val_mapped=(float)map(val, 0, 1023, 0,100);
 Potentiometer.JumpToStep(val_mapped +20);
 if(val_mapped >=50){
  blink_=true;
  myservo.write(14);              // tell servo to go to position in variable 'pos'
    
    delay(15);     
 }
 if(val_mapped <50 && val_mapped >10){
  blink_=false;
  myservo.write(0);              // tell servo to go to position in variable 'pos'
    
    delay(15);     
 }
 
 heartBeat(1.0);
  
}

void heartBeat(float tempo){
  if(blink_==true){
    if ((millis() - prevMillis) > (long)(heartBeatArray[hbeatIndex] * tempo)){
        hbeatIndex++;
        if (hbeatIndex > 3) hbeatIndex = 0;

        if ((hbeatIndex % 2) == 0){
            digitalWrite(LEDpin, HIGH);
            delay((int)heartBeatArray[hbeatIndex]) ;  
            digitalWrite(LEDpin, LOW);
        }
        hbeatIndex++;
        // Serial.println(hbeatIndex);
        prevMillis = millis();

    }
  }
}
