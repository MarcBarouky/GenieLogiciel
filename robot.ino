#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;

String BLE_val;

int base_degrees;
int arm_degrees;
int claw_degrees;


 boolean forward_flag;
 boolean backward_flag;
 boolean left_flag;
 boolean right_flag;
 boolean claw_close_flag;
 boolean claw_open_flag;
 boolean arm_forward_flag;
 boolean claw_recracted_flag;
 boolean base_anticlockwise_flag;
 boolean base_clockwise_flag;

 char bluetooth_val;

 //Sensors
boolean Avoidance_Function_flag; 
int distance;
int speed_car;


void setup(){
  Serial.begin(9600);
  BLE_val = "";
  base_degrees = 90;
  arm_degrees = 135;
  claw_degrees = 90;

  speed_car = 220;

  forward_flag = false;
  backward_flag = false;
  left_flag = false;
  right_flag = false;
  claw_close_flag = false;
  claw_open_flag = false;
  arm_forward_flag = false;
  claw_recracted_flag = false;
  base_anticlockwise_flag = false;
  base_clockwise_flag = false;
  Avoidance_Function_flag = false;

  distance = 0;

  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);


  myservo1.write(claw_degrees);
  delay(500);
  myservo2.write(arm_degrees);
  delay(500);
  myservo3.write(base_degrees);
  delay(500);

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT); //sensor
  pinMode(13, INPUT); //sensor
  Serial.begin(9600);

}
