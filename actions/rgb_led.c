/*
 * rgb_led.c
 *
 *  Created on: 02.06.2024
 *      Author: felix
 */
#include "rgb_led.h"
#include "button.h"

const char *responsedef;


void RGBLed_SetColorSineWave(const char **response_button,int index, uint32_t sys_clk) {
    uint32_t ui32PWMClock = 1875000; // 120 MHz/64
    uint32_t ui32Load = ui32PWMClock / PWM_FREQUENCY - 1;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK); // Port K for Red and Green LEDs
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM); // Port M for Blue LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);  // PWM0 module

    // Wait for the GPIO and PWM modules to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)) {}

    // Configure the GPIO pins for PWM function.
    GPIOPinConfigure(GPIO_PK4_M0PWM6);  // Red LED on PK4 (M0PWM6)
    GPIOPinConfigure(GPIO_PK5_M0PWM7);  // Green LED on PK5 (M0PWM7)
    GPIOPinConfigure(GPIO_PM0_T2CCP0);  // Blue LED on PM0 (M0PWM0)

    GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_4);  // Set PK4 as PWM
    GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_5);  // Set PK5 as PWM
    GPIOPinTypePWM(GPIO_PORTM_BASE, GPIO_PIN_0);  // Set PM0 as PWM

    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);

    ui32PWMClock = 1875000;  // 120 MHz/64
    ui32Load = 18749;

    // Configure the PWM generator for count-down mode with immediate updates to the parameters.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);

    // Set the PWM period. For a 1kHz frequency, the period is (120000000 / 1000) - 1.
    uint32_t pwmPeriod = sys_clk / PWM_FREQUENCY - 1;
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, pwmPeriod);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, pwmPeriod);

    // Enable the PWM outputs.
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT | PWM_OUT_7_BIT | PWM_OUT_0_BIT, true);

    // Enable the PWM generators.
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    const float APP_PI = 3.14159265358979323846;
    const uint32_t STEPS = 256;
    uint32_t ui32Index = 0;
    float fAngle;
    uint32_t ui32RedLevel, ui32GreenLevel, ui32BlueLevel;
    int i = 0;
    while (i < 1000) {
        fAngle = ui32Index * (2.0f * APP_PI / STEPS);

        // Red LED
        ui32RedLevel = (uint32_t)(ui32Load / 2 * (1 + sinf(fAngle)));
        // Green LED
        ui32GreenLevel = (uint32_t)(ui32Load / 2 * (1 + sinf(fAngle + APP_PI / 2))); // 90 degrees phase shift
        // Blue LED
        ui32BlueLevel = (uint32_t)(ui32Load / 2 * (1 + sinf(fAngle + APP_PI))); // 180 degrees phase shift

        // Set the pulse width for each color
        switch (index) {
            case 0:
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, ui32RedLevel);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, ui32GreenLevel);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1);

                break;
            case 1:
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui32BlueLevel);
//                *response_button = wrongresponses[1];
                break;
            case 2:
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, ui32GreenLevel);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1);
//                *response_button = responses_index[1];
                break;
            default:
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, ui32RedLevel);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1);



                break;
        }

        ui32Index++;
        i++;
        if (ui32Index == STEPS) {
            ui32Index = 0;
        }

        // Delay to make the color transition visually pleasant
        SysCtlDelay(sys_clk / (STEPS * 3)); // approximately 3 seconds total delay
    }




    PWMGenDisable(PWM0_BASE, PWM_GEN_3);
    PWMGenDisable(PWM0_BASE, PWM_GEN_0);

        switch(index){
        case 0:
            *response_button = wrongresponses[0];
            break;

        case 1:
            *response_button = wrongresponses[1];
            break;

        case 2:
            responsedef = "Für den nächsten Teil des Passworts fragt einen server an der euch auf /button eine Nachricht zurück gibt.";
                    *response_button = ConcatenateStrings(responses_index[1],responsedef);
            break;

        default:
                            responsedef = " die stelle bekommt ihr wenn ihr das reine grün blinkende Licht findet per Anfrage auf /blink/%d %d = 0 1 2 ...";
                            *response_button = ConcatenateStrings(responses_ziffer[1],responsedef);
                            break;


        }
}



