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

void MotorDriver::exec(){
    while(true){
        ThisThread::sleep_for(BLOCKING_SLEEP);
    }
}
//test version which simply toggles a gpio. 
void MotorDriver::stepMotor(int direction){
    switch (direction) {
        case 0: 
            motor1Step = !motor1Step; //DEBUG ADD PROPER LOGIC HERE LATER
            //step up;
            break;
        case 1:
            motor1Dir = !motor1Dir;
            //step down;
            break;
        case 2:
            motor2Step = !motor2Step;
            //step left;
            break;
        case 3:
            motor2Dir = !motor2Dir;
            //step right;
            break;
    }

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