/* 
 * File:   Touch_Sensor.h
 * Author: nessn
 *
 * Created on December 9, 2019, 12:35 PM
 * 
 * File Description 
 *      Header file for library that interfaces with the CAP1188 Touch Sensor.
 */

#ifndef TOUCH_SENSOR_H
#define	TOUCH_SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
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
void setup_touch_sensor(void);

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
void transmit_to_touch_sensor(unsigned char address, char data);

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
unsigned char read_from_touch_sensor(unsigned char address);

#ifdef	__cplusplus
}
#endif

#endif	/* TOUCH_SENSOR_H */

