/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 overLose /home/justin/Documents/hw11/GameOverLose.jpg 
 * Time-stamp: Monday 11/10/2014, 20:53:52
 * 
 * Image Information
 * -----------------
 * /home/justin/Documents/hw11/GameOverLose.jpg 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * To err is human... to really foul up requires the root password.
 * 
 * Your ability is appreciated.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef OVERLOSE_BITMAP_H
#define OVERLOSE_BITMAP_H

extern const unsigned short overLose_palette[256];
#define OVERLOSE_PALETTE_SIZE 256

extern const unsigned short GameOverLose[19200];
#define GAMEOVERLOSE_SIZE 19200
#define GAMEOVERLOSE_WIDTH 240
#define GAMEOVERLOSE_HEIGHT 160

#endif

