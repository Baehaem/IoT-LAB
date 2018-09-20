#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

const int BUTTON[] = {4,5,6,7};
String str;
#define STRART "start"
int blueRx=3;   //Rx (받는핀 설정)
int blueTx=2;   //Tx (보내는핀 설정)at
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언


boolean lastButton[] = {HIGH, HIGH, HIGH, HIGH}; //이전 버튼의 눌림 상태를 Boolean형 변수로 선언
boolean currentButton[] = {HIGH, HIGH, HIGH, HIGH}; //현재 버튼의 눌림 상태를 Boolean형 변수로 선언


void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600); //블루투스 시리얼
    
    for(int i=0;i<4;i++) {
      pinMode(BUTTON[i], INPUT);
    }
    Serial.println("connected");
}


boolean debounce(boolean last, int btn)
{
    boolean current=digitalRead(btn); //현재 버튼 상태를 확인
    if(last != current) //이전 버튼 상태와 현재 버튼 상태가 다름
    {
        delay(5); //5ms 동안 기다림
        current=digitalRead(btn); //current에 현재 버튼 상태를 저장
    }
    return current; //current 변수값을 반환
}

void loop()
{
  for(int i = 0; i< 4; i++)
  {
    currentButton[i] = debounce(lastButton[i], BUTTON[i]); //디바운싱 처리된 버튼값을 읽음
    if(lastButton[i] == HIGH && currentButton[i] == LOW) {
        Serial.print("btn");
        Serial.print(i+1);
        Serial.println(" pushed");
        if(i==0) {
        mySerial.write(STRART);
        delay(7);
        Serial.println(STRART);
      }
     }
      lastButton[i]=currentButton[i]; 
  }
}
