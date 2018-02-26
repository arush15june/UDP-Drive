#include "Arduino.h"
#include "DifferentialDrive.h"

/*  
*   Constructor Parameters 
*   ( pins[rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB], rightDefaultSpeed, leftDefaultSpeed ) 
*   
*/    

DifferentialDrive::DifferentialDrive() {
  
}

DifferentialDrive::DifferentialDrive(int pins[],int rDS, int lDS) {
  rightMotorEnable = pins[0];
  rightMotorDirF = pins[1];
  rightMotorDirB = pins[2];
  
  leftMotorEnable = pins[3];
  leftMotorDirF = pins[4];
  leftMotorDirB = pins[5];

  rightDefaultSpeed = rDS;
  leftDefaultSpeed = lDS;

  pinMode(rightMotorEnable,OUTPUT);
  pinMode(rightMotorDirF,OUTPUT);
  pinMode(rightMotorDirB,OUTPUT);

  pinMode(leftMotorEnable,OUTPUT);
  pinMode(leftMotorDirF,OUTPUT);
  pinMode(leftMotorDirB,OUTPUT);
  
}

void DifferentialDrive::forward() {
  //      Right Motor 
  analogWrite(rightMotorEnable, rightDefaultSpeed);
  digitalWrite(rightMotorDirF, HIGH);
  digitalWrite(rightMotorDirB, LOW);
  //      Left Motor 
  analogWrite(leftMotorEnable, leftDefaultSpeed);
  digitalWrite(leftMotorDirF, HIGH);
  digitalWrite(leftMotorDirB, LOW);      
}

void DifferentialDrive::backward() {
  //      Right Motor 
  analogWrite(rightMotorEnable, rightDefaultSpeed);
  digitalWrite(rightMotorDirF, LOW);
  digitalWrite(rightMotorDirB, HIGH);
  //      Left Motor 
  analogWrite(leftMotorEnable, leftDefaultSpeed);
  digitalWrite(leftMotorDirF, LOW);
  digitalWrite(leftMotorDirB, HIGH);      
}

void DifferentialDrive::left() {
  //      Right Motor 
  analogWrite(rightMotorEnable, rightDefaultSpeed);
  digitalWrite(rightMotorDirF, LOW);
  digitalWrite(rightMotorDirB, HIGH);
  //      Left Motor 
  analogWrite(leftMotorEnable, leftDefaultSpeed);
  digitalWrite(leftMotorDirF, HIGH);
  digitalWrite(leftMotorDirB, LOW);      
}

void DifferentialDrive::right() {
  //      Right Motor 
  analogWrite(rightMotorEnable,rightDefaultSpeed);
  digitalWrite(rightMotorDirF,HIGH);
  digitalWrite(rightMotorDirB,LOW);
  //      Left Motor 
  analogWrite(leftMotorEnable,leftDefaultSpeed);
  digitalWrite(leftMotorDirF,LOW);
  digitalWrite(leftMotorDirB,HIGH);      
}

void DifferentialDrive::stop() {
  //      Right Motor 
  analogWrite(rightMotorEnable,0);
  digitalWrite(rightMotorDirF,LOW);
  digitalWrite(rightMotorDirB,LOW);
  //      Left Motor 
  analogWrite(leftMotorEnable,0);
  digitalWrite(leftMotorDirF,LOW);
  digitalWrite(leftMotorDirB,LOW);      
}
