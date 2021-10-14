/*
 * This program will comunicate with ros in orther to move the wheels of the robot
 */

#include "Arduino.h"
#include <ros.h>
#include <std_msgs/Int32.h>

//Motores
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 6;
int motor2pin2 = 7;

//JoyStick
int VRx = A0;
int VRy = A1;
int SW = 2;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;


//Gloabl variables
ros::NodeHandle nh;
volatile int motor_vel; //

void fn_motor_adelante(){
  //adelante
    Serial.print("adelante");
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}
void fn_motor_atras(){
  //atrás
    Serial.print("atras");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
}
void fn_gira_izquierda(){
  //gira izquierda
    Serial.print("izquierda");
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
}
void fn_gira_derecha(){
  //gira derecha
    Serial.print("derecha");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
}

void fn_motor_alto(){
  //stop
    Serial.print("stop");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
}

//Motor callback
void motor_vel_cb(){
  
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  if(mapY < -200){fn_motor_adelante}
  if(mapY > 200){fn_motor_atras}
  if(mapX < -200){fn_gira_izquierda}
  if(mapX > 200){fn_gira_derecha}
  if((mapY>-200)&&(mapY<200)&&)
}

//Creates the ROS subscribers
ros::Subscriber<std_msgs::Int32> motor_vel_sub("arduino/motor_vel", motor_vel_cb);

//Arduino SETUP
void setup() {
  //JoyStick
  Serial.begin(9600); 
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  //Motores
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void loop(){
  nh.spinOnce();
  delay(1);
}
