#include <IRremote.h>
int IR_RECEIVE_PIN = 9;
#define OPEN = 0xEAB7BACD
int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
long duration, cm, inches, ms;
unsigned long runTime;
void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出
  pinMode(echoPin, INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("CLEARDATA");     //清空數據
  Serial.println("LABEL,Date,Time,mills,distance(cm)");
}
void loop(){ 
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.address == 0x0) {
      if (IrReceiver.decodedIRData.command == 0x16) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(5);
        digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        pinMode(echoPin, INPUT);             // 讀取 echo 的電位
        duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
        cm = (duration / 2) / 29.1;       // 將時間換算成距離 cm 或 inch
        inches = (duration / 2) / 74;
        runTime = millis();
        Serial.println( (String) "DATA,DATE,TIME," + runTime + "," + cm );
      }
      IrReceiver.resume();
    }
    delay(10);
  }
}
