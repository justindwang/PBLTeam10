#include <Servo.h>
// #include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <SPI.h>
#include <Pixy2.h>

//our L298N control pins
int enA = 2;
int IN1 = 3;
int IN2 = 4;

int enB = 7;
int IN3 = 5;
int IN4 = 6;

int trigPin = 8;
int echoPin = 9;
// defines variables
long duration;
int distance;
bool found = false;
// int maxDistance = 200;

// boolean goesForward = false;
// int distance = 150;

// NewPing sonar(trigPin, echoPin, maxDistance);
Servo base_servo; //our servo name
int base_servo_angle = 180;
Servo cup_servo; //our servo name
int cup_servo_angle = 0;

Pixy2 pixy;

void setup(){

  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pixy.init();
  
  base_servo.attach(10); //our servo pin
  base_servo.write(180);
  cup_servo.attach(11); //our servo pin
  cup_servo.write(0);
  // delay(2000);
  // distance = readPing();
  // delay(100);
  // distance = readPing();
  // delay(100);
  // distance = readPing();
  // delay(100);
  // distance = readPing();
  // delay(100);

}

void loop(){

  // test();
  test2();
  Serial.println("==looping==");
  // delay(1000);

  // int distanceRight = 0;
  // int distanceLeft = 0;
  // delay(1000);
  // if (distance <= 20){
  //   moveStop();
  //   delay(300);
  //   moveBackward();
  //   delay(400);
  //   moveStop();
  //   delay(300);
  //   distanceRight = lookRight();
  //   delay(300);
  //   distanceLeft = lookLeft();
  //   delay(300);

  //   if (distance >= distanceLeft){
  //     turnRight();
  //     moveStop();
  //   }
  //   else{
  //     turnLeft();
  //     moveStop();
  //   }
  // }
  // else{
  // moveForward();
  
  // }
    // distance = readPing();
}

// int lookRight(){  
//   servo_motor.write(50);
//   delay(500);
//   int distance = readPing();
//   delay(100);
//   servo_motor.write(115);
//   return distance;
// }

// int lookLeft(){
//   servo_motor.write(170);
//   delay(500);
//   int distance = readPing();
//   delay(100);
//   servo_motor.write(115);
//   return distance;
//   delay(100);
// }

int readPing(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);
  return distance;
}

void moveStop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void moveForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);

  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(enA, 50);
  analogWrite(enB, 55.2);
}

void moveBackward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  analogWrite(enA, 50);
  analogWrite(enB, 52);
}

void turnRight(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  analogWrite(enA, 50);
  analogWrite(enB, 50);
  delay(500);
  moveStop();
}

void turnLeft(){
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(enA, 50);
  analogWrite(enB, 50);
  delay(500);
  moveStop();

}

unsigned short lfsr = 0xACE1u;
unsigned bit;

int rand() {
    bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    lfsr = (lfsr >> 1) | (bit << 15);

    return (bit == 0) ? 0 : 1; // Return 0 if bit is 0, otherwise return 1
}

void testPixy() {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
    found = true;
  }
}

void servoMoveToAngle(Servo servo_, int& startAngle, int targetAngle, unsigned long duration) {
    unsigned long startTime = millis();  // Get the current time
    while (millis() - startTime <= duration) {
        float progress = (millis() - startTime) / (float)duration;  // Calculate the progress (0.0 to 1.0)
        int angle = startAngle + (targetAngle - startAngle) * progress;  // Calculate the interpolated angle
        servo_.write(angle);  // Set the servo angle
    }
    servo_.write(targetAngle);  // Ensure that the servo reaches the target angle accurately
    startAngle = targetAngle;  // Update the current angle property
}

void test(){
  if(found){
    moveStop();
    delay(2000);
    found = false;
    turnLeft();
    turnLeft();
  }
  else{

  
  int dist = readPing();
  Serial.print("Distance: ");
  Serial.println(dist);
  if (dist <= 30){
    moveStop();
    delay(100);
    moveBackward();
    delay(600);
    moveStop();
    delay(100);
    if(rand() == 0){
      turnLeft();
    }
    else{
      turnRight();
    }
  }
  else
  {
    moveForward();
  }
  testPixy();
  }
  // turnLeft();

  // delay(2000);

  // moveBackward();

  // delay(2000);

  // turnRight();

  // delay(2000);
  // moveBackward();
  // delay(2000);
  // turnLeft();
  // delay(2000);
  // moveForward();
  // delay(2000);
  // turnRight();
  // delay(2000);
}
void test2(){
  // Servo spins forward at full speed for 1 second.
  // servoMoveToAngle(base_servo, base_servo_angle, 180, 2000);
  // // // servoMoveToAngle(cup_servo, cup_servo_angle, 0, 500);
  // delay(1000);
  // servoMoveToAngle(base_servo, base_servo_angle, 90, 2000);
  // // servoMoveToAngle(cup_servo, cup_servo_angle, 90, 2000);
  // delay(1000);
  // // // Servo is stationary for 1 second.
  // servoMoveToAngle(base_servo, base_servo_angle, 70, 2000);
  // // servoMoveToAngle(cup_servo, cup_servo_angle, 0, 500);
  // delay(1000);
  // servoMoveToAngle(base_servo, base_servo_angle, 90, 2000);
  // // // servoMoveToAngle(cup_servo, cup_servo_angle, 0, 500);
  // delay(1000);
  

  // base_servo.write(0);
  // delay(1000);
  // base_servo.write(90);
  // delay(1000);
  // base_servo.write(180);
  // delay(1000);
  // base_servo.write(90);
  // delay(1000);

}