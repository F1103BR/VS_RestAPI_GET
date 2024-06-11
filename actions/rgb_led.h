#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "inc/hw_types.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include <math.h>
#include "Private/responses.h"


#define PWM_FREQUENCY 1000

void RGBLed_SetColorSineWave(const char **response_button,int index, uint32_t sys_clk);

#endif // RGB_LED_H
