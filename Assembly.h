/* 
 * File:   Assembly.h
 *
 * Created on September 25, 2019, 10:18 PM
 * 
 * File Description
 *      Header file for support functions for writing a bitstream to the iLED with accuracy.
 */

#ifndef ASSEMBLY_H
#define	ASSEMBLY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /*
    * Description
    *       Created in assembly code through repeating the ?nop? operation 1593 times which 
    *       corresponds to roughly a hundred microseconds using the 16 MHz clock. This assembly 
    *       function was implemented in the Ndelay function to essentially create a consistent 
    *       delay that we would use throughout our project.
    * Parameters 
    *       void 
    * Return
    *       void 
    */
    void delay_hund_uS(void);
    
    /*
     * Description
     *      Created in assembly code through repeating the ?nop? operation 15993 times which 
     *      corresponds to about one millisecond using the 16 MHz clock. This assembly 
     *      function was not implemented throughout our project as we already had an adequate 
     *      delay in the prior function.
     * Parameters 
     *      void
     * Return
     *      void 
     */
    void delay_MS(void);
    
    /*
     * Description
     *      Created in assembly code, containing instructions for a high pulse of 6 instruction 
     *      cycles followed by a low value for 14 instruction cycles which correspond to 0.375µs 
     *      and 0.875µs respectively. From the datasheet, this period of 20 clock cycles is 
     *      interpreted as a ?0? bit by the LED matrix.
     * Parameters 
     *      void
     * Return
     *      void
     */
    void write_0(void);
    
    /*
     * Description
     *      Created in assembly code, containing instructions for a high pulse of 12 instruction 
     *      cycles followed by a low value for 8 instruction cycles which correspond to 0.750µs 
     *      and 0.500µs respectively. From the datasheet, this period of 20 clock cycles is 
     *      interpreted as a ?1? bit by the LED matrix.
     * Parameters 
     *      void
     * Return
     *      void
     */
    void write_1(void);
#ifdef	__cplusplus
}
#endif

#endif	/* ZWETT007_LAB2B_ASMLIB_V001_H */

