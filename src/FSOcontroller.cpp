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
    for (int sfp=2; sfp<8; sfp++){
        sfps[sfp]->disable();
    }
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
#ifndef DISABLE_FAST_POWER_POLL
        ThisThread::sleep_for(POWER_POLL_SLEEP);
#endif
    }
}

void FSOcontroller::disableSFPs(){
    for (int sfp = 0; sfp<8; sfp++){
        sfps[sfp]->disable();
    }
}

void FSOcontroller::pollForPower(){
#ifdef DISABLE_POWER_POLL
    return;
#endif

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

    //if highest on same fibre as before and is above the low power threshold don't route anything
    if ((SFPpowers[highestPowerSFP] > SFP_LOW_POWER_THRESHOLD) && (highestPowerSFP == prevHighestPowerSFP)){ //if it's still the highest power don't switch
        return;
    }

    //All TX On, Power threshold now exceeded so turn 6 of the 7 off
    if (allOnAfterLowPower && (SFPpowers[highestPowerSFP] > SFP_LOW_POWER_THRESHOLD)){
        xpoints->routeTX(highestPowerSFP);
        for (int sfp = 1; sfp<8; sfp++){
            if (sfp == highestPowerSFP){ //if highest, leave enabled else turn off
                continue;
            }
            sfps[sfp]->disable();
        }
        allOnAfterLowPower = false;
    }else if (allOnAfterLowPower){ //All TX on, opwer threshold not exceeded, keep all on
        return;
    }
    else if (SFPpowers[highestPowerSFP] < SFP_LOW_POWER_THRESHOLD){ //All TX off and highest is too weak so turn all on
        xpoints->routeAllTX();
        for (int sfp = 1; sfp<8; sfp++){
            sfps[sfp]->enable();
        }
        allOnAfterLowPower=true;
    }else{ //normal switch, 1 fibre tx to a different fibre tx, power is above threshold
        xpoints->routeTX(highestPowerSFP);
    }
    prevHighestPowerSFP = highestPowerSFP;

#endif 
}

