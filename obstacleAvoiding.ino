
#include <Servo.h>
#include <NewPing.h>

const int rightFrontMotor = 4;
const int rightBackMotor = 5;
const int leftFrontMotor = 6;
const int leftBackMotor = 7;

#define trig_pin A2
#define echo_pin A1
#define max_distance 200

boolean goesForward = false;
int distance = 100;

Servo servo_motor;
NewPing sonar(trig_pin, echo_pin, max_distance);

void setup() {
  // put your setup code here, to run once:
  pinMode(rightFrontMotor, OUTPUT);
  pinMode(rightBackMotor, OUTPUT);
  pinMode(leftFrontMotor, OUTPUT);
  pinMode(leftBackMotor, OUTPUT);

  servo_motor.attach(9);
  Serial.begin(9600);

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}

void loop() {
//  servo_motor.write(170);
//  delay(1000);
//  servo_motor.write(50);
//  delay(1000);
  int distanceRight = 0;
  int distanceLeft = 0;
  Serial.println(distance);
  delay(50);

  if (distance <= 35) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);

    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if(distance >= distanceLeft) {
      turnRight();
      moveStop();
    }
    else {
      turnLeft();
      moveStop();
    }
  }

  else {
    moveForward();
  }

  distance = readPing();

}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();

  if(cm == 0) {
    cm = 250;
  }

  return cm;
}

int lookLeft() {
  servo_motor.write(50);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_motor.write(115);

  return distance;
}

int lookRight() {
  servo_motor.write(170);
  delay(500);

  int distance = readPing();
  delay(100);

  servo_motor.write(115);

  return distance;
}

void moveStop() {
  digitalWrite(rightFrontMotor, LOW);
  digitalWrite(rightBackMotor, LOW);
  digitalWrite(leftFrontMotor, LOW);
  digitalWrite(leftBackMotor, LOW); 
}

void moveForward() {
  if(!goesForward) {
    goesForward = true;

    digitalWrite(rightFrontMotor, HIGH);
    digitalWrite(leftFrontMotor, HIGH);

    digitalWrite(rightBackMotor, LOW);
    digitalWrite(leftBackMotor, LOW);
  }
}

void moveBackward() {
  goesForward = false;

  digitalWrite(rightBackMotor, HIGH);
  digitalWrite(leftBackMotor, HIGH);

  digitalWrite(rightFrontMotor, LOW);
  digitalWrite(leftFrontMotor, LOW);
}

void turnLeft() {
  digitalWrite(rightFrontMotor, HIGH);
  digitalWrite(rightBackMotor, LOW);

  digitalWrite(leftFrontMotor, LOW);
  digitalWrite(leftBackMotor, HIGH);

  delay(250);

  digitalWrite(rightFrontMotor, HIGH);
  digitalWrite(leftFrontMotor, HIGH);

  digitalWrite(rightBackMotor, LOW);
  digitalWrite(leftBackMotor, LOW);
}

void turnRight() {
  digitalWrite(leftFrontMotor, HIGH);
  digitalWrite(leftBackMotor, LOW);

  digitalWrite(rightFrontMotor, LOW);
  digitalWrite(rightBackMotor, HIGH);

  delay(250);

  digitalWrite(rightFrontMotor, HIGH);
  digitalWrite(leftFrontMotor, HIGH);

  digitalWrite(rightBackMotor, LOW);
  digitalWrite(leftBackMotor, LOW);
}
