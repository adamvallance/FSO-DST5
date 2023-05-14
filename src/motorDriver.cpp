#include "motorDriver.h"


MotorDriver::MotorDriver(PinName* motorControlsOut, PinName* motorButtonInputs, FullExpandedGPIO* gpios):
    gpios(gpios),
    //initialise member digital outputs which are static based on the input list of pin names
    motor1Step(motorControlsOut[0], 0),
    motor1Dir(motorControlsOut[1], 0),
    motor2Step(motorControlsOut[2], 0),
    motor2Dir(motorControlsOut[3], 0), 
    //initialise member interrupt inputs 
    motorDirCtrlUp(motorButtonInputs[0]),
    motorDirCtrlDown(motorButtonInputs[1]),
    motorDirCtrlLeft(motorButtonInputs[2]),
    motorDirCtrlRight(motorButtonInputs[3])

{   //settings for motors
    gpios->write(GPIO_MOTOR_1_ADEC, 1);//smart tune to minimize ripple
    gpios->write(GPIO_MOTOR_2_ADEC, 1);//smart tune to minimize ripple
    
    gpios->write(GPIO_MOTOR_1_DEC0_OE_N, 0); //write logic high to dec0
    gpios->write(GPIO_MOTOR_1_DEC0, 1); 
    gpios->write(GPIO_MOTOR_2_DEC0_OE_N, 0); //write logic high to dec1
    gpios->write(GPIO_MOTOR_2_DEC0, 1); 

    //Current scalar torque DAC 11 for 100 ZZ for 50 see datasheet for more
    //try 50
    gpios->write(GPIO_MOTOR_1_I0_OE_N, 1);
    gpios->write(GPIO_MOTOR_2_I0_OE_N, 1);

    //disable microstepping
    gpios->write(GPIO_MOTOR_1_M0_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_1_M0, 0); 
    gpios->write(GPIO_MOTOR_2_M0_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_2_M0, 0); 


    //set toff to 30us (longest)
    gpios->write(GPIO_MOTOR_1_TOFF_OE_N, 0);// logic 1
    gpios->write(GPIO_MOTOR_1_TOFF, 1);
    gpios->write(GPIO_MOTOR_2_TOFF_OE_N, 0);
    gpios->write(GPIO_MOTOR_2_TOFF, 1); 
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

void MotorDriver::wakeUp(){
    if (isAsleep){
        gpios->write(GPIO_MOTOR_1_SLEEP_N, 1); //wake up motors
        gpios->write(GPIO_MOTOR_2_SLEEP_N, 1);
        gpios->write(GPIO_MOTOR_1_ENBL_N, 0);//enable motor outputs
        gpios->write(GPIO_MOTOR_2_ENBL_N, 0);//enable motor outputs
    }else{
        //reset timeout
        sleepTimeout.detach();

    }
    sleepTimeout.attach(callback(this, &MotorDriver::sleep), MOTOR_SLEEP_TIMEOUT);
    isAsleep = false;


}


void MotorDriver::sleep(){
    gpios->write(GPIO_MOTOR_1_SLEEP_N, 0); //set motors to sleep
    gpios->write(GPIO_MOTOR_2_SLEEP_N, 0);
    gpios->write(GPIO_MOTOR_1_ENBL_N, 1);//disable motor outputs
    gpios->write(GPIO_MOTOR_2_ENBL_N, 1);//disable motor outputs
    isAsleep = true;
}
//periodically wakes up sleeping thread. An interrupt will alternatively wake up thread.
void MotorDriver::exec(){
    while(true){
        if (azStepTriggered){
            wakeUp();

            stepTickerAz.attach(callback(this, &MotorDriver::doHalfStepAz), HALF_STEP_TIME);
            stopAzStepping.attach(callback(this, &MotorDriver::stopStepAz), TIME_MOTOR_STEPPING); //replace this to allow for variable number of steps
            azStepTriggered= false;
            currentlyStepping = true;
        }
        if (elStepTriggered){
            wakeUp();
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
    stopAzStepping.detach();
    azStepTriggered = false;
    currentlyStepping = false;
    motor1Step=0;
}


void MotorDriver::doHalfStepEl(){
    motor2Step = !motor2Step;
}
void MotorDriver::stopStepEl(){
    stepTickerEl.detach();
    stopElStepping.detach();
    elStepTriggered = false;
    currentlyStepping = false;
    motor2Step = 0;
}

void MotorDriver::interrupt(){
    //This means motor1fault or motor2fault
    printf("Motor fault");
    ERROR_LED.write(0);
}