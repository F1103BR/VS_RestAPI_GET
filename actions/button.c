/*
 * button.c
 *
 *  Created on: 03.06.2024
 *      Author: felix
 */
#include "button.h"

const char *responsedef;
void Buttons_Init(void) {
    // Enable the peripherals for Port H and Port K
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);

    // Wait for the peripherals to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOH)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK)) {}

    // Configure button 1 (PH1) as input
    GPIOPinTypeGPIOInput(BUTTON1_PORT, BUTTON1_PIN);
    GPIOPadConfigSet(BUTTON1_PORT, BUTTON1_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // Enable weak pull-up

    // Configure button 2 (PK6) as input
    GPIOPinTypeGPIOInput(BUTTON2_PORT, BUTTON2_PIN);
    GPIOPadConfigSet(BUTTON2_PORT, BUTTON2_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); // Enable weak pull-up
}
void Buttons_Write_Response(const char **response_button){

    uint8_t button1_state;
    uint8_t button2_state;


    button1_state = GPIOPinRead(BUTTON1_PORT, BUTTON1_PIN);
    button2_state = GPIOPinRead(BUTTON2_PORT, BUTTON2_PIN);
    UARTprintf("Button1 %d\r\n", button1_state);
    UARTprintf("Button2: %d\r\n", button2_state);
    if (button1_state == 0 && button2_state == 0){

        responsedef = ConcatenateStrings(responses_ziffer[0],responses_index[0]);

        *response_button = ConcatenateStrings(responsedef,"\nSuche jetzt den server der auf /tone einen Ton ausgibt.");
    }else if(button1_state == 2 && button2_state == 0) {
        *response_button = ConcatenateStrings(responses_ziffer[5],responses_index[5]);

    }else if(button1_state == 0 && button2_state == 64) {
        *response_button = ConcatenateStrings(responses_ziffer[6],responses_index[6]);

    }else {
        *response_button = "Es wurde kein Button gedrückt!\n Drücke jeden Button einzeln und dann zusammen um Teile des Passworts zu erhalten. Falls du mich nicht findest, mein Display blinkt!";
    }


}
char* ConcatenateStrings(const char* str1, const char* str2) {
    char* result = malloc(strlen(str1) + strlen(str2) + 1); // +1 for null-terminator
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}
void DisplayBlink(){
//    int i;
//for (i=0;i<20;i++){
//    CFAF128128B0145T_clear( CFAF128128B0145T_color_white);
////    SysCtlDelay(SysCtlClockGet()*2);
//    CFAF128128B0145T_clear(CFAF128128B0145T_color_black);
////    SysCtlDelay(SysCtlClockGet()*2);
//}

}



