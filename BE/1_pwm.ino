const byte pinLedGreen = 34;
const byte pinLedRed = 8;
const byte pinBtn = 19;

boolean isGreenOn = true;



void setup() {
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinBtn, INPUT);
  Serial.begin(115200);
  Serial.println("Ready.");
  attachInterrupt(digitalPinToInterrupt(pinBtn), lightOff, RISING); // interruption au front montant
}

void loop() {
  if (isGreenOn){ // la LED verte est allumable
    pwm(pinLedGreen);
  }
  analogWrite(pinLedRed, 255*0.4); // LED rouge (pwm natif)
  
}

void lightOff(){
  /*
   * extinction de la LED verte
   */
  isGreenOn = !isGreenOn;
  digitalWrite(pinLedGreen, LOW);
  Serial.println("btn OK");
}

void pwm(byte pin){
  /*
  * https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
  */
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(150-10);
}
