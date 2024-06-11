#include "buzzer.h"

#define PWM_FREQUENCY 1000

void Buzzer_Init(uint32_t sys_clk) {
    // Enable the peripherals used by the buzzer.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Wait for the peripherals to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)) {}

    // Configure the GPIO pin for PWM function.
    GPIOPinConfigure(GPIO_PG1_M0PWM5); // Assuming the Buzzer is connected to PG1 (PWM0)

    GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);

    // Configure the PWM generator for count-down mode.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);

    // Set the PWM period.
    uint32_t ui32Load = (sys_clk / PWM_FREQUENCY) - 1;
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ui32Load);

    // Enable the PWM output.
    PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);

    // Enable the PWM generator.
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}

void Buzzer_PlayTone(uint32_t frequency, uint32_t duration) {
    uint32_t sys_clk = SysCtlClockGet();
    uint32_t ui32Load = (sys_clk / frequency) - 1;

    // Set the PWM period for the specified frequency.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ui32Load);

    // Set the PWM duty cycle to 50%.
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, ui32Load / 2);

    // Enable the PWM generator.
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);

    // Wait for the specified duration.
    SysCtlDelay(sys_clk / 3 / 1000 * duration); // SysCtlDelay is approximately 1ms delay

    // Stop the buzzer.
    Buzzer_Stop();
    char* concatenated_string = ConcatenateStrings(responses_ziffer[3], responses_index[3]);
    UARTprintf("%s\n", concatenated_string);
}

void Buzzer_Stop(void) {
    // Disable the PWM generator.
    PWMGenDisable(PWM0_BASE, PWM_GEN_2);
}
void playAlleMeineEntchen() {
    int melody[] = {0, 1, 2, 3, 4, 3, 4, 5, 5, 5, 5, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    int noteDurations[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 1000, 500};
int i;
    for (i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        buzzer_playTone(melody[i], noteDurations[i]);
        SysCtlDelay(SysCtlClockGet()*2); // Delay zwischen den Noten
    }

}
void buzzer_playTone(int note, int duration) {
    switch(note) {
        case 0: // C
            Buzzer_PlayTone(262, duration);
            break;
        case 1: // D
            Buzzer_PlayTone(294, duration);
            break;
        case 2: // E
            Buzzer_PlayTone(330, duration);
            break;
        case 3: // F
            Buzzer_PlayTone(349, duration);
            break;
        case 4: // G
            Buzzer_PlayTone(392, duration);
            break;
        case 5: // A
            Buzzer_PlayTone(440, duration);
            break;
        case 6: // H
            Buzzer_PlayTone(494, duration);
            break;
        case 7: // C
            Buzzer_PlayTone(523, duration);
            break;
        default: // Pause
            Buzzer_Stop();
            break;
    }
}
void playWindowsErrorSound() {
    int melody[] = {2, 0, 5}; // E, C, A
    int noteDurations[] = {1500, 1500, 3000}; // Durations in milliseconds
    int i;
    for (i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        buzzer_playTone(melody[i], noteDurations[i]);
        SysCtlDelay(SysCtlClockGet() / 3 / 1000 * 50); // Short delay between notes
    }
}
void Buzzer_Response(const char **response_button){
    *response_button = "Frage mich auf /getmypart an";
}
