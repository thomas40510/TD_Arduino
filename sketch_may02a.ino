#include <LiquidCrystal.h>
#include <Wire.h>

#define ID 0x98 >> 1
#define RD_CNTR 0xA8
#define RD_SLOPE 0xA9
const byte rs=12;
const byte enable=11;
String txt;
byte val;
LiquidCrystal lcd(rs,enable,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
lcd.write("nein");

Wire.begin();
Wire.beginTransmission(ID);
Wire.write(0xAC);
Wire.write(0x02);
Wire.write(0x19);
Wire.beginTransmission(ID);
Wire.write(0xEE);
Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
float data;

delay(1000);

//getTemp();
data = highResTemp();

writeTempHR(data);
}
void writeTemp(int data){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature :");
  lcd.setCursor(0,1);
  lcd.print("+"+String(data >> 8) + (data & 0xFF ? ".5" : ".0"));
}
void writeTempHR(float data){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature :");
  lcd.setCursor(0,1);
  lcd.print(data);
}

void getTemp(){
  unsigned int data;
  Wire.beginTransmission(ID);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(ID, 2);
  if(Wire.available()){data = Wire.read() << 8;}
  if(Wire.available()){data |= Wire.read();}
  
  Serial.print(data >> 8);
  Serial.print(data & 0xFF ? ".5" : ".0");
  Serial.println("");
  writeTemp(data);
}

byte getReg(byte reg){
  Wire.beginTransmission(ID);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(ID, 1);
  byte regVal = Wire.read();
  return regVal;
}

float highResTemp(){
  unsigned int data;
//  Wire.beginTransmission(ID);
//  Wire.write(0xAA);
//  Wire.endTransmission();
//  Wire.requestFrom(ID, 2);
//  if(Wire.available()){data = Wire.read() << 8;}
//  if(Wire.available()){data |= Wire.read();}
  unsigned int temp = getReg(0xAA);
  byte remain = getReg(0xA8);
  byte slope = getReg(0xA9);
  Serial.println(remain);
  Serial.println(slope);
  float d = slope - remain;
  Serial.println(d/slope);
  float tempHR = temp - 0.25 + d/slope;
  Serial.println(tempHR);
  return tempHR;
}
