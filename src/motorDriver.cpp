#include "motorDriver.h"

//constructor, initialises pins as required
MotorDriver::MotorDriver(PinName* pins, bool clockwiseSymbol): 
    //initialise member digital outputs which are static based on the input list of pin names
    motorStep(pins[0], 1),
    motorDir(pins[1], 1),

    //initialise member interrupt inputs 
    motorDirCtrlClockwise(pins[2]),
    motorDirCtrlAnticlockwise(pins[3]),
    clockwiseSymbol(clockwiseSymbol)

{   
    
    ;
}

void MotorDriver::start(){
    //register interrupt callbacks
    motorDirCtrlClockwise.fall(callback(this, &MotorDriver::stepCW));
    motorDirCtrlAnticlockwise.fall(callback(this, &MotorDriver::stepACW));

    exec();
}

void MotorDriver::exec(){
    while(true){
        ThisThread::sleep_for(BLOCKING_SLEEP);
        motorStep = !motorStep; //debug
    }
}

//test version which simply toggles a gpio. 

void MotorDriver::stepMotor(int direction){
    switch (direction) {
        //step clockwise
        case 0:
            motorDir = clockwiseSymbol;
            break;

        //step anticlockwise
        case 1:
            motorDir = !clockwiseSymbol;
            //step down;
            break;
        
        //do steps
    }
    motorStep = !motorStep; //DEBUG ADD PROPER LOGIC HERE LATER

};

// void MotorDriver::stepMotor(int direction){
//     finished == false;
//     while(finished == false){
//         switch (direction) {
//             case 0: 
//                 motor1Step = !motor1Step; //DEBUG ADD PROPER LOGIC HERE LATER
//                 //step up;
//                 break;
//             case 1:
//                 motor1Dir(motorControlsOut[1], 1),

//                 //step down;
//                 break;
//             case 2:
//                 //step left;
//                 break;
//             case 3:
//                 //step right;
//                 break;
//         }
//         ThisThread::sleep_until(Kernel::get_ms_count() + STEP_SLEEP_TIME);
//     }
// };