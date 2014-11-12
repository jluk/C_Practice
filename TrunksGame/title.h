/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 title /home/justin/Documents/hw11/TrunksTitle.png 
 * Time-stamp: Monday 11/10/2014, 20:53:26
 * 
 * Image Information
 * -----------------
 * /home/justin/Documents/hw11/TrunksTitle.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * To err is human... to really foul up requires the root password.
 * 
 * For hate is never conquered by hate. Hate is conquered by love.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef TITLE_BITMAP_H
#define TITLE_BITMAP_H

extern const unsigned short title_palette[256];
#define TITLE_PALETTE_SIZE 256

extern const unsigned short TrunksTitle[19200];
#define TRUNKSTITLE_SIZE 19200
#define TRUNKSTITLE_WIDTH 240
#define TRUNKSTITLE_HEIGHT 160

#endif

