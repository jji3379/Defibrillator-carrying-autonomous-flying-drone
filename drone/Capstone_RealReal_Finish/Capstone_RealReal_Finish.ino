#include <Joystick.h>          //조이스틱 라이브러리
#include <SoftwareSerial.h>    // 무선통신 라이브러리
SoftwareSerial HC12(10,11);    //RX, TX
int button_state=0; 

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  1, 0,                        // Button Count, Hat Switch Count
  true, true, true,            // X and Y, but no Z Axis
  true, true, false,           // No Rx, Ry, or Rz
  false, true,                 // No rudder or throttle
  false, false, false);        // No accelerator, brake, or steering

const int Roll=A0;
const int Pitch=A1;
const int Yaw=A2;
const int Throttle=A3;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);                     //시리얼 통신 시작
HC12.begin(9600);                       //무선 통신 시작

pinMode(9, INPUT_PULLUP);               // ARM 버튼

Joystick.begin();                       // 조이스틱 시작
Joystick.setXAxisRange(-127, 127);      // Roll범위 설정
Joystick.setYAxisRange(-127, 127);      // Pitch범위 설정
Joystick.setRyAxisRange(0, 360);        // Throttle범위 설정
Joystick.setRxAxisRange(0, 360);        // Yaw범위 설정

}
int lastButtonState[3] = {0,0,0};       // 버튼 마지막 상태
const int pinToButtonMap =9 ;           // 물리적 핀을 조이스틱 버튼에 매핑하는 상수.

void loop() {
  // put your main code here, to run repeatedly:
int Roll_value=analogRead(Roll);                       // Roll 수신 값 변수 지정
int Pitch_value=analogRead(Pitch);                     // Pitch 수신 값 변수 지정
int Throttle_value=analogRead(Throttle);               // Throttle 수신 값 변수 지정
int Yaw_value=analogRead(Yaw);                         // Yaw 수신 값 변수 지정

Joystick.setXAxis(map(Roll_value,0,1023,-127,127));    // Roll 수신값 범위 변경      
Joystick.setYAxis(map(Pitch_value,0,1023,-127,127));   // Pitch 수신값 범위 변경
Joystick.setRyAxis(map(Throttle_value,0,1023,0,360));  // Throttle 수신값 범위 변경
Joystick.setRxAxis(map(Yaw_value,0,1023,0,360));       // Yaw 수신값 범위 변경
  

   for (int index = 0; index < 3; index++)             
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);   // 조이스틱 버튼 할당
      lastButtonState[index] = currentButtonState;
    }
  }
  
if(HC12.available()){                // 무선통신 대기 상태
  Serial.write(HC12.read());         // 무선통신 수신
  Joystick.setRyAxis(0);             // Throttle 낮춤
  delay(1000);
  Joystick.pressButton(0);           // ARM 시동
  delay(1000);
  Joystick.releaseButton(0);         // 버튼 해제
  delay(2000);
  Joystick.setRyAxis(160);           // Throttle 44%
  delay(500);
  Joystick.setRyAxis(170);           // Throttle 47%
  delay(500);
  Joystick.setRyAxis(180);           // Throttle 50%
  delay(500);
  Joystick.setRyAxis(290);           // Throttle 80%
  delay(500);
  Joystick.setRyAxis(300);           // Throttle 83%
  delay(1000);
  Joystick.setXAxis(110);            // Auto Mode 변경
  delay(1000);
  Serial.println("제세동기 출발");
  }
  if(Serial.available()){
    HC12.write(Serial.read());
     }
}
