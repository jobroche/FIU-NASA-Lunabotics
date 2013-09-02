/*****************************************************
 * DIP Switches as per the wized:
 * Pin 1 - ON
 * Pin 2 - OFF
 * Pin 3 - ON
 * Pin 4 - OFF
 * Pin 5 - ON
 * Pin 6 - ON
 ****************************************************/

#include "Sabertooth.h"

const int SABER_TX_PIN = 8; //transmission/output
const int SABER_RX_PIN = 12; //input
const int SABER_MOTOR1_FULL_FORWARD = 127;
const int SABER_MOTOR1_STOP = 64;
const int SABER_MOTOR1_FULL_REVERSE = 1;
const int SABER_MOTOR2_FULL_FORWARD = 255;
const int SABER_MOTOR2_STOP = 192;
const int SABER_MOTOR2_FULL_REVERSE = 128;
const int SABER_ALL_STOP = 0;
unsigned char current_engine_speed1 = 0;
unsigned char current_engine_speed2 = 0;

SoftwareSerial SaberSerial(SABER_RX_PIN, SABER_TX_PIN);


Sabertooth::Sabertooth(){init();}

Sabertooth::~Sabertooth(){};

void Sabertooth::init()
{

    /*pinMode(SABER_TX_PIN, OUTPUT); // Init software UART to communicate 

    SaberSerial.begin(9600);  
    Serial.println("Starting sabertooth...");
    delay(2000); 
    Serial.println("Started sabertooth..."); */
    setSpeed(SABER_ALL_STOP); //start with engines stopped
}


void Sabertooth::setSpeed(char motor_speed) //input percentage -100 to +100
{

  unsigned char cSpeedVal_Motor1 = 0;
  unsigned char cSpeedVal_Motor2 = 0;



  if(motor_speed == 0)
  {
    // Send and set motors to 0 speed
    SaberSerial.write((byte)0); //**************MAKE SURE THIS WORKS
    SaberSerial.write((byte)0); 

    current_engine_speed1 = 0;
    current_engine_speed2 = 0;
    Serial.println("Stopped from Sabertooth!");

    return;
  }  


  if(motor_speed >= 100) //100% forward
  {
    cSpeedVal_Motor1 = SABER_MOTOR1_FULL_FORWARD;
    cSpeedVal_Motor2 = SABER_MOTOR2_FULL_FORWARD;
    Serial.println("moving forward from sabertooth!");
  }
  else if(motor_speed <= -100) //100% reverse
  {
    cSpeedVal_Motor1 = SABER_MOTOR1_FULL_REVERSE;
    cSpeedVal_Motor2 = SABER_MOTOR2_FULL_REVERSE;
  }
  else
  {
    // Calc motor speeds (Final value ranges from 1 to 127)
    cSpeedVal_Motor1 = map(motor_speed, -100, 100, SABER_MOTOR1_FULL_REVERSE, SABER_MOTOR1_FULL_FORWARD);
    cSpeedVal_Motor2 = map(motor_speed, -100, 100, SABER_MOTOR2_FULL_REVERSE, SABER_MOTOR2_FULL_FORWARD);
  }

  // Fire the values off to the Sabertooth motor controller
  SaberSerial.write(cSpeedVal_Motor1); 
  SaberSerial.write(cSpeedVal_Motor2); 


  current_engine_speed1 = cSpeedVal_Motor1;
  current_engine_speed2 = cSpeedVal_Motor2;

}


