
/*
 * File Description
 *      Header file for the functions that draw the fruits on the LED matrix. 
 * 
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
 * 
 */

#ifndef FRUIT_ANIMATION_H
#define	FRUIT_ANIMATION_H

#include <xc.h> // include processor files - each processor file is guarded.  



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
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
    void banana_slide(void);
    
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
    void munching_apple(void);
    
    /*
     * Description
     *      The orange animation implements the 2D array data structure with the first array holding the design of the 
     *      fruit, and the second array holding essentially each animation frame. We went on a crafting website and 
     *      mapped out 8x8 grids to draw each orange frame that we wanted (in this case we used 10 animation slides) 
     *      which would correspond to the matrix. We wanted to make an orange grow gradually from the stop, so we carefully 
     *      added LED pixels from the top down in orange to make it seem as if it was growing naturally. Each row would 
     *      basically be a binary number; for example, in the first row, if the 4th pixel was supposed to be lit up we 
     *      would place 8 (0b0001000) in the array. Through nested for loops and if statements, we were able to successfully 
     *      map out our animations. For the color aspect, we created a placeholder array that is really just a shift register 
     *      containing data from the original fruit array. We bit masked the placeholder array with 0x80 to check the most 
     *      significant bit and put it in a temporary variable. If it was a 1, we would implement our writeColor(); function 
     *      with the respective color of orange in this case, if not we would leave the LED matrix blank. We additionally left 
     *      shifted the hold register one spot for each iteration so it was the second most significant bit that would be checked 
     *      for the next iteration.
     * Parameters 
     *      void 
     * Return
     *      void
     */
    void annoying_orange(void);
    
    /*
     * Description
     *      The grape animation also implements the 2D array data structure with the first array holding the design of the fruit, 
     *      and the second array holding essentially each animation frame. We went on a crafting website and mapped out 8x8 grids 
     *      to draw each grape frame that we wanted (in this case we used 12 animation slides) which would correspond to the matrix. 
     *      We wanted to make grapes being picked off one by one from the bottom up, so we successfully took away LED pixels in purple 
     *      to make it seem as if someone was picking off grapes and eating them naturally. Each row would basically be a binary number; 
     *      for example, in the first row, if the 4th pixel was supposed to be lit up we would place 8 (0b0001000) in the array. Through 
     *      nested for loops and if statements, we were able to successfully map out our animations. For the color aspect, we created a 
     *      placeholder array that is really just a shift register containing data from the original fruit array. We bit masked the 
     *      placeholder array with 0x80 to check the most significant bit and put it in a temporary variable. If it was a 1, we would 
     *      implement our writeColor(); function with the respective color of purple in this case, if not we would leave the LED matrix 
     *      blank. We additionally left shifted the hold register one spot for each iteration so it was the second most significant bit 
     *      that would be checked for the next iteration.
     * Parameters 
     *      void 
     * Return
     *      void
     */
    void grapes_of_wrath(void);

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

