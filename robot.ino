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

void loop(){
  while (Serial.available() > 0) {
    BLE_val = BLE_val + ((char)(Serial.read()));
    delay(2);
  }
  if (0 < String(BLE_val).length() && 2 >= String(BLE_val).length()) {
    Serial.println(String(BLE_val).length());
    Serial.println(BLE_val);
    switch (String(BLE_val).charAt(0)) {
     case 'o':
      claw_open();
      break;
     case 'c':
      claw_close();
      break;
     case 'u':
      arm_up();
      break;
     case 'd':
      arm_down();
      break;
     case 'l':
      arm_base_anticlockwise();
      break;
     case 'r':
      arm_base_clockwise();
      break;
     case 'F':
      Move_forward_Function();
      break;
     case 'B':
      Move_backward_Function();
      break;
     case 'L':
      Turn_left_Function();
      break;
     case 'R':
      Turn_right_Function();
      break;
     case 'S':
      Stop();
      break;
     case 'A':
      Avoidance_Function();
      break;
    }
    BLE_val = "";

  } else {
    BLE_val = "";

  }

}


void claw_close() {
  claw_close_flag = true;
  while (claw_close_flag) {
    claw_degrees = claw_degrees + 1;
    myservo1.write(claw_degrees);
    Serial.println(claw_degrees);
    delay(10);
    if (claw_degrees >= 180) {
      claw_degrees = 180;

    }
    if (Serial.read() == 's') {
      claw_close_flag = false;

    }
  }
}


void claw_open() {
  claw_close_flag = true;
  while (claw_close_flag) {
    claw_degrees = claw_degrees - 1;
    myservo1.write(claw_degrees);
    Serial.println(claw_degrees);
    delay(10);
    if (claw_degrees <= 90) {
      claw_degrees = 90;

    }
    if (Serial.read() == 's') {
      claw_close_flag = false;

    }
  }
}

void arm_down() {
  arm_forward_flag = true;
  while (arm_forward_flag) {
    arm_degrees = arm_degrees + 1;
    myservo2.write(arm_degrees);
    delay(10);
    Serial.println(arm_degrees);
    if (arm_degrees >= 135) {
      arm_degrees = 135;

    }
    if (Serial.read() == 's') {
      arm_forward_flag = false;

    }
  }
}




void arm_up() {
  claw_recracted_flag = true;
  while (claw_recracted_flag) {
    arm_degrees = arm_degrees - 1;
    myservo2.write(arm_degrees);
    Serial.println(arm_degrees);
    delay(10);
    if (arm_degrees <= 90) {
      arm_degrees = 90;

    }
    if (Serial.read() == 's') {
      claw_recracted_flag = false;

    }
  }
}

void Stop() {
  digitalWrite(2,LOW);
  analogWrite(5,0);
  digitalWrite(4,HIGH);
  analogWrite(6,0);
}

void arm_base_anticlockwise() {
  base_anticlockwise_flag = true;
  while (base_anticlockwise_flag) {
    base_degrees = base_degrees + 1;
    myservo3.write(base_degrees);
    Serial.println(base_degrees);
    delay(10);
    if (base_degrees >= 180) {
      base_degrees = 180;

    }
    if (Serial.read() == 's') {
      base_anticlockwise_flag = false;

    }
  }
}



void arm_base_clockwise() {
  base_clockwise_flag = true;
  while (base_clockwise_flag) {
    base_degrees = base_degrees - 1;
    myservo3.write(base_degrees);
    Serial.println(base_degrees);
    delay(10);
    if (base_degrees <= 0) {
      base_degrees = 0;

    }
    if (Serial.read() == 's') {
      base_clockwise_flag = false;

    }
  }
}

void Move_Forward(int speed) //Define the forward function of the input speed
{
  digitalWrite(2,HIGH);
  analogWrite(5,speed);
  digitalWrite(4,LOW);
  analogWrite(6,speed);
}

void Rotate_Left(int speed) //Define the left rotation function of the input speed
{
  digitalWrite(2,LOW);
  analogWrite(5,speed);
  digitalWrite(4,LOW);
  analogWrite(6,speed);
}

void Rotate_Right(int speed) //Define the right rotation function that can enter the speed
{
  digitalWrite(2,HIGH);
  analogWrite(5,speed);
  digitalWrite(4,HIGH);
  analogWrite(6,speed);
}

void Move_Backward(int speed) //Define the back function of the input speed
{
  digitalWrite(2,LOW);
  analogWrite(5,speed);
  digitalWrite(4,HIGH);
  analogWrite(6,speed);
}

void Move_backward_Function() {
  backward_flag = true;
  while (backward_flag) {
    Move_Backward(speed_car);
    if (Serial.read() == 'S') {
      backward_flag = false;
      Stop();

    }
  }
}

void Move_forward_Function() {
  forward_flag = true;
  while (forward_flag) {
    Move_Forward(speed_car);
    if (Serial.read() == 'S') {
      forward_flag = false;
      Stop();

    }
  }
}

void Avoidance_Function() {
  int Avoidance_distance = 0;
  Avoidance_Function_flag = true;
  while (Avoidance_Function_flag) {
    Avoidance_distance = checkdistance();
    if (Avoidance_distance <= 25) {
      if (Avoidance_distance <= 15) {
        Stop();
        delay(100);
        Move_Backward(100);
        delay(600);

      } else {
        Stop();
        delay(100);
        Rotate_Left(100);
        delay(600);

      }

    } else {
      Move_Forward(70);

    }
    if (Serial.read() == 'S') {
      Avoidance_Function_flag = false;
      Stop();

    }
  }
}

float checkdistance() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  float distance = pulseIn(13, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Turn_right_Function() {
  right_flag = true;
  while (right_flag) {
    Rotate_Right(speed_car);
    if (Serial.read() == 'S') {
      right_flag = false;
      Stop();

    }
  }
}

void Turn_left_Function() {
  left_flag = true;
  while (left_flag) {
    Rotate_Left(speed_car);
    if (Serial.read() == 'S') {
      left_flag = false;
      Stop();

    }
  }
}
