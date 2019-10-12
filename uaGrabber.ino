// Includes the Servo library
#include <VarSpeedServo.h>

const int trigPin = 3;
const int echoPin = 11;
// VARATUT 4,5,6,7,8,10. Servolle 12, echo 11, trig 3.

VarSpeedServo myServo; // Creates a servo object for controlling the servo motor

int motorSpeed[] = {0,0};
long duration;
int distance;
int safetyDistance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // Motor Driver;
 // Motor_1 controll pin initiate;
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(9, OUTPUT); // Speed control

 // Motor_2 controll pin initiate;
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(10, OUTPUT);  // Speed control

 //Enable the Motor Shield output;
 pinMode(6, OUTPUT);
 digitalWrite(6, HIGH);

 myServo.attach(12, 544, 2400); // Defines on which pin is the servo motor attached
 myServo.write(0, 90);
 delay(1000);
}

void loop() {
  char firstChar;
  int value;

  distance = uasensor();
  delay(20);

  grabber(distance);

  if (Serial.available())
  {

    firstChar = Serial.read();

    if (firstChar == 'R' ||
        firstChar == 'L' ||
        firstChar == 'C')
    {
      value = Serial.parseInt();
      if (value > 255 || value < -255)
      {
        value = 0;
      }
    }
    else if(firstChar == 'G')
    {
      motorTask();
    }

    switch (firstChar)
    {
      case 'R': // Right Motor
        motorSpeed[0] = value;
        break;
      case 'L': // Left Motor
        motorSpeed[1] = value;
        break;
      case 'C':
        Serial.print("MUST_INVADE_");
        Serial.println(value*value); // Check code.
      default:
        break;
    }
  }

  delay(10);

  return;
}

void motorTask()
{
  if (motorSpeed[0] >= 0)
  {
    analogWrite(9, motorSpeed[0]);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }

  if (motorSpeed[0] < 0)
  {
    analogWrite(9, abs(motorSpeed[0]));
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }

  // ------------------

  if (motorSpeed[1] >= 0)
  {
    analogWrite(10, motorSpeed[1]);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
  }

  if (motorSpeed[1] < 0)
  {
    analogWrite(10, abs(motorSpeed[1]));
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
  }

  Serial.print(motorSpeed[0]);
  Serial.print(" ");
  Serial.print(motorSpeed[1]);
  Serial.println(" ");
}

void uasensor(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;

  //Serial.println(distance);
  //Serial.println(".");
  return distance
}

void grabber(distance){
  if(distance > 0 && distance < 12){
    myServo.write(140, 90);
    delay(20);
  } else {
    myServo.write(10, 90);
    delay(20);
  }
}
