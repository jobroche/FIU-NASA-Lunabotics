#ifndef Sabertooth_h
#define Sabertooth_h

#include "SoftwareSerial.h"
#include <Arduino.h>


class Sabertooth{
public:
    Sabertooth();
    ~Sabertooth();
    void init();
    void setSpeed(char);

};

#endif
