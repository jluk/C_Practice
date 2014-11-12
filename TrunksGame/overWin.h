/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 overWin /home/justin/Documents/hw11/GameOverWin.png 
 * Time-stamp: Monday 11/10/2014, 20:53:41
 * 
 * Image Information
 * -----------------
 * /home/justin/Documents/hw11/GameOverWin.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * To err is human... to really foul up requires the root password.
 * 
 * Your life will be happy and peaceful.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef OVERWIN_BITMAP_H
#define OVERWIN_BITMAP_H

extern const unsigned short overWin_palette[256];
#define OVERWIN_PALETTE_SIZE 256

extern const unsigned short GameOverWin[19200];
#define GAMEOVERWIN_SIZE 19200
#define GAMEOVERWIN_WIDTH 240
#define GAMEOVERWIN_HEIGHT 160

#endif

