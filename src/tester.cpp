#include "tester.h"

testClass::testClass(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints):
    gpios(gpios),
    i2cbufs(i2cbufs),
    xpoints(xpoints)
{   
    gpios->registerInterrupt(0, this);

    // gpios->registerInterrupt(1, this);
    // gpios->registerInterrupt(2, this);
    // gpios->registerInterrupt(3, this);    
}

void testClass::interrupt(){
    ERROR_LED.write(0);
    printf("test interrupt\n");
}

void testClass::toggleDebugGPIO(){
    // //gpios->write(GPIO_DEBUG_LOOP_A, 1);
    // //gpios->write(GPIO_DEBUG_LOOP_A, 0);
    // gpios->write(GPIO_DEBUG_LOOP_A, 0);
    // gpios->write(GPIO_DEBUG_LOOP_B, 0);


    while(true){
        gpios->write(GPIO_DEBUG_LED, 0);

        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);

        gpios->write(GPIO_DEBUG_LED, 1);
        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);
        ;
    }
}

void testClass::I2CbufferTest(){
     //buf 0 (sfps 1234) on i2cB
     //buf 1 sfps567out on i2cA
    i2cbufs->reset();
    //char dummyData[2] = {0xB0, 0x0B};
    char dummyData[1] = {96};

    while(true){
        for (int i = 1; i<5; i++){
            i2cbufs->selectSFP(i);
            I2CB.write(SFP_I2C_ADDRESS, &dummyData[0], 1);
        }
        for (int j = 5; j<8; j++){
            i2cbufs->selectSFP(j);
            I2CA.write(SFP_I2C_ADDRESS, &dummyData[0], 1);
        }
        //sfp out
        i2cbufs->selectSFP(0);
        I2CA.write(SFP_I2C_ADDRESS, &dummyData[0], 1);
        ThisThread::sleep_for(1000ms);
    }
}

void testClass::XPointsTest(){
    //xpoints->reset();
    xpoints->routeRX(1);
    while(true){
        //xpoints->routeAllTX();
        //xpoints->routeRX(1);
        for (int sfp = 1; sfp<8; sfp++){
            xpoints->routeTX(sfp);
        }
        ThisThread::sleep_for(1000ms);
    }
}

//alex test using motor buttons
#ifdef ALEX_TEST
void testClass:XPointsToggleTX1(){
    if (!TX1){
        xpoints->routeTX(1);
    }
}

#endif