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
        SFPpowers.reserve(7); //allocate memory for 7 power measurements
#ifndef ROUTE_TX_ONLY_ONE_FIBRE //route all if doing all
    xpoints->routeAllTX(); 
    for (int sfp=0; sfp<8; sfp++){
        sfps[sfp]->enableTX();
    }
#else //If on one fibre on at a time operation
    xpoints->routeTX(1);
    sfps[0]->enableTX(); //master sfp enable
    sfps[1] ->enableTX(); //sfp 1, default
    for (int sfp=2; sfp<8; sfp++){
        sfps[sfp]->disableTX(); //ensure other TX are off
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
#ifdef POLL_SPEED_TEST
    t.start();
#endif

    while(true){
        pollForPower();
        nominalRunningLED = !nominalRunningLED;
#ifdef POLL_SPEED_TEST
    pollCounter++;
    if (pollCounter == 10000){
        t.stop();
        printf("Time taken for 10000 polls = %d milliseconds\n", t.read_ms());
        pollCounter = 0;
        t.reset();
        t.start();
    }
    
#endif
#ifdef DISABLE_FAST_POWER_POLL
        ThisThread::sleep_for(POWER_POLL_SLEEP);
#endif
    }
}

void FSOcontroller::disableSFPs(){
    for (int sfp = 0; sfp<8; sfp++){
        sfps[sfp]->disableTX();
    }
}

void FSOcontroller::pollForPower(){
#ifdef DISABLE_POWER_POLL
    return;
#endif

    for (int sfp=1; sfp<8; sfp++){
        SFPpowers[sfp-1] = sfps[sfp]->getRXPower();
    }

#ifdef DEBUG_OUTPUT_POWERS
#ifdef DEBUG_OUTPUT_POWERS_DBM
    printf("POWERS (dBm): ");
    float powerdBm;
    for (int sfp=1; sfp<8; sfp++){
        powerdBm = 10*log10(SFPpowers[sfp-1]*POWER_READING_CONV_DBM);
        printf("%.2f  ", powerdBm);
    }
    printf("\n");
#else
    printf("POWERS (uW): ");
    for (int sfp=1; sfp<8; sfp++){
        printf("%d  ", (int) SFPpowers[sfp-1]*POWER_READING_CONV_UW);
    }
    printf("\n");
#endif
#endif

//search for highest power sfp
    highestPowerSFP = 1; 
    for (int sfp =2; sfp<8; sfp++){     
        if (SFPpowers[sfp-1]>SFPpowers[highestPowerSFP-1]){
            highestPowerSFP = sfp;
        }
    }

#ifdef VERBOSE_XPOINT_SWITCH_DEBUG 
    printf("highest power SFP: %d\n", highestPowerSFP);
#endif

#ifdef ROUTING_TEST
    return; //if routing test skip routing based on highest power and use buttons
#endif     
    
    xpoints->routeRX(highestPowerSFP);

//forced switching for polling test
#ifdef POWER_POLL_TEST_FORCE_SWITCH

#ifdef POWER_POLL_FORCE_SWITCH_TX
    xpoints->routeTX(currentToggle + 1);
#endif
#ifdef  POWER_POLL_FORCE_SWITCH_RX
    xpoints->routeRX(currentToggle + 1);
    
#endif
#ifdef POWER_POLL_FORCE_TOGGLE_DISABLE
if (currentToggle==1){
    sfps[1]->enableTX();
    sfps[2]->disableTX();
}else{
    sfps[1]->disableTX();
    sfps[2]->enableTX();
}

#endif
    currentToggle = (currentToggle + 1) %2;
    return;
#endif

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
            sfps[sfp]->disableTX();
        }
        allOnAfterLowPower = false;
    }else if (allOnAfterLowPower){ //All TX on, opwer threshold not exceeded, keep all on
        return;
    }
    else if (SFPpowers[highestPowerSFP] < SFP_LOW_POWER_THRESHOLD){ //All TX off and highest is too weak so turn all on
        xpoints->routeAllTX();
        for (int sfp = 1; sfp<8; sfp++){
            sfps[sfp]->enableTX();
        }
        allOnAfterLowPower=true;
    }else{ //normal switch, 1 fibre tx to a different fibre tx, power is above threshold
        xpoints->routeTX(highestPowerSFP);
        sfps[prevHighestPowerSFP]->disableTX();
        sfps[highestPowerSFP]->enableTX();

    }
    prevHighestPowerSFP = highestPowerSFP;

#endif 
}

