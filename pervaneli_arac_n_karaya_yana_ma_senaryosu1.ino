#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#define kirmizi 12
#define turuncu 11
#define yesil 10
#define buzzer 9
#define isik A3
#define farlar 6
#define mesafe 13

Adafruit_LiquidCrystal lcd_mesafe(0);
int servoPin = 5;
Servo pervane;


void setup()
{
  pinMode(kirmizi, OUTPUT);
  pinMode(turuncu, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(isik, INPUT);
  pinMode(farlar, OUTPUT);
 
  lcd_mesafe.begin(16, 2);
  lcd_mesafe.setBacklight(1);
  
  pervane.attach(servoPin);
  Serial.begin(9600);
 
}

void loop()
{
  long sure, uzaklik;
  int angle=0;
  
  digitalWrite(kirmizi, 0);
  digitalWrite(turuncu, 0);
  digitalWrite(yesil, 0);
  digitalWrite(farlar, 0);
 
  //ortam verilerini alma
  int Isik = analogRead(isik);
  
  //yazdırma
 
  Serial.print("isik: ");
  Serial.println(Isik);
  
 
  
  //UZAKLIK ÖLÇÜMÜ
  pinMode(mesafe, OUTPUT);
  digitalWrite(mesafe, 0);
  delayMicroseconds(2);
  digitalWrite(mesafe, 1);
  delayMicroseconds(5);
  digitalWrite(mesafe, 0);
  pinMode(mesafe, INPUT);
  sure = pulseIn(mesafe, 1);
  uzaklik = sure/29/2;
  Serial.print("uzaklik: ");
  Serial.println(uzaklik);
  Serial.println(" ");
  
  lcd_mesafe.setCursor(1, 1);
  lcd_mesafe.print("mesafe: ");
  lcd_mesafe.print(uzaklik);
  
  if(uzaklik>100)
  {
    digitalWrite(kirmizi, 1);
    delay(500);
    angle = 0;
    pervane.write(angle);
  	angle = 360;
 	pervane.write(angle);
  	delay(1750-(uzaklik*5));
 	angle = 0;
    pervane.write(angle);
  }
  else if(uzaklik>50 && uzaklik<=100)
  {
    digitalWrite(kirmizi, 0);
    digitalWrite(turuncu, 1); 
    tone(buzzer, 1200-(uzaklik*10));
    delay(uzaklik*5);
    noTone(buzzer);
    delay((uzaklik*5)/2);
    
    angle = 0;
    pervane.write(angle);
  	angle = 360;
 	pervane.write(angle);
  	delay(2000-(uzaklik*10));
 	angle = 0;
    pervane.write(angle);
    
  }
  else if(uzaklik>=38 && uzaklik<50)
  {
    digitalWrite(kirmizi, 0);
    digitalWrite(turuncu, 0);
    digitalWrite(yesil, 1);
    tone(buzzer, 1000);
    delay(250);
    noTone(buzzer);
    delay(100);
    
    angle = 0;
    delay(1000);
  }
  
  if(Isik<125)
  {
    digitalWrite(farlar, 1);
    delay(1000);
  }
   lcd_mesafe.clear();
  
}