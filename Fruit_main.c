/*
 * File:   zwett007_lab2b_main_v001.c
 * Author: jackzwettler
 *
 * Created on September 25, 2019, 9:53 PM
 * 
 * File Description 
 *      Main function to run the touch sensor and LED matrix out of.
 */


#include "xc.h"
#include "Assembly.h"
#include "Fruit_animation.h"
#include "Touch_sensor.h"
#define FCY 16000000UL
#include <libpic30.h>

#include "xc.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled,                                       
                                        // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

/*
 * Description
 *      Basic set up for PIC24 need to run the program.
 * Parameters 
 *      void 
 * Return
 *      void
 */
void setup(void) 
{
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9FFF;
    TRISA = 0b1111111111111110; // RA0 is an output
    LATA = 0x0000;
    TRISB = 0x0000; // set all output, should be overwritten for SPI 
}

/*
 * Description
 *      Main function to run the infinite loop out of. 
 * Parameters 
 *      void 
 * Return
 *      void
 */
int main(void)
{
    setup();
    setup_touch_sensor();
    
    // Set LED high 
    LATBbits.LATB5 = 1;

    while (1)
    {
       __delay_ms(500);
       if (PORTAbits.RA1 == 0) // pin 3
       {
           LATBbits.LATB5 = !LATBbits.LATB5;
           banana_slide();
       }
       else if (PORTAbits.RA2 == 0) // pin 9
       {
           LATBbits.LATB5 = !LATBbits.LATB5;
           munching_apple();
       }
       else if (PORTAbits.RA3 == 0) // pin 10 
       {
           LATBbits.LATB5 = !LATBbits.LATB5;
           annoying_orange();
       }
       else if (PORTAbits.RA4 == 0) // pin 12
       {
           LATBbits.LATB5 = !LATBbits.LATB5;
           grapes_of_wrath();
       }
    }
    
    return 0;
}

   

