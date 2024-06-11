/*
 * gruppenfunktionen.c
 *
 *  Created on: 04.06.2024
 *      Author: felix
 */

#include "gruppenfunktionen.h"

void funktion_gruppe1(const char **response_button){
    Buttons_Init();
    Buttons_Write_Response(response_button);
    DisplayBlink();
}
void funktion_gruppe2(const char **response_button,int index,uint32_t sys_clk){

    RGBLed_SetColorSineWave(response_button,index,sys_clk);

}
void funktion_gruppe3(const char **response_button){
    displaytext(response_button);

}
void funktion_gruppe4(const char **response_button){
    Buzzer_PlayTone(100,200000);
    Buzzer_Response(response_button);
}
void funktion_gruppe5(const char **response_button){
    *response_button = "Ergänzt jetzt die 9. Stelle des Passwortes mit eruem Wissen. Öffnet dann den Browser: http://141.37.157.11 und schaut ob das Passwort richtig ist.";
}
void funktion_gruppe6(const char **response_button){
    const char *responsedef;
    responsedef = ConcatenateStrings(responses_ziffer[7],responses_index[7]);
    *response_button =ConcatenateStrings(responsedef,"\nDas sind die ersten Teile vom Passwort.\nDas Passwort hat insgesamt 9 Stellen ihr müsst euch jetzt durch jeden Server, mithilfe von GET anfragen, die Teile vom Passwort, erfragen\nFindet jetzt das rot blinkende Licht wenn ihr einen Server auf /blink anfragt");
}



