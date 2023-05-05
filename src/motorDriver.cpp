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
    
    ;
}

void MotorDriver::start(){
    //register interrupt callbacks
    motorDirCtrlUp.fall(callback(this, &MotorDriver::stepUp));
    motorDirCtrlDown.fall(callback(this, &MotorDriver::stepDown));
    motorDirCtrlLeft.fall(callback(this, &MotorDriver::stepLeft));
    motorDirCtrlRight.fall(callback(this, &MotorDriver::stepRight));

    exec();
}

//periodically wakes up sleeping thread. An interrupt will alternatively wake up thread.
void MotorDriver::exec(){
    while(true){
        if (azStepTriggered){
            stepTickerAz.attach(callback(this, &MotorDriver::doHalfStepAz), HALF_STEP_TIME);
            stopAzStepping.attach(callback(this, &MotorDriver::stopStepAz), TIME_MOTOR_STEPPING); //replace this to allow for variable number of steps
            azStepTriggered= false;
            currentlyStepping = true;
        }
        if (elStepTriggered){
            stepTickerEl.attach(callback(this, &MotorDriver::doHalfStepEl), HALF_STEP_TIME);
            stopElStepping.attach(callback(this, &MotorDriver::stopStepEl), TIME_MOTOR_STEPPING); //replace this to allow for variable number of steps
            elStepTriggered = false;
            currentlyStepping = true;
        }
        ThisThread::sleep_for(BLOCKING_SLEEP);
    }
}

//test version which simply toggles a gpio. 
void MotorDriver::stepMotor(int direction){
    if (currentlyStepping){
        return;//skip if one already in progress
    }
    switch (direction) {
        case 0: 
            motor1Dir = ELEVATION_STEP_DIR_UP;
            azStepTriggered = true;
            //step up;
            break;
        case 1:
            motor1Dir = ELEVATION_STEP_DIR_DOWN;
            azStepTriggered = true;

            //step down;
            break;
        case 2:
            motor2Dir = AZIMUTH_STEP_DIR_LEFT;
            elStepTriggered = true;
            //step left;
            break;
        case 3:
            motor2Dir = AZIMUTH_STEP_DIR_RIGHT;
            elStepTriggered = true;
            //step right;
            break;
    };


};

void MotorDriver::doHalfStepAz(){
    motor1Step = !motor1Step;
}
void MotorDriver::stopStepAz(){
    stepTickerAz.detach();
    azStepTriggered = false;
    currentlyStepping = false;
}


void MotorDriver::doHalfStepEl(){
    motor2Step = !motor2Step;
}
void MotorDriver::stopStepEl(){
    stepTickerEl.detach();
    elStepTriggered = false;
    currentlyStepping = false;
}
