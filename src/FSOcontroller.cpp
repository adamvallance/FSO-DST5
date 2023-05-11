#include "FSOcontroller.h"

//global error led
DigitalOut ERROR_LED(PIN_FRDM_LED_RED, 1);

FSOcontroller::FSOcontroller(PinName* pins, FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints): // I2C* I2CA
    nominalRunningLED(pins[0], 0), //active low 
    fanPWM(pins[1]), 
    gpios(gpios),
    i2cbufs(i2cbufs),
    xpoints(xpoints)
    {   
        SFPpowers.reserve(7);
#ifndef ROUTE_TX_ONLY_ONE_FIBRE
    xpoints->routeAllTx();
#else
    xpoints->routeTX(1);
#endif
}

void FSOcontroller::start(){
    fanPWM.period(FAN_PWM_PERIOD);
    fanPWM.write(FAN_PWM_DUTY);
    exec();
}

void FSOcontroller::exec(){
    printf("Initialisation complete. Beginning power tracking.\n");
    while(true){
        pollForPower();
        nominalRunningLED = !nominalRunningLED;
        //ThisThread::sleep_for(POWER_POLL_SLEEP);
    }
}

void FSOcontroller::disableSFPs(){
    for (int sfp = 0; sfp<8; sfp++){
        sfps[sfp]->disable();
    }
}

void FSOcontroller::pollForPower(){
    for (int sfp=1; sfp<8; sfp++){
        SFPpowers[sfp-1] = sfps[sfp]->getPower();
    }
#ifdef DEBUG_OUTPUT_POWERS
        printf("POWERS ");
    for (int sfp=1; sfp<8; sfp++){
        printf("%.2f  ", SFPpowers[sfp-1]);
    }
    printf("\n");
#endif
          

    highestPowerSFP = std::distance(SFPpowers.begin(), std::max_element(SFPpowers.begin(), SFPpowers.end())) + 1; 

#ifdef ALEX_TEST
    return; //if alex test skip routing based on highest power
#endif     

    
    xpoints->routeRX(highestPowerSFP);
#ifdef ROUTE_TX_ONLY_ONE_FIBRE
        //if highest on same fibre and is above the low power threshold don't route anything
    if ((SFPpowers[highestPowerSFP] > SFP_LOW_POWER_THRESHOLD) && (highestPowerSFP == prevHighestPowerSFP)){ //if it's still the highest power don't switch
        return;
    }else{ 
        prevHighestPowerSFP = highestPowerSFP;
    }

    if (allOnAfterLowPower && (SFPpowers[highestPowerSFP] < SFP_LOW_POWER_THRESHOLD)){
        xpoints->routeTX(highestPowerSFP);
        allOnAfterLowPower = false;
    }
    else if (SFPpowers[highestPowerSFP] < SFP_LOW_POWER_THRESHOLD){
        xpoints->routeAllTX();
        allOnAfterLowPower=true;
    }else{ //normal switch, 1 fibre tx to a different fibre tx
        xpoints->routeTX(highestPowerSFP);

    }
#endif 
}

