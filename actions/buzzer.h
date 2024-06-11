#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "actions/button.h"

void Buzzer_Init(uint32_t sys_clk);
void Buzzer_PlayTone(uint32_t frequency, uint32_t duration);
void Buzzer_Stop(void);
void buzzer_playTone(int note, int duration);
void playAlleMeineEntchen();
void playWindowsErrorSound();
void Buzzer_Response(const char **response_button);

#endif // BUZZER_H
