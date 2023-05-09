/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "FSOcontroller.h"



int main()
{   
    printf("Initialising...\n");

    FSOcontroller controller = {&FSO_CONTROLLER_PINS[0]};
    controller.start();
}