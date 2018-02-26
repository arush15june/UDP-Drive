#ifndef DifferentialDrive_h
#define DifferentialDrive_h

#include "Arduino.h"

class DifferentialDrive {
    
private:
    int rightMotorEnable;
    int rightMotorDirF;
    int rightMotorDirB;
    
    int leftMotorEnable;
    int leftMotorDirF;
    int leftMotorDirB;

    int leftDefaultSpeed;
    int rightDefaultSpeed;

public:
    DifferentialDrive();
    DifferentialDrive(int[], int, int);
    void forward();
    void backward();
    void left();
    void right();
    void stop();
};

#endif
