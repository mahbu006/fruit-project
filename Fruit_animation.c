/*
 * File:   Fruit_animation.c
 * Author: zwett007
 *
 * Created on December 5, 2019, 3:28 PM
 * 
 * File Description
 *      Header file for the functions that draw the fruits on the LED matrix. 
 * Background 
 *      All of the functions in this file are responsible for creating animations on the LED matrix. 
 *      The basic mechanism within each file is the same: 64 consecutive 3-byte packets must be sent 
 *      to the matrix to make each LED light up sequentially. This is done using 64 consecutive function 
 *      calls of writeColor. The LEDs are lit up by row, starting at the top row. Within each row, the 
 *      left-most LED is accessed first. As an example, here is a visual representation of the matrix 
 *      corresponding to one frame of the banana animation:
 * 
 *      0 0 0 0 0 0 1 0     2
 *      0 0 0 0 0 1 1 1     7
 *      0 0 0 0 0 1 1 1     7
 *      0 0 0 0 1 1 1 1     15
 *      0 0 0 1 1 1 1 0     30
 *      0 1 1 1 1 1 1 0     126
 *      1 1 1 1 1 1 0 0     252
 *      0 1 1 1 0 0 0 0     112
 * 
 *      unsigned int banana[24] = {0,0,0,0,0,0,0,0, 2,7,7,15,30,126,252,112,0,0,0,0,0,0,0,0} 
 * 
 *      If this frame is to be displayed on the LED matrix, a for loop of 64 iterations is needed to 
 *      process each individual LED. Within this for loop, there are 8 separate modes for each row 
 *      (8 if-else if statements). Using bit-masking, each LED location is checked to determine if it 
 *      should be lit or unlit (1 or 0). writeColor can be modified to produce the desired color. 
 */


#include "xc.h"
#include "Assembly.h"
#include "Support_fruit.h"
#define PERIOD 2000
volatile int z;
volatile int f;
volatile int y;

/*
 * Description
 *      The purpose of this function is to animate a banana sliding first across the matrix 
 *      from left to right and then from top to bottom. Both of these animations use the 
 *      aforementioned banana array using different shift operations. For the horizontal sliding, 
 *      only elements banana[8-15] (those highlighted in red) are considered. The animation itself 
 *      consists of three distinct modes contained within a for loop. The first 8 steps involve 
 *      left-shifting each row entry by 8-n, where n=0 for the first step, n=1 for the second, and 
 *      so on (0 <= n <= 7). This has the effect of moving the banana to the right. The second mode 
 *      is when the banana is centered in the matrix (shown in the figure above). At this step, 
 *      when n=8, the banana array is left unchanged. The final mode involves right-shifting each 
 *      row entry by n-8, producing the effect of the banana moving right (9 <= n <= 16). 
 * 
 *      For the banana sliding down, the extra ?0? entries in the original banana array become relevant. 
 *      This animation involves using an 8-element placeholder array to store the rows required for each 
 *      frame. Specifically, elements 23-n to 16-n from the initial banana array are used for each frame 
 *      (0 <= n <= 16). This animation produces the effect of the banana moving down. Both of these 
 *      animations use the 1D array method, which exploits the constancy of the banana image.
 * Parameters 
 *      void 
 * Return
 *      void 
 */
void banana_slide(void) {
    /* -------------------------- Banana Animation --------------------------- */
        unsigned int banana[24] = {0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 7, 15, 30, 126, 252, 112, 0, 0, 0, 0, 0, 0, 0, 0};

        for (y = 0; y < 17; y++) { // Banana sliding right

            unsigned int hold[8];
            int j;

            if (y < 8) {
                for (j = 0; j < 8; j++) {
                    hold[j] = banana[j + 8] << (8 - y);
                }
            } else if (y == 8) {
                for (j = 0; j < 8; j++) {
                    hold[j] = banana[j + 8];
                }
            } else {
                for (j = 0; j < 8; j++) {
                    hold[j] = banana[j + 8] >> (y - 8);
                }
            }

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
       
        for (y = 16; y >= 0; y--) { //Banana going down

            unsigned int hold[8];
            int j;

            for (j = 0; j < 8; j++) {
                hold[j] = banana[j + y];
            }

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(32, 32, 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
}

/*
 * Description
 *      The apple animation contains two separate methods of operation: 1D array and 2D array. In the 
 *      1D array method, the apple has the same animations as the banana: sliding left to right first 
 *      and then top to bottom. The only extra point to consider in this mode of operation is the fact 
 *      that the apple has three possible states for any one of its LEDs: green, red, or off. This 
 *      introduces a slight increase in difficulty in the form of a color array that stores the color 
 *      information for any given row. This is only relevant in the downward sliding animation, when the 
 *      rows corresponding to red and green change in every frame.
 * 
 *      The 2D array method is needed for the third animation of the apple, which shows the apple being 
 *      eaten. Because the shape of the apple changes in each frame, symmetry cannot be exploited. This 
 *      requires a two dimensional array: one dimension containing the row information for the given frame, 
 *      and the other dimension specifying the frame itself. The mechanics for initializing this array are 
 *      quite simple: each frame is specified individually using nested for loops. The outer for loop controls 
 *      which frame is being specified, and the inner for loop updates each row for that frame. In this case, 
 *      the result is an animation of an apple being eaten.
 * Parameters 
 *      void
 * Return
 *      void 
 */
void munching_apple(void) {
    /* ---------------------- Apple Animation --------------------------------- */
        unsigned int apple[24] = {0, 0, 0, 0, 0, 0, 0, 0, 14, 12, 24, 36, 126, 126, 126, 60, 0, 0, 0, 0, 0, 0, 0, 0};
        for (y = 0; y < 17; y++) { // Apple going right
            unsigned int hold[8];
            int j;
            if (y < 8) {
                for (j = 0; j < 8; j++) {
                    hold[j] = apple[j + 8] << (8 - y);
                }
            } else if (y == 8) {
                for (j = 0; j < 8; j++) {
                    hold[j] = apple[j + 8];
                }
            } else {
                for (j = 0; j < 8; j++) {
                    hold[j] = apple[j + 8]>>(y - 8);
                }
            }

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
       
        unsigned int color[8];
       
        for (y = 16; y >= 0; y--) { // Apple going down
            unsigned int hold[8];
            int j;
            for (j = 0; j < 8; j++) {
                hold[j] = apple[j + y];
                if (y > 10) {
                    if ((y + j) < 17)
                        color[j] = 1;
                    else
                        color[j] = 0;
                } else {
                    if ((y + j) < 8)
                        color[j] = 0;
                    else if (((y + j) >= 8)&&((y + j) < 11))
                        color[j] = 2;
                    else
                        color[j] = 1;
                }
            }

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(16 * (2 & color[0]), 32 * (1 & color[0]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(16 * (2 & color[1]), 32 * (1 & color[1]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(16 * (2 & color[2]), 32 * (1 & color[2]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(16 * (2 & color[3]), 32 * (1 & color[3]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(16 * (2 & color[4]), 32 * (1 & color[4]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(16 * (2 & color[5]), 32 * (1 & color[5]), 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(16 * (2 & color[6]), 32 * (1 & color[6]), 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(16 * (2 & color[7]), 32 * (1 & color[7]), 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
        /*Apple being eaten*/
        unsigned int newapple[8][8];
        for (z=0;z<8;z++) {
            for (f=0;f<8;f++) {
                if (f == 0) {
                    newapple[f][z]=14;
                }
                else if (f == 1)
                    newapple[f][z]=12;
                else if (f == 2)
                    newapple[f][z]=24;
                else if (f == 3)
                    newapple[f][z]=36;
                else if (f == 4) {
                    if (z <= 1) 
                        newapple[f][z] = 126;
                    else if (z == 2)
                        newapple[f][z] = 124;
                    else if ((z == 3) || (z == 4))
                        newapple[f][z] = 120;
                    else if (z == 5)
                        newapple[f][z] = 56;
                    else if ((z == 6) || (z == 7))
                        newapple[f][z] = 24;                      
                }
                else if (f == 5) {
                    if (z == 0) 
                        newapple[f][z] = 126;
                    else if (z == 1)
                        newapple[f][z] = 124;
                    else if (z == 2)
                        newapple[f][z] = 120;
                    else if (z == 3)
                        newapple[f][z] = 112;
                    else if (z == 4)
                        newapple[f][z] = 48;
                    else if (z == 5)
                        newapple[f][z] = 16;
                    else if (z == 6)
                        newapple[f][z] = 16;
                    else if (z == 7)
                        newapple[f][z] = 16;
                }
                else if (f == 6) {
                    if (z == 0) 
                        newapple[f][z] = 126;
                    else if (z == 1)
                        newapple[f][z] = 126;
                    else if (z == 2)
                        newapple[f][z] = 124;
                    else if (z == 3)
                        newapple[f][z] = 120;
                    else if (z == 4)
                        newapple[f][z] = 120;
                    else if (z == 5)
                        newapple[f][z] = 56;
                    else if (z == 6)
                        newapple[f][z] = 24;
                    else if (z == 7)
                        newapple[f][z] = 24;
                }
                else if (f == 7) {
                    if (z == 0) 
                        newapple[f][z] = 60;
                    else if (z == 1)
                        newapple[f][z] = 60;
                    else if (z == 2)
                        newapple[f][z] = 60;
                    else if (z == 3)
                        newapple[f][z] = 60;
                    else if (z == 4)
                        newapple[f][z] = 60;
                    else if (z == 5)
                        newapple[f][z] = 60;
                    else if (z == 6)
                        newapple[f][z] = 60;
                    else if (z == 7)
                        newapple[f][z] = 36;
                }
            }
        }
        for (y = 0; y < 8; y++) { // Apple biting
            unsigned int hold[8];
            int j;
            for (j = 0; j < 8; j++) {
                    hold[j] = newapple[j][y];
            }
            

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(0, 32, 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
}

/*
 * Description
 *      The orange animation implements the 2D array data structure with the first array holding the design of the fruit, 
 *      and the second array holding essentially each animation frame. We went on a crafting website and mapped out 
 *      8x8 grids to draw each orange frame that we wanted (in this case we used 10 animation slides) which would 
 *      correspond to the matrix. We wanted to make an orange grow gradually from the stop, so we carefully added LED 
 *      pixels from the top down in orange to make it seem as if it was growing naturally. Each row would basically be a 
 *      binary number; for example, in the first row, if the 4th pixel was supposed to be lit up we would place 8 
 *      (0b0001000) in the array. Through nested for loops and if statements, we were able to successfully map out our 
 *      animations. For the color aspect, we created a placeholder array that is really just a shift register containing 
 *      data from the original fruit array. We bit masked the placeholder array with 0x80 to check the most significant bit 
 *      and put it in a temporary variable. If it was a 1, we would implement our writeColor(); function with the respective 
 *      color of orange in this case, if not we would leave the LED matrix blank. We additionally left shifted the hold 
 *      register one spot for each iteration so it was the second most significant bit that would be checked for the next iteration.
 * Parameters 
 *      void 
 * Return
 *      void
 */
void annoying_orange(void) {
     /* ---------------------- Orange Animation --------------------------------- */
        unsigned int orange[8][10];
        for (z=0;z<8;z++) {
            for (f=0;f<10;f++) {
                if (z == 0) {
                      if (f != 9)
                          orange[z][f] = 240;
                      else
                          orange[z][f] = 48;
                }
                else if (z == 1)
                    orange[z][f] = 24;
                else if (z == 2) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 8;
                    else if (f == 2)
                       orange[z][f] = 24;
                    else if (f == 3)
                       orange[z][f] = 28;
                    else if (f == 4)
                       orange[z][f] = 28;
                    else if (f == 5)
                       orange[z][f] = 28;
                    else if (f == 6)
                       orange[z][f] = 28;
                    else if (f == 7)
                       orange[z][f] = 60;
                    else if (f == 8)
                       orange[z][f] = 60;
                    else if (f == 9)
                       orange[z][f] = 60;
                }
                else if (z == 3) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 24;
                    else if (f == 2)
                       orange[z][f] = 24;
                    else if (f == 3)
                       orange[z][f] = 28;
                    else if (f == 4)
                       orange[z][f] = 28;
                    else if (f == 5)
                       orange[z][f] = 62;
                    else if (f == 6)
                       orange[z][f] = 62;
                    else if (f == 7)
                       orange[z][f] = 126;
                    else if (f == 8)
                       orange[z][f] = 126;
                    else if (f == 9)
                       orange[z][f] = 126;
                }
                else if (z == 4) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 0;
                    else if (f == 2)
                       orange[z][f] = 0;
                    else if (f == 3)
                       orange[z][f] = 8;
                    else if (f == 4)
                       orange[z][f] = 28;
                    else if (f == 5)
                       orange[z][f] = 62;
                    else if (f == 6)
                       orange[z][f] = 62;
                    else if (f == 7)
                       orange[z][f] = 126;
                    else if (f == 8)
                       orange[z][f] = 126;
                    else if (f == 9)
                       orange[z][f] = 126;
                }
                else if (z == 5) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 0;
                    else if (f == 2)
                       orange[z][f] = 0;
                    else if (f == 3)
                       orange[z][f] = 0;
                    else if (f == 4)
                       orange[z][f] = 0;
                    else if (f == 5)
                       orange[z][f] = 28;
                    else if (f == 6)
                       orange[z][f] = 62;
                    else if (f == 7)
                       orange[z][f] = 126;
                    else if (f == 8)
                       orange[z][f] = 126;
                    else if (f == 9)
                       orange[z][f] = 126;
                }
                else if (z == 6) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 0;
                    else if (f == 2)
                       orange[z][f] = 0;
                    else if (f == 3)
                       orange[z][f] = 0;
                    else if (f == 4)
                       orange[z][f] = 0;
                    else if (f == 5)
                       orange[z][f] = 0;
                    else if (f == 6)
                       orange[z][f] = 28;
                    else if (f == 7)
                       orange[z][f] = 60;
                    else if (f == 8)
                       orange[z][f] = 126;
                    else if (f == 9)
                       orange[z][f] = 126;
                }
                else if (z == 7) {
                    if (f == 0)
                       orange[z][f] = 0;
                    else if (f == 1)
                       orange[z][f] = 0;
                    else if (f == 2)
                       orange[z][f] = 0;
                    else if (f == 3)
                       orange[z][f] = 0;
                    else if (f == 4)
                       orange[z][f] = 0;
                    else if (f == 5)
                       orange[z][f] = 0;
                    else if (f == 6)
                       orange[z][f] = 0;
                    else if (f == 7)
                       orange[z][f] = 0;
                    else if (f == 8)
                       orange[z][f] = 60;
                    else if (f == 9)
                       orange[z][f] = 60;
                }
            }
        }
        for (y = 0; y < 10; y++) { // Orange growing
            unsigned int hold[8];
            int j;
            for (j = 0; j < 8; j++) {
                    hold[j] = orange[j][y];
            }
            

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(8, 32, 0);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
}

/*
 * Description
 *      The grape animation also implements the 2D array data structure with the first array holding the design 
 *      of the fruit, and the second array holding essentially each animation frame. We went on a crafting website 
 *      and mapped out 8x8 grids to draw each grape frame that we wanted (in this case we used 12 animation slides) 
 *      which would correspond to the matrix. We wanted to make grapes being picked off one by one from the bottom 
 *      up, so we successfully took away LED pixels in purple to make it seem as if someone was picking off grapes 
 *      and eating them naturally. Each row would basically be a binary number; for example, in the first row, if 
 *      the 4th pixel was supposed to be lit up we would place 8 (0b0001000) in the array. Through nested for loops 
 *      and if statements, we were able to successfully map out our animations. For the color aspect, we created a 
 *      placeholder array that is really just a shift register containing data from the original fruit array. We bit 
 *      masked the placeholder array with 0x80 to check the most significant bit and put it in a temporary variable. 
 *      If it was a 1, we would implement our writeColor(); function with the respective color of purple in this case, 
 *      if not we would leave the LED matrix blank. We additionally left shifted the hold register one spot for each 
 *      iteration so it was the second most significant bit that would be checked for the next iteration.
 * Parameters 
 *      void 
 * Return
 *      void
 */
void grapes_of_wrath(void) {
    /* ---------------------- Grape Animation --------------------------------- */
        unsigned int grape[8][12];
        for (z=0;z<8;z++) {
            for (f=0;f<12;f++) {
                if (z == 0)
                    grape[z][f] = 116;
                else if (z == 1)
                    grape[z][f] = 28;
                else if (z == 2) {
                    if (f < 10)
                        grape[z][f] = 56;
                    else if (f == 10)
                        grape[z][f] = 24;
                    else
                        grape[z][f] = 0;
                }
                else if (z == 3) {
                    if (f == 0)
                       grape[z][f] = 124;
                    else if (f == 1)
                       grape[z][f] = 124;
                    else if (f == 2)
                       grape[z][f] = 124;
                    else if (f == 3)
                       grape[z][f] = 124;
                    else if (f == 4)
                       grape[z][f] = 124;
                    else if (f == 5)
                       grape[z][f] = 124;
                    else if (f == 6)
                       grape[z][f] = 124;
                    else if (f == 7)
                       grape[z][f] = 60;
                    else if (f == 8)
                       grape[z][f] = 48;
                    else if (f == 9)
                       grape[z][f] = 16;
                    else if (f == 10)
                       grape[z][f] = 0;
                    else if (f == 11)
                       grape[z][f] = 0;
                }
                else if (z == 4) {
                    if (f == 0)
                       grape[z][f] = 124;
                    else if (f == 1)
                       grape[z][f] = 124;
                    else if (f == 2)
                       grape[z][f] = 124;
                    else if (f == 3)
                       grape[z][f] = 124;
                    else if (f == 4)
                       grape[z][f] = 124;
                    else if (f == 5)
                       grape[z][f] = 60;
                    else if (f == 6)
                       grape[z][f] = 48;
                    else if (f == 7)
                       grape[z][f] = 16;
                    else if (f == 8)
                       grape[z][f] = 16;
                    else if (f == 9)
                       grape[z][f] = 0;
                    else if (f == 10)
                       grape[z][f] = 0;
                    else if (f == 11)
                       grape[z][f] = 0;
                }
                else if (z == 5) {
                    if (f == 0)
                       grape[z][f] = 124;
                    else if (f == 1)
                       grape[z][f] = 124;
                    else if (f == 2)
                       grape[z][f] = 60;
                    else if (f == 3)
                       grape[z][f] = 48;
                    else if (f == 4)
                       grape[z][f] = 16;
                    else if (f == 5)
                       grape[z][f] = 0;
                    else if (f == 6)
                       grape[z][f] = 0;
                    else if (f == 7)
                       grape[z][f] = 0;
                    else if (f == 8)
                       grape[z][f] = 0;
                    else if (f == 9)
                       grape[z][f] = 0;
                    else if (f == 10)
                       grape[z][f] = 0;
                    else if (f == 11)
                       grape[z][f] = 0;
                }
                else if (z == 6) {
                    if (f == 0)
                       grape[z][f] = 56;
                    else if (f == 1)
                       grape[z][f] = 48;
                    else if (f == 2)
                       grape[z][f] = 16;
                    else if (f == 3)
                       grape[z][f] = 16;
                    else if (f == 4)
                       grape[z][f] = 0;
                    else if (f == 5)
                       grape[z][f] = 0;
                    else if (f == 6)
                       grape[z][f] = 0;
                    else if (f == 7)
                       grape[z][f] = 0;
                    else if (f == 8)
                       grape[z][f] = 0;
                    else if (f == 9)
                       grape[z][f] = 0;
                    else if (f == 10)
                       grape[z][f] = 0;
                    else if (f == 11)
                       grape[z][f] = 0;
                }
                else if (z == 7) {
                    if (f == 0)
                        grape[z][f] = 16;
                    else
                        grape[z][f] = 0;
                }
            }
        }
        for (y = 0; y < 12; y++) { // Grape eating
            unsigned int hold[8];
            int j;
            for (j = 0; j < 8; j++) {
                    hold[j] = grape[j][y];
            }
            

            Ndelay(PERIOD);
            int i;
            int r;
           
            for (i = 0; i < 64; i++) {
                if (i < 8) {
                    r = hold[0] & 0x80;
                    hold[0] = hold[0] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 16) {
                    r = hold[1] & 0x80;
                    hold[1] = hold[1] << 1;
                    if (r)
                        writeColor(32, 0, 0);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 24) {
                    r = hold[2] & 0x80;
                    hold[2] = hold[2] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 32) {
                    r = hold[3] & 0x80;
                    hold[3] = hold[3] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 40) {
                    r = hold[4] & 0x80;
                    hold[4] = hold[4] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 48) {
                    r = hold[5] & 0x80;
                    hold[5] = hold[5] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                } else if (i < 56) {
                    r = hold[6] & 0x80;
                    hold[6] = hold[6] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                } else {
                    r = hold[7] & 0x80;
                    hold[7] = hold[7] << 1;
                    if (r)
                        writeColor(0, 32, 32);
                    else
                        writeColor(0, 0, 0);
                }
            }
        }
}

