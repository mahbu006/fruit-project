/*
 * File Description
 *	Header file for support functions for writing a bitstream to the iLED with accuracy.   
 */
    
.include "xc.inc"
.text                       ;BP (put the following data in ROM(program memory))
; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading
; underscore (_) and be included in a comment delimited list below.
.global _example_public_function, _second_public_function, _delay_hund_uS, _delay_MS, _write_0, _write_1

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
    _delay_hund_uS:
    
    repeat #1593
    nop
    return
    
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
    _delay_MS:
    repeat #15993
    nop
    return
    
    /*
     * Description
     *      Created in assembly code, containing instructions for a high pulse of 6 instruction 
     *      cycles followed by a low value for 14 instruction cycles which correspond to 0.375탎 
     *      and 0.875탎 respectively. From the datasheet, this period of 20 clock cycles is 
     *      interpreted as a ?0? bit by the LED matrix.
     * Parameters 
     *      void
     * Return
     *      void
     */
    _write_0: 
    inc LATA;
    repeat #3
    nop
    clr LATA;
    repeat #6
    nop
    return
    
    /*
     * Description
     *      Created in assembly code, containing instructions for a high pulse of 12 instruction 
     *      cycles followed by a low value for 8 instruction cycles which correspond to 0.750탎 
     *      and 0.500탎 respectively. From the datasheet, this period of 20 clock cycles is 
     *      interpreted as a ?1? bit by the LED matrix.
     * Parameters 
     *      void
     * Return
     *      void
     */
    _write_1:
    inc LATA;
    repeat #9
    nop
    clr LATA;
    nop
    nop
    return


