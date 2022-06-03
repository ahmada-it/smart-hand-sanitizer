#include<SoftwareSerial.h>
#include<timer.h>
#include<Servo.h>

#define pinServo 8 // pin servo
#define pinServo2 9 // pin servo 2
#define pinInfra 7 // pin infrared

Servo myservo;
Servo servoku;
String hasilInfra;

SoftwareSerial ss(2,3); // 3 to pin D6 NodeMCU, 2 to pin D5 NodeMCU
auto timer = timer_create_default();

void setup(){
  Serial.begin(9600);
  ss.begin(115200);
  timer.every(1000, sendData);
  timer.every(1000, aksi);
  pinMode(pinInfra, INPUT);
  myservo.attach(pinServo);
  servoku.attach(pinServo2);
}

void loop(){
  timer.tick();
}

// fungsi untuk aksi servo
void aksi(){
  if(digitalRead(pinInfra) == HIGH){
    Serial.println("Handsanitizer Off");
    myservo.write(180);
    servoku.write(-180);
    hasilInfra = "1";
//    if(hasilInfra==0){
//      hasilInfra=1;
//    }
    Serial.println(hasilInfra);
  }
  else{
    Serial.println("Handsanitizer On");
    myservo.write(-180);
    servoku.write(180);
    hasilInfra = "0";
//    if(hasilInfra==1){
//      hasilInfra=0;
//    }
    Serial.println(hasilInfra);
  }
}
//
//int getInfra(){
//  int readInfra = digitalRead(pinInfra);
//  Serial.println(readInfra);
//  return readInfra;
//}

void sendData(){
  String msg = "@";
  msg += String(hasilInfra);

  ss.println(msg);
}
