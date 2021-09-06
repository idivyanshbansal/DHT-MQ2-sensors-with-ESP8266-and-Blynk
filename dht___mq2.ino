#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = ".............";
char ssid[] = ",,,,,,,,,,,,";
char pass[] = ".............";
#define DHTPIN 2         
#define DHTTYPE DHT11     
int Value_D7;
int Value_D8;
int Pin_D7 = 13;
int Pin_D8 = 15;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
float h = dht.readHumidity();
float t = dht.readTemperature(); 
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
pinMode(Pin_D7,OUTPUT);
  pinMode(Pin_D8,OUTPUT);
  pinMode(A0,INPUT);
  timer.setInterval(1000L, sendSensor);
}
void loop()
{
  digitalWrite(Pin_D7, HIGH);     
  delay(10);                     
  Value_D7 = analogRead(0);       
  digitalWrite(Pin_D7, LOW);      
  digitalWrite(Pin_D8, HIGH);   
  delay(10);                    
  Value_D8 = analogRead(0);    
  digitalWrite(Pin_D8, LOW);    
  delay(10);                     
  Serial.print("D7 = ");   
  Serial.print(Value_D7);
  Serial.print(" / D8 = ");   
  Serial.println(Value_D8);
  Blynk.virtualWrite(V20, Value_D7); 
  Blynk.virtualWrite(V21, Value_D8);      
  Blynk.run();
  timer.run(); 
}
