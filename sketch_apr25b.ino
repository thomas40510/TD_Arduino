const byte pinLedRed=37;
const byte pinLedGreen = 36;
const byte boutonPoussoir =18;
long k=0;
long t1=0;
long t2=0;

void setup() {
  // put your setup code here, to run once:
// pinMode(pinLedRed,OUTPUT);
// pinMode(pinLedGreen,OUTPUT);
// pinMode(boutonPoussoir,INPUT);
DDRC |= 00000011;
Serial.begin(115200);
Serial.println("Ready");
t1=millis()
;}

void loop() {
  // put your main code here, to run repeatedly:

k=k+1;
PORTC |= 0x03;
PORTC &= 0xFC;
//digitalWrite(pinLedRed,HIGH);
//digitalWrite(pinLedRed,LOW);
//digitalWrite(pinLedGreen,HIGH);
//digitalWrite(pinLedGreen,LOW);
if (k==10000) {
  t2=millis();
  Serial.println(t2-t1);}

}
