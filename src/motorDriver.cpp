#include "motorDriver.h"


MotorDriver::MotorDriver(PinName* motorControlsOut, PinName* motorButtonInputs): 
    //initialise member digital outputs which are static based on the input list of pin names
    motor1Step(motorControlsOut[0], 1),
    motor1Dir(motorControlsOut[1], 1),
    motor2Step(motorControlsOut[2], 1),
    motor2Dir(motorControlsOut[3], 1), 
    //initialise member interrupt inputs 
    motorDirCtrlUp(motorButtonInputs[0]),
    motorDirCtrlDown(motorButtonInputs[1]),
    motorDirCtrlLeft(motorButtonInputs[2]),
    motorDirCtrlRight(motorButtonInputs[3])

    {   
        //register interrupt callbacks
        motorDirCtrlUp.fall(callback(this, &MotorDriver::stepUp));
        motorDirCtrlDown.fall(callback(this, &MotorDriver::stepDown));
        motorDirCtrlLeft.fall(callback(this, &MotorDriver::stepLeft));
        motorDirCtrlRight.fall(callback(this, &MotorDriver::stepRight));
        //check it's not an issue with this https://os.mbed.com/cookbook/FPointer

        //debug(0);

    
    ;//do other setup
}

void MotorDriver::debug(int direction){
    while (true) {
        //motorControls[0] = ! motorControls[0];
        motor1Step = !motor1Step;
        ThisThread::sleep_for(200ms);
    }
    //step in direction as indicated by input int
    ;
}

void MotorDriver::stepMotor(int direction){
    switch (direction) {
        case 0: 
            debug(0);
            //motor1Step = !motor1Step; //DEBUG ADD PROPER LOGIC HERE LATER
            //step up;
            break;
        case 1:
            //step down;
            break;
        case 2:
            //step left;
            break;
        case 3:
            //step right;
            break;
    }

};
