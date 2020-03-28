/*
 * File Description 
 *      Header file for the support function for drawing the fruits on the LED Matrix. 
 *  
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SUPPORT_FRUIT_H
#define	SUPPORT_FRUIT_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
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
    void writeColor(unsigned char r, unsigned char g, unsigned char b);
    
    /*
     * Description
     *      Ndelay simply repeats the assembly function delay_MS n times to achieve the 
     *      desired delay (Only works for delays that are a multiple of 1 ms).
     * Parameters 
     *      1. int n, number of milliseconds to delay
     * Return
     *      void 
     */
    void Ndelay(int n);
    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

