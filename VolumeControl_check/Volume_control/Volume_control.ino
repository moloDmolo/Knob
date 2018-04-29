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

Servo myservo;
boolean blink_=false;
 int counter = 0; 
 int aState;
 int aLastState;
 float counter_mapped;
 
 int pos = 0;   
 long heartBeatArray[] = {
    50, 100, 15, 1200};
int hbeatIndex = 1;   // this initialization is important or it starts on the "wrong foot"
long prevMillis;

int LEDpin = 13;
void setup() {
  pinMode(LEDpin, OUTPUT);
  myservo.attach(12); 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
	Serial.begin(9600);
	Serial.println();
	Serial.print(F("X9C104 Digital Potentiometer setup..."));
	randomSeed(analogRead(0));
	//Potentiometer.Begin();
	Potentiometer.Setup(X9_CS_PIN, X9_UD_PIN, X9_INC_PIN);
	Serial.println(F(" complete."));
  aLastState = digitalRead(outputA);   

}

void loop() {
  
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
       
     } else {
       counter --;
       
     }
     Serial.print("Position: ");
     counter_mapped = (float) (map(counter, -100,100, -256, 256));
     Serial.println(counter_mapped);
     Potentiometer.JumpToStep(counter_mapped);

     if(counter_mapped >=75){
      blink_=true;
      // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(14);              // tell servo to go to position in variable 'pos'
    
    delay(15);                       // waits 15ms for the servo to reach the position

  }
  if(counter_mapped < 75){
    blink_=false;
       // in steps of 1 degree
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(15);
  
  }
   } 
   aLastState = aState;
   heartBeat(1.0);
	//Potentiometer.JumpToStep(random(100));
	//Serial.print(F("Potentiometer current step: "));
	//Serial.print(Potentiometer.GetStep(), DEC);
	//Serial.println();
	//delay(1000);    // wait for a second
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
