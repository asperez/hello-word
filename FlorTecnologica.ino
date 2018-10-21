#include <Stepper.h>
double distance;
int pinTrigger=6;
int pinEcho=7;
int pinLedGreen=2;
int pinLedYellow=3;
int pinLedRed=4;
int pinBuzzer=8;
int pinStep1=10;
int pinStep2=11;
int pinStep3=12;
int pinStep4=13;
double dist1=10;
double dist2=30;
double dist3=50;

#define STEPSV 200
#define SPEED 100
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262


Stepper stepper_1(STEPSV,pinStep1,pinStep3,pinStep2,pinStep4);

double fnc_ultrasonic_distance(int _t, int _e){
  double dur=0;
  digitalWrite(_t, LOW);
  delayMicroseconds(2);
  digitalWrite(_t, HIGH);
  delayMicroseconds(10);
  digitalWrite(_t, LOW);
  dur = pulseIn(_e, HIGH);
  return (dur / 29.0 / 2.0);
}

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void playMusic(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pinBuzzer, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(pinBuzzer);
  }
}

void setup()
{
  Serial.begin(9600);
  stepper_1.setSpeed(SPEED);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
      //stepper_1.step(-200);

}


void loop()
{
    distance = fnc_ultrasonic_distance(pinTrigger,pinEcho);
    if (distance<=dist1){
      Serial.println("muy cerca");
      digitalWrite(pinLedGreen, LOW);
      digitalWrite(pinLedYellow, LOW);
      digitalWrite(pinLedRed, HIGH);
      //stepper_1.setSpeed(500);
      stepper_1.step(400);
      delay(1000);
      playMusic();
      stepper_1.step(-400);
      delay(1000);
      
    } else {
      //stepper_1.setSpeed(0);
      if (distance<dist2){
        Serial.println("cerca");
        digitalWrite(pinLedGreen, LOW);
        digitalWrite(pinLedYellow, HIGH);
        digitalWrite(pinLedRed, LOW);
      }
      if (distance>=dist2 && distance<dist3){
        Serial.println("normal");
        digitalWrite(pinLedGreen, HIGH);
        digitalWrite(pinLedYellow, LOW);
        digitalWrite(pinLedRed, LOW);
      }
      if(distance>=dist3){
        Serial.println("lejos");
        digitalWrite(pinLedGreen, LOW);
        digitalWrite(pinLedYellow, LOW);
        digitalWrite(pinLedRed, LOW);
      }  
   }
}


