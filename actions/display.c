/*
 * display.c
 *
 *  Created on: 04.06.2024
 *      Author: felix
 */


#include "display.h"
#include "button.h"

void displaytext(const char **response_button){
    *response_button = "Schaue auf mein Display";
    char* concatenated_string = ConcatenateStrings(responses_ziffer[2],responses_index[2]);
    CFAF128128B0145T_text(0, 5, concatenated_string, CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(0, 30, "letzter Schritt ist", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(0, 45, "auf /snake anzufragen", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
    CFAF128128B0145T_text(0, 60, "sammel dabei 3 Aepfel", CFAF128128B0145T_color_white, CFAF128128B0145T_color_black, 1, 1);
}

