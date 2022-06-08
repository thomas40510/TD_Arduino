const byte pinLedGreen = 32;
const byte pinGen = 19;

float freq = 0.0; //decimal places to force float type
boolean measuring = false;

long t0;
long tf;

void setup() {
  //init pins
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinGen, INPUT);

  //init serial
  Serial.begin(38400);
  Serial.println("Ready.");

  attachInterrupt(digitalPinToInterrupt(pinGen), mesTime, CHANGE); //detect rising and falling of wave gen
}

void loop() {
  digitalWrite(pinLedGreen, digitalRead(pinGen)); //LED has same state as gen
  Serial.println("Freq: " + String(freq) + "Hz"); //display frequency
}

void mesTime(){
  /*
   * Measure time between peaks and freq of signal from wave gen
   */
  if (measuring){
    tf = millis();
    freq = 1.0/(tf-t0) * 1000.0;
  } else {
    t0 = millis();
  }
  measuring = !measuring;
}
