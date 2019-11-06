#include <LiquidCrystal.h> 
#include <SoftwareSerial.h>


int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

const int Ao = 0; //A0{S} to A0{U} 
const int Do = 7; //D0{S} to D7{U}
const int led = 13; // Led on D3{U}

SoftwareSerial mySerial(9, 10);

int limit;
int value;

void setup() {
analogWrite(6,Contrast);
lcd.begin(16, 2);

Serial.begin(115200);
mySerial.begin(9600);

pinMode(Ao,INPUT); //input on A0{S}
pinMode(Do,INPUT); //input on Do{S}
pinMode(led, OUTPUT);//output for led form U


}
void loop() { 
     
value = analogRead(Ao);
limit = digitalRead(Do);
Serial.print("Alcohol Level :");
Serial.println(value);
Serial.print("Limit : ");
Serial.println(limit);
delay(500);

if (value>=500){
digitalWrite(13,LOW);
lcd.setCursor(0, 0);
lcd.print("Alcohol Detected");
   
lcd.setCursor(0, 1);
lcd.print("Engine Blocked");

mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
delay(1000);  // Delay of 1 second
mySerial.println("AT+CMGS=\"+919354843009\"\r"); 
delay(1000);
mySerial.println("Alert!!!!!!!!   The Driver in the Vehicle with Registration Number HR 26 XX XXXX is Badily Drunk. Please Reach ASAP. - DnD Avoider");
delay(100);
mySerial.println((char)26);
delay(1000);
}
else {
digitalWrite(13,HIGH);
lcd.setCursor(0, 0);
lcd.print("TIME : 5:43pm");
   
lcd.setCursor(0, 1);
lcd.print("TRIP A : 5896");}
 }
