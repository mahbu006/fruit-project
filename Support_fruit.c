/*
 * File:   Support_fruit.c
 * Author: zwett007
 *
 * Created on December 5, 2019, 3:34 PM
 * 
 * File Description 
 *      Source file for the support function for drawing the fruits on the LED Matrix. 
 */


#include "xc.h"
#include "Assembly.h"

/*
 * Description
 *      From the device datasheet, each individual LED within the matrix is updated by a 3 byte 
 *      instruction with the first byte corresponding to green intensity, the second to red intensity, 
 *      and the third to blue intensity. 255 corresponds to the highest intensity and 0 to the lowest. 
 *      writeColor takes in three integer inputs corresponding to the desired intensity of each color 
 *      (?g? corresponds to green, ?r? to red, and ?b? to blue as is convention in hexadecimal color 
 *      codes) and uses bit-masking to send the proper values to the LED by means of write_0 and write_1.
 * Parameters 
 *      1. unsigned char r, the intensity of red 
 *      2. unsigned char g, the intensity of green 
 *      3. unsigned char b, the intensity of blue 
 * Return
 *      void
 */
void writeColor(unsigned int r, unsigned int g, unsigned int b) {

    int on, i, j, k;

    for (i = 0; i < 8; i++) { // Red loop
        on = r & 0x80;
        if (on)
            write_1();
        else
            write_0();
        r = r << 1;
    }
    for (j = 0; j < 8; j++) { // Green loop
        on = g & 0x80;
        if (on)
            write_1();
        else
            write_0();
        g = g << 1;
    }
    for (k = 0; k < 8; k++) { // Blue loop
        on = b & 0x80;
        if (on)
            write_1();
        else
            write_0();
        b = b << 1;
    }
}

/*
 * Description
 *      Ndelay simply repeats the assembly function delay_MS n times to achieve the 
 *      desired delay (Only works for delays that are a multiple of 1 ms).
 * Parameters 
 *      1. int n, number of milliseconds to delay
 * Return
 *      void 
 */
void Ndelay(int n) { // Delays for 100 microseconds n times
    int l;
    for (l = 0; l < n; l++) {
        delay_hund_uS();
    }
}
