/*
 * button.h
 *
 *  Created on: 03.06.2024
 *      Author: felix
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Private/responses.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "CFAF128128B0145T/CFAF128128B0145T.h"

#define BUTTON1_PORT    GPIO_PORTH_BASE
#define BUTTON1_PIN     GPIO_PIN_1

#define BUTTON2_PORT    GPIO_PORTK_BASE
#define BUTTON2_PIN     GPIO_PIN_6

void Buttons_Init(void);
void Buttons_Write_Response(const char **response_button);
char* ConcatenateStrings(const char* str1, const char* str2);
void DisplayBlink();



#endif /* BUTTON_H_ */
