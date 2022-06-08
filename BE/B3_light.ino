const byte pinLedRed = 6;
const byte pinBtn = 21;
const byte pinPont = A9;

long t0;

float values[] = {0.0};
int n = 0;

void setup() {
  //init pins
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinBtn, INPUT);
  pinMode(pinPont, INPUT);

  //init serial
  Serial.begin(115200);
  Serial.println("Ready.");

  t0 = millis();

  attachInterrupt(digitalPinToInterrupt(pinBtn), resetMoyenne, RISING); //interrupt on btn press
}

void loop() {
  if(millis() - t0 >= 2000){ //every 2 seconds
    float data = analogRead(pinPont); //80lux : 392.0
    t0 = millis();
    digitalWrite(pinLedRed, (data <= 392.0));
    values[n] = data;
    Serial.println(moyenne(values));
    n++;
  }
}

float moyenne(float* vals){
  /*
   * Calculates mean of array
   */
  float tot = 0.0;
  int N = sizeof(vals);
  for (int i = 0; i < N; i++){
    tot += vals[i];
  }
  return tot/N;
}

void resetMoyenne(){
  /*
   * resets mean to current val
   */
  Serial.println("reset OK");
  memset(values, analogRead(pinPont), sizeof(values));
  n = 0;
}
