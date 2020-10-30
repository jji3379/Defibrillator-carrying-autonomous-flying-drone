#include <SoftwareSerial.h>

#define RX 0
#define TX 1
unsigned long cnt=0; // 몇초 눌러지는지 확인용
unsigned long times=0; // 눌러진 시간

SoftwareSerial HC12(RX,TX);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
HC12.begin(9600); 
pinMode(13,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
int button=digitalRead(13);
if(digitalRead(13)==HIGH && cnt==0){
  cnt=millis();
}
else if(cnt>0 && digitalRead(13)==LOW){
  times=millis()-cnt;
  cnt=0;
  }
  else if(digitalRead(13)==LOW){
    times=0;
    } 
    if(times>3000){
  HC12.write(button);
  Serial.write(HC12.read());
  Serial.println("버튼 눌림");
  delay(1000);
  }
  if(Serial.available()){
    HC12.write(Serial.read());
    }
}
