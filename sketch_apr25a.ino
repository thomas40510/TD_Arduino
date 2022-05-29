#include <TimerOne.h>
const byte pinLedRed=37;
const byte pinLedGreen = 36;
const byte boutonPoussoir =18;
boolean prec =false;
int t1=0;
int t0=0;


#define digitalPinToInterrupt(p) ((p)==2 ? 0: ((p)==3 ? 1 :((p)>=18&&(p)<=21 ? 23-(p) : -1)))


void setup() {
  // put your setup code here, to run once:
 pinMode(pinLedRed,OUTPUT);
 pinMode(pinLedGreen,OUTPUT);
 pinMode(boutonPoussoir,INPUT);
Serial.begin(115200);
Serial.println("Ready");
attachInterrupt(digitalPinToInterrupt(boutonPoussoir),lum,CHANGE);
Timer1.initialize();
Timer1.setPeriod(4000000);
Timer1.attachInterrupt(TurnLightOff);
}
void loop() { // repeat infinitely ...

digitalWrite(pinLedRed,HIGH);
delay(1000);
digitalWrite(pinLedRed,LOW);
delay(1000);
  }


void lum() {
  if (digitalRead(boutonPoussoir)!=0) {
  digitalWrite(pinLedGreen,HIGH);
  t0=millis();
  Serial.println("timer starts");
  Timer1.start();}}

void TurnLightOff() {
    digitalWrite(pinLedGreen,LOW);
    t1=millis();
    Serial.println(t1-t0);
    Serial.println("timer ends");
    Timer1.stop();}
