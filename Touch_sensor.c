/*
 * File Description 
 *      Source file for the library that interfaces with the CAP1188 touch sensor.
 *      This includes setup, writing, and reading functions for this device. The
 *      functions in this file handle I2C communication between the CAP1188 and 
 *      PIC24.
 * 
 */

#include "Touch_sensor.h"
#include "xc.h"

/*
 * Description
 *      Sets up needed settings for the CAP1188 capacitive touch sensor and I2C communication. Changes 
 *      the LEDs on the CAP1188 chip to be mapped to detected touches and sets internal
 *      pull-up resistor in PIC24 pins in order to read from the CAP1188 LED pins. 
 *      This should be called once at the beginning of the the program. 
 * Parameters 
 *      void
 * Return
 *      void
 */
void setup_touch_sensor(void)
{
    // Set up of I2C
    I2C2CONbits.I2CEN = 0; // Make sure I2C2 is off, since I2C2 is used pins 6, 7 will be SDA, SCL
    I2C2BRG = 157; // will make the I2C clock rate 100kHz from table on pg 153 of PIC24 FDS
                   // clock rate seems to be fine for the CAP1188 from pg 19 of CAP1188
    I2C2CONbits.I2CEN = 1; // enable I2C2
    IFS3bits.MI2C2IF = 0; // I2C2 Reset interrupt flag 
    
    // Set up for the pins to be read from on the PIC24 to detect touches. The CAP1188 was not having consistent
    // reads so the touches were mapped to turning the LEDs in the chip on. When the LED is on it is 
    // pulled to ground and when it is off its pulled high by the internal pull up resistors 
    // in the PIC24 as set below. This makes it easy to digital read from these PIC24 pins to find out
    // if a pin on the CAP1188 was pressed.
    CNPU1bits.CN3PUE = 1; // PIC24 pin 3 and RA1 
    CNPU2bits.CN30PUE = 1; // Pin 9 and RA2
    CNPU2bits.CN29PUE = 1; // Pin 10 and RA3
    CNPU1bits.CN0PUE = 1; // Pin 12 and RA4
    
    // Register 0x72 controls mapping of CAP1188 LEDs to detected touches. By default these are not 
    // connected. Writing 11111111 to this register will map all touch pins to their corresponding 
    // LED. Needs to be transmitted several times due to it not working with just one time.  
    transmit_to_touch_sensor(0x72, 0b11111111);
    transmit_to_touch_sensor(0x72, 0b11111111);
    transmit_to_touch_sensor(0x72, 0b11111111);
    transmit_to_touch_sensor(0x72, 0b11111111);
}

/*
 * Description
 *      Will transmit a byte of data to a register in the CAP1188 through I2C.
 *      This function might need to be called several times in a row because data 
 *      does not seem to be received the first time it is transmitted due to erratic 
 *      device behavior.
 * Parameters 
 *      1. unsigned char, the address of the register in the CAP1188 that is being written to. 
 *      2. char, the data that is being transmitted.
 * Return
 *      void
 */
void transmit_to_touch_sensor(unsigned char address, char data)
{
    // I2C write sequence
    I2C2CONbits.SEN = 1; // Send start condition
    while (I2C2CONbits.SEN) {} // Wait for start to clear signaling it has been sent
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2TRN = 0b01010000; // Slave address of CAP1188 because ADDR_COMM pin is tied to VDD, 
                          // last bit is 0 to write 
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt  
    while (I2C2STATbits.TBF) {} // Wait for transmission to end 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag  
    
    I2C2TRN = address; // Register address on the CAP1188 to change 
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt 
    while (I2C2STATbits.TBF) {} // Wait for transmission to end
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2TRN = data; // Data to be written to the address on the CAP1188 
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt 
    while (I2C2STATbits.TBF) {} // Wait for transmission to end
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2CONbits.PEN = 1; // Send stop 
    while (I2C2CONbits.PEN) {} // Wait for stop bit to clear signaling transmission 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
}

/*
 * Description
 *      Will read a byte of data from a register in the CAP1188 through I2C. This 
 *      function needs to be called twice if a write just occurred because the first
 *      read will return invalid data. Due to the lack of reliability in reading data 
 *      taken from detectable pin touches, the LED pins changing voltage on the 
 *      CAP1188 were used to take touch data. 
 * Parameters 
 *      1. unsigned char, the address of the memory location to get data from. 
 * Return
 *      unsigned char, the data received from the memory location.
 */
unsigned char read_from_touch_sensor(unsigned char address)
{
    
    unsigned char temp = 0; // Temp variable to read to value of the receive register from 
    
    // I2C read sequence 
    I2C2CONbits.SEN = 1; // Send start condition
    while (I2C2CONbits.SEN) {} // Wait for start to clear signaling it has been sent
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2TRN = 0b01010000; // Slave address of CAP1188 because ADDR_COMM pin is tied to VDD, 
                          // last bit is 0 to write because is sent first then read 
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag

    I2C2TRN = address; // Register address on the CAP1188 to read from
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag

    I2C2CONbits.RSEN = 1; // Repeat start condition for read sequence 
    while (I2C2CONbits.RSEN) {} // Wait for repeat start to clear signaling it has been sent 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2TRN = 0b01010001; // Slave address of CAP1188 because ADDR_COMM pin is tied to VDD, 
                          // last bit is 1 to read
    while (IFS3bits.MI2C2IF == 0) {} // Wait for interrupt 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2CONbits.RCEN = 1; // Enable data reception 
    while (I2C2CONbits.RCEN) {} // Wait for data reception to clear signaling data received
    while (!I2C2STATbits.RBF) {} // Wait till the data received buffer is full
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2CONbits.ACKDT = 1; // Setting to transmit a NACK to CAP1188 to signal PIC24 received data
    I2C2CONbits.ACKEN = 1; // Transmit the NACK
    while (I2C2CONbits.ACKEN) {} // Wait for NACK to transmit 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    I2C2CONbits.PEN = 1; // Send stop 
    while (I2C2CONbits.PEN) {} // Wait for stop bit to clear signaling transmission 
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    temp =  I2C2RCV; // Read data from CAP1188 out of the receive buffer
    return temp; // Return the data from the CAP1188 
}
