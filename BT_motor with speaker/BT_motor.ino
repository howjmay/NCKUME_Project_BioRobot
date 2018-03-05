#include <SoftwareSerial.h> 
#include <Wire.h>  


const int UP = 1, DOWN = 2, RIGHT = 3, LEFT = 4, FRONT = 5, BACK = 6;


SoftwareSerial BT(10,11); //(RX, TX)

const int motor1_relay1 = 3, motor1_relay2 = 4;
const int motor2_relay1 = 5, motor2_relay2 = 6;
const int screw_relay1 = 8, screw_relay2 = 9;
const int BUZZ = 10;

int dir = 0;

// idle
long int itime = 0;
long int buzz_time = 0;

void setup() { 
  Serial.begin(9600);  
  BT.begin(9600);
  pinMode(motor1_relay1, OUTPUT);
  pinMode(motor1_relay2, OUTPUT);
  pinMode(motor2_relay1, OUTPUT); 
  pinMode(motor2_relay2, OUTPUT);
  
  pinMode(screw_relay1, OUTPUT);
  pinMode(screw_relay2, OUTPUT);
  
  digitalWrite(motor1_relay1, LOW);
  digitalWrite(motor1_relay2, LOW);
  digitalWrite(motor2_relay1, LOW);
  digitalWrite(motor2_relay2, LOW);

  digitalWrite(screw_relay1, LOW);
  digitalWrite(screw_relay2, LOW);
} 

void loop() { 

  char cmd; 
  if (BT.available() > 0)   //whether receive the data
  {
    itime = millis();
    cmd = BT.read();
    
    if(cmd == 'u')
    { 
      //Serial.println("u");
      dir = 1;
    }
    if(cmd == 'd')
    { 
      //Serial.println("d");
      dir = 2;
    }
    if(cmd == 'l')
    {
      //Serial.println("l");
      dir = 3;
    }
    if(cmd == 'r')
    {
      //Serial.println("r");
      dir = 4;
    }
    if(cmd == 'f')
    {
      //Serial.println("f");
      dir = FRONT;
    }
    if(cmd == 'b')
    {
      //Serial.println("b");
      dir = BACK;
    }
    if(cmd == 'e')
    {
      //Serial.println("e");
      dir = 0;
    }
    if(cmd == 'z')
    {
      //Serial.println("z");
      digitalWrite(BUZZ, HIGH);
      buzz_time = millis();
    }
    dir_ctrl(dir);
  }
  
  
  if(millis() - buzz_time  > 500)
  {
    digitalWrite(BUZZ, LOW);
  }
  
  if( (millis() - itime) > 500)
  {
    //Serial.println("accidently dicnt");
    dir_ctrl(1100);
  }
  
}
void dir_ctrl(int dir){
    switch(dir)
    {
    case UP:
      //Serial.println(UP);
      digitalWrite(motor1_relay1, HIGH);
      digitalWrite(motor1_relay2, HIGH);
      digitalWrite(motor2_relay1, LOW);
      digitalWrite(motor2_relay2, LOW);
     break;
    case DOWN:
      //Serial.println(DOWN);
      digitalWrite(motor1_relay1, LOW);
      digitalWrite(motor1_relay2, LOW);
      digitalWrite(motor2_relay1, HIGH);
      digitalWrite(motor2_relay2, HIGH);
     break;
    case RIGHT:
      //Serial.println(RIGHT);
      digitalWrite(motor1_relay1, HIGH);
      digitalWrite(motor1_relay2, HIGH);
      digitalWrite(motor2_relay1, HIGH);
      digitalWrite(motor2_relay2, HIGH);
      break;
    case LEFT:
      //Serial.println(LEFT);
      digitalWrite(motor1_relay1, LOW);
      digitalWrite(motor1_relay2, LOW);
      digitalWrite(motor2_relay1, LOW);
      digitalWrite(motor2_relay2, LOW);
      break;
    case FRONT:
      //Serial.println("FRONT");
      digitalWrite(screw_relay1, HIGH);
      digitalWrite(screw_relay2, HIGH);
      break;  
    case BACK:
      //Serial.println("BACK");
      digitalWrite(screw_relay1, LOW);
      digitalWrite(screw_relay2, LOW);
      break;
    default:
      //Serial.println("Stop");
      digitalWrite(motor1_relay1, LOW);
      digitalWrite(motor1_relay2, HIGH);
      digitalWrite(motor2_relay1, LOW);
      digitalWrite(motor2_relay2, HIGH);

      digitalWrite(screw_relay1, LOW);
      digitalWrite(screw_relay2, HIGH);
    }
}


