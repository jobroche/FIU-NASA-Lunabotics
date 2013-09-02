/*
 drive motor: http://www.dimensionengineering.com/datasheets/Sabertooth2x25v2.pdf
 linear actuator: http://www.dimensionengineering.com/datasheets/Sabertooth2x5.pdf
 
 Motor 1: 1-127
   + 127 is full forward
   + 1 is full reverse
   + 64 is stop
 Motor 2: 128-255
   +  255 is full forward
   +  128 is full reverse
   +  192 is stop
   
   TODO: linear actuators, full steering
 */

#include "WiFly.h"
#include "Credentials.h"
#include <SoftwareSerial.h>

Server server(800);
SoftwareSerial driveSerial(0,4); //rx(input),tx(output)

void setup() {
  
  Serial.begin(9600);  
  driveSerial.begin(9600);
  
  WiFly.begin();
  
  if (!WiFly.join(ssid, passphrase)) { 
    while (1) {
      Serial.println("error");
    }    
  }
  else {
    Serial.print("IP: ");
    Serial.println(WiFly.ip());
    server.begin();    
  }

}

void loop() {    
    
    while(SpiSerial.available() > 0) {

    int wifly_read = SpiSerial.read();
    
    if (wifly_read == 119) { //'w' forward
    
       driveSerial.write(127); //motor1 full forward
       driveSerial.write(255); //motor 2 full forward
       SpiSerial.println("Forward");
    }
    if (wifly_read == 64) { //'@' advanced mode
    
        SpiSerial.println(" -- advanced mode -- "); //0-9 where 0 = full reverse and 9 = full speed
        int aSpeed = SpiSerial.read();
        driveSerial.write(map(aSpeed, 0, 9, 1, 127)); //motor 1
        driveSerial.write(map(aSpeed, 0, 9, 128, 255)); //motor 2
    }
    else {
        driveSerial.write(byte(0));
    }

  }
}

