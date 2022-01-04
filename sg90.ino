#include<Servo.h> //呼叫Servo函式庫
Servo myservo;

void setup() {
  myservo.attach(9);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(5);
  delay(2000);
  myservo.write(175);
  delay(2000);
}
