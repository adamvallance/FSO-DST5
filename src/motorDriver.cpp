#include "motorDriver.h"

MotorDriver::MotorDriver(PinName* motorPins, FullExpandedGPIO* gpios):
    gpios(gpios),
    //initialise member digital outputs which are static based on the input list of pin names
    motor1Step(motorPins[0], 0),
    motor1Dir(motorPins[1], 0),
    motor2Step(motorPins[2], 0),
    motor2Dir(motorPins[3], 0), 
    //initialise member interrupt inputs 
    motorDirCtrlUp(motorPins[6]),
    motorDirCtrlDown(motorPins[7]),
    motorDirCtrlLeft(motorPins[4]),
    motorDirCtrlRight(motorPins[5]),
    led(motorPins[8])


{   //settings for motors
    //sleep();//sleep so these settings don't take effect immediately.
    //applySettings();
}
void MotorDriver::applySettings(){

    gpios->write(GPIO_MOTOR_1_ADEC, 1);//smart tune to minimize ripple
    gpios->write(GPIO_MOTOR_2_ADEC, 1);//smart tune to minimize ripple
    
    gpios->write(GPIO_MOTOR_1_DEC0_OE_N, 0); //write logic high to dec0
    gpios->write(GPIO_MOTOR_1_DEC0, 1); 
    gpios->write(GPIO_MOTOR_1_DEC1_OE_N, 0); //write logic high to dec0
    gpios->write(GPIO_MOTOR_1_DEC1, 1); 
    gpios->write(GPIO_MOTOR_2_DEC0_OE_N, 0); //write logic high to dec1
    gpios->write(GPIO_MOTOR_2_DEC0, 1); 
    gpios->write(GPIO_MOTOR_2_DEC1_OE_N, 0); //write logic high to dec1
    gpios->write(GPIO_MOTOR_2_DEC1, 1); 

    //Current scalar torque DAC 11 for 100 ZZ for 50 see datasheet for more
    ////try 50%
    // gpios->write(GPIO_MOTOR_1_I0_OE_N, 1);
    // gpios->write(GPIO_MOTOR_1_I1_OE_N, 1);
    // gpios->write(GPIO_MOTOR_2_I0_OE_N, 1);
    // gpios->write(GPIO_MOTOR_2_I1_OE_N, 1);

    // ////try 100%
    // gpios->write(GPIO_MOTOR_1_I0_OE_N, 0);//logic 1
    // gpios->write(GPIO_MOTOR_1_I0, 1);
    // gpios->write(GPIO_MOTOR_1_I1_OE_N, 0);//logic 1
    // gpios->write(GPIO_MOTOR_1_I1, 1);
    // gpios->write(GPIO_MOTOR_2_I0_OE_N, 0);//logic 1
    // gpios->write(GPIO_MOTOR_2_I0, 1);
    // gpios->write(GPIO_MOTOR_2_I1_OE_N, 0);//logic 1
    // gpios->write(GPIO_MOTOR_2_I1, 1);

        ////try 12.5%
    gpios->write(GPIO_MOTOR_1_I0_OE_N, 0);//logic 1
    gpios->write(GPIO_MOTOR_1_I0, 1);
    gpios->write(GPIO_MOTOR_1_I1_OE_N, 0);//logic 1
    gpios->write(GPIO_MOTOR_1_I1, 1);
    gpios->write(GPIO_MOTOR_2_I0_OE_N, 0);//logic 1
    gpios->write(GPIO_MOTOR_2_I0, 1);
    gpios->write(GPIO_MOTOR_2_I1_OE_N, 0);//logic 1
    gpios->write(GPIO_MOTOR_2_I1, 1);

    //disable microstepping
    gpios->write(GPIO_MOTOR_1_M0_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_1_M0, 0); 
    gpios->write(GPIO_MOTOR_1_M1_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_1_M1, 0); 

    gpios->write(GPIO_MOTOR_2_M0_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_2_M0, 0); 
    gpios->write(GPIO_MOTOR_2_M1_OE_N, 0); //logic 0
    gpios->write(GPIO_MOTOR_2_M1, 0); 

    //set toff to 30us (longest)
    gpios->write(GPIO_MOTOR_1_TOFF_OE_N, 0);// logic 1
    gpios->write(GPIO_MOTOR_1_TOFF, 1);
    gpios->write(GPIO_MOTOR_2_TOFF_OE_N, 0);
    gpios->write(GPIO_MOTOR_2_TOFF, 1); 
}


void MotorDriver::start(){
    //gpios->write(GPIO_MOTOR_1_SLEEP_N, 1); //wake up motors
    //gpios->write(GPIO_MOTOR_2_SLEEP_N, 1);
    // gpios->write(GPIO_MOTOR_1_ENBL_N, 0);//enable motor outputs
    // gpios->write(GPIO_MOTOR_2_ENBL_N, 0);//enable motor outputs
    exec();
}

void MotorDriver::readInputs(){
    if (motorDirCtrlUp.read() == 0){
        gpios->write(GPIO_DEBUG_LED, 0);
        motor2Dir.write(ELEVATION_STEP_DIR_UP);
        doStep(1);
    }else if (motorDirCtrlDown.read()==0){
        gpios->write(GPIO_DEBUG_LED, 0);
        motor2Dir.write(ELEVATION_STEP_DIR_DOWN);
        doStep(1);


    }
    else if (motorDirCtrlLeft.read()==0){
        gpios->write(GPIO_DEBUG_LED, 0);
        motor1Dir.write(AZIMUTH_STEP_DIR_LEFT);
        doStep(0);

    }
    else if (motorDirCtrlRight.read()==0){
        gpios->write(GPIO_DEBUG_LED, 0);
        motor1Dir.write(AZIMUTH_STEP_DIR_RIGHT);
        doStep(0);

    }

}

void MotorDriver::doStep(int motor){
    if (motor == 0){
        gpios->write(GPIO_MOTOR_1_ENBL_N, 0);
    }else{
        gpios->write(GPIO_MOTOR_2_ENBL_N, 0);
    }
    gpios->gpioExpanders[motor]->setPinDefaults(motor);
    if (motor == 0){
        gpios->write(GPIO_MOTOR_1_SLEEP_N, 1);
    }else{
        gpios->write(GPIO_MOTOR_2_SLEEP_N, 1);
    }
    applySettings();
    for (int i = 0; i< MOTOR_N_STEPS; i++){
        steps[motor]->write(1);
        ThisThread::sleep_for(HALF_STEP_TIME);
        //wait_us(HALF_STEP_TIME);
        steps[motor]->write(0);
        ThisThread::sleep_for(HALF_STEP_TIME);
        //wait_us(HALF_STEP_TIME);

    }
}


void MotorDriver::exec(){
    gpios->write(GPIO_MOTOR_1_SLEEP_N, 1);

    while(true){
        led = !led;
        readInputs();
        // gpios->write(GPIO_MOTOR_1_SLEEP_N, 0);
        // ThisThread::sleep_for(200ms);
        // gpios->write(GPIO_MOTOR_1_SLEEP_N, 1);
        ThisThread::sleep_for(200ms);
    }
}
