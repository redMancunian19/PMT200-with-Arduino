#include <max6675.h>

#include <Adafruit_MAX31865.h>

#include <LiquidCrystal.h>
#include <Wire.h>

const int  buttonPinCTN   = 30;
const int  buttonPinPT100   = 31;
const int  buttonPinK  = 32;
const int  buttonPinJ  = 33;

const int RS = 13, EN = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int buttonStateCTN = 0; 
int lastButtonStateCTN = 0;  
int buttonStatePT100 = 0; 
int lastButtonStatePT100 = 0;
int buttonStateK = 0; 
int lastButtonStateK = 0;
int buttonStateJ = 0; 
int lastButtonStateJ = 0;

bool bPress = false;

int thermoDO_k = 24;
int thermoCS_k = 5;
int thermoCLK_k = 4;

int thermoDO_j = 25;
int thermoCS_j = 7;
int thermoCLK_j = 6;

float EA0;
float Ur;
float CTN;

MAX6675 thermocouple_k(thermoCLK_k, thermoCS_k, thermoDO_k);
MAX6675 thermocouple_j(thermoCLK_j, thermoCS_j, thermoDO_j);
Adafruit_MAX31865 mon_capteur = Adafruit_MAX31865(2, 3, 22, 23);

void setup() {
  
  Serial.begin(9600);
  mon_capteur.begin(MAX31865_2WIRE);
  lcd.begin(16, 2);
  pinMode( buttonPinK , INPUT_PULLUP);
  pinMode( buttonPinJ , INPUT_PULLUP);
  pinMode( buttonPinPT100 , INPUT_PULLUP);
  pinMode( buttonPinCTN , INPUT_PULLUP);
}


void loop() {

  K();
  J();
  PT100();
  T_CTN();
  
    if( bPress){

       bPress = false;

      lcd.setCursor(2,1);

      lcd.print("               ");

   

   }

}

void K(){
  buttonStateK = digitalRead(buttonPinK);
  if (buttonStateK != lastButtonStateK) {
    if (buttonStateK == LOW) {
           bPress = true;
   lcd.setCursor(0, 0);        
   lcd.print("Tk en C = "); 
   lcd.setCursor(2, 1); 
   lcd.print(thermocouple_k.readCelsius());
   delay(1000);
      }
    else {
  Serial.println("off");}

    delay(50);

  }

   lastButtonStateK = buttonStateK;
 }


 void J(){
  buttonStateJ = digitalRead(buttonPinJ);
  if (buttonStateJ != lastButtonStateJ) {
    if (buttonStateJ == LOW) {
           bPress = true;
   lcd.setCursor(0, 0); 
   lcd.print("Tj en C = "); 
   lcd.setCursor(2, 1); 
   lcd.print(thermocouple_j.readCelsius());
   delay(1000);
 
      }
    else {
  Serial.println("off");}

    delay(50);

  }

   lastButtonStateJ = buttonStateJ;
 }


   
  
 void PT100(){
 
  buttonStatePT100 = digitalRead(buttonPinPT100);
  if (buttonStatePT100 != lastButtonStatePT100) {
    if (buttonStatePT100 == LOW) {
           bPress = true;
  float R = mon_capteur.lecture_resistance();
  float T=(R-101.7)/0.378;
  lcd.setCursor(0, 0);
  lcd.print("tempPT100 en C = "); 
  lcd.setCursor(2, 1);
  lcd.print(T);
  delay(1000);
  
 
      }
    else {
  Serial.println("off");}

    delay(50);

  }

   lastButtonStatePT100 = buttonStatePT100;
 }

   
 void T_CTN(){
  buttonStateCTN = digitalRead(buttonPinCTN);
  if (buttonStateCTN != lastButtonStateCTN) {
    if (buttonStateCTN == LOW) {
           bPress = true;
    EA0 = analogRead(A0);
   Ur=5*EA0/1023;
   CTN=(Ur-1.19)/52.8E-3;
   lcd.setCursor(0, 0);
   lcd.print("tempCTN en C = "); 
   lcd.setCursor(2, 1);
   lcd.print(CTN);
   delay(1000);
  
 
      }
    else {
  Serial.println("off");}

    delay(50);

  }

   lastButtonStateCTN = buttonStateCTN;
 }
  


  
