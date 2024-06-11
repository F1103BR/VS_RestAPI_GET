#ifndef GRUPPENFUNKTIONEN_H
#define GRUPPENFUNKTIONEN_H

#include "actions/button.h"
#include "actions/buzzer.h"
#include "actions/rgb_led.h"
#include "actions/display.h"
#include "Private/responses.h"
#include "utils/uartstdio.h"
//#include "actions/snake_html.h"

void funktion_gruppe1(const char **response_button); // buttons init
void funktion_gruppe2(const char **response_button,int index,uint32_t sys_clk); // rgb led
void funktion_gruppe3(const char **response_button); // Display
void funktion_gruppe4(const char **response_button);  // buzzer
void funktion_gruppe5(const char **response_button); // Finish
void funktion_gruppe6(const char **response_button); //init funktion
int funktion_gruppe7(char **response, const char *index_info, const char *ziffer_info); // snake
#endif //GRUPPENFUNKTIONEN_H
