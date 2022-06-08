const byte pinLedRed = 9;
const byte pinBtnA = 19;
const byte pinBtnB = 18;

boolean timerIsOn = false;
boolean timerEnd = false;
boolean isPaused = false;

long t0;

long tpauseOn;

void setup() {
  //setting up pins
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinBtnA, INPUT);
  pinMode(pinBtnB, INPUT);

  //Serial comms
  Serial.begin(19200);
  Serial.println("Ready.");

  digitalWrite(pinLedRed, LOW);

  //interrupts
  attachInterrupt(digitalPinToInterrupt(pinBtnB), commuteTimer, RISING);
  attachInterrupt(digitalPinToInterrupt(pinBtnA), pauseTimer, RISING);
  
}

void loop() {
  if (timerEnd){ // timer just ended
    Serial.println("Time was: ");
    Serial.println(millis()-t0);
    digitalWrite(pinLedRed, LOW);
    timerEnd = false;
  }
}

void commuteTimer(){
  /*
   * commutes the state of the timer (if OFF, then turns ON ; if ON, turn OFF)
   */
  if (!timerIsOn){
    t0 = millis();
    digitalWrite(pinLedRed, HIGH);
    Serial.println("Measuring time...");
  } else {
    timerEnd = true;
  };
  timerIsOn = !timerIsOn;
  isPaused = false;
}

void pauseTimer(){
  /*
   * "pauses" timer : saves pause begin and end times and slides t0 towards corrected value
   */
  if (!isPaused){
    tpauseOn = millis();
    Serial.println("Pausing.");
  } else{
    t0 = millis() - tpauseOn + t0;
    Serial.println(t0);
    Serial.println("Resuming timer.");
  }
  isPaused = !isPaused;
}
