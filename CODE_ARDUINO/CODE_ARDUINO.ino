// phai trai do den do+ den- out4+(10)  out2+(8)
//out3 (9)  out1(7)
// phai out4 out3
// trai out2 out1
#include <Wire.h>
#include "DHT.h"            
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
String sttXe;
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
void setup()
{
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void receiveEvent(int howMany) {
  sttXe="";
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    sttXe = String(sttXe+c);           /* print the character */
  }
               /* to newline */
}
void loop()
{
  if (sttXe == "up")
    Up();
  if (sttXe == "down")
    Down();
  if (sttXe == "left")
    Left();
  if (sttXe == "right")
    Right();  
}
void Up()
{
  Serial.println(sttXe);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Left(){
  Serial.println(sttXe);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Right()
{
  Serial.println(sttXe);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Down(){
  Serial.println(sttXe);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
