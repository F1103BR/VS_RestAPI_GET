#include <stdbool.h>
#include <stdint.h>
#include "mongoose.h"
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
#include "Private/responses.h"
#include <math.h>
#include <stdio.h>
#include "actions/rgb_led.h"
#include "actions/buzzer.h"
#include "actions/button.h"
#include "actions/snake_html.h"

#include "Private/gruppenfunktionen.h"


#include "CFAF128128B0145T/CFAF128128B0145T.h"



#define SYSTICKHZ 100
#define SYSTICKMS (1000 / SYSTICKHZ)
#define IP_LINK_DOWN (0xffffffffU)
#define IP_LINK_UP (0)



#define PWM_FREQUENCY 1000
uint32_t sys_clk;
volatile uint32_t ui32Load; // PWM period
volatile uint32_t ui32PWMClock;
uint8_t button1_state;
uint8_t button2_state;
struct mg_mgr g_mgr;
int index;
extern char* ConcatenateStrings(const char* str1, const char* str2);





// The main Mongoose event handler.
void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  static int led_value = 0;
  if (ev == MG_EV_POLL) return;
// Insert switch case here.
}




int gettimeofday(struct timeval *tv, void *tzvp) {
  tv->tv_sec = time(NULL);
  tv->tv_usec = 0;
  return 0;
}

void mg_lwip_mgr_schedule_poll(struct mg_mgr *mgr) {
}



// Invoked by lwiplib every HOST_TMR_INTERVAL ms (defined in lwipopts.h).
void lwIPHostTimerHandler(void) {
  static uint32_t old_ip = IP_LINK_DOWN;
  uint32_t ip = lwIPLocalIPAddrGet();
  if (ip != old_ip) {
    switch (ip) {
      case IP_LINK_DOWN: {
        UARTprintf("Link down.\r\n");
        LEDWrite(CLP_D2, 0);
        break;
      }
      case IP_LINK_UP: {
        UARTprintf("Link up.\r\n");
        LEDWrite(CLP_D2, 0);
        break;
      }
      default: {
        UARTprintf("IP: http://%s/\r\n", ipaddr_ntoa((const ip_addr_t *) &ip));
        LEDWrite(CLP_D2, CLP_D2);
        break;
      }
    }
    old_ip = ip;
  }

  mg_mgr_poll(&g_mgr, 0);
}

void SysTickIntHandler(void) {
  // Call the lwIP timer handler.
  lwIPTimer(SYSTICKMS);
}


 int main(void) {
    decode_responses_ziffer();
    volatile uint32_t ui32PWMClock;
  //
  // Make sure the main oscillator is enabled because this is required by
  // the PHY.  The system must have a 25MHz crystal attached to the OSC
  // pins. The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
  // frequency is 10MHz or higher.
  //
  SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

  // Run from the PLL at 120 MHz.
   sys_clk =
      MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                              SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                             120000000);
   CFAF128128B0145T_init(2, sys_clk, 20000000);

  // Configure the device pins.
  PinoutSet(true, false);

  // Configure UART.
  UARTStdioConfig(0, 115200, sys_clk);
  UARTprintf("VS Felix Brandstetter und Lars Weber: Password Guesser\n\n");

  // Configure board's LEDs: D2 is on when IP has been acquired,
  // D1 is toggled on every HTTP request.
  MAP_GPIOPinTypeGPIOOutput(CLP_D1_PORT, CLP_D1_PIN);
  MAP_GPIOPinTypeGPIOOutput(CLP_D2_PORT, CLP_D2_PIN);
  LEDWrite(CLP_D1, 0);
  LEDWrite(CLP_D2, 0);

  //
  // Configure the hardware MAC address for Ethernet Controller filtering of
  // incoming packets.  The MAC address will be stored in the non-volatile
  // USER0 and USER1 registers.
  //
  uint32_t u0, u1;
  MAP_FlashUserGet(&u0, &u1);
  uint8_t mac[6];
  mac[0] = ((u0 >> 0) & 0xff);
  mac[1] = ((u0 >> 8) & 0xff);
  mac[2] = ((u0 >> 16) & 0xff);
  mac[3] = ((u1 >> 0) & 0xff);
  mac[4] = ((u1 >> 8) & 0xff);
  mac[5] = ((u1 >> 16) & 0xff);

  // Initialize the lwIP library, using DHCP.
  lwIPInit(sys_clk, mac, 0, 0, 0, IPADDR_USE_DHCP);
  const char *cert_file = "C:\\Users\\felix\\cert.pem";
  const char *key_file = "C:\\Users\\felix\\key.pem";

  // Configure Mongoose and initialize it here.




  Buzzer_Init(sys_clk);
  Buttons_Init();


  // Configure SysTick for a periodic interrupt.
  MAP_SysTickPeriodSet(sys_clk / SYSTICKHZ);
  MAP_SysTickEnable();
  MAP_SysTickIntEnable();

  // Loop forever.  All the work is done in interrupt handlers.
  // Group 1 insert your blinking display in this while loop.
  while (true) {

  }
}







