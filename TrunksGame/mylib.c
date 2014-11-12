//Justin Luk
//CS 2110 HW 11

#include "mylib.h"
#include "game.h"
#include <stdlib.h>
#include "imageArr.h"


u16 *videoBuffer = (u16 *)0x6000000;
//change what is displayBuffer is pointing to as you flipPage
u16 *displayBuffer = (u16 *)0x600A000;

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color) {
  videoBuffer[OFFSET(r,c, 240)] = color;
}

void setPixel4(int row, int col, u8 index){
  int whichPixel = OFFSET(row, col, 240);
  int whichShort = whichPixel/2;
  if (col & 1) {
    videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
  } else {
    videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | (index);
  }
}

void drawScreen(const u16* image) {
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = 240*160 | DMA_ON;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int row, int col, int height, int width, u16 color) {
  int r;
  for (r = 0; r < height; r++) {
    DMA[3].src = &color;
    DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
    DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
  }
}

// A function to draw a HOLLOW rectangle starting at (r,c)
// NOTE: It has to run in O(w+h) time.
void drawHollowRect(int r, int c, int width, int height, u16 color){
  for (int i = r; i < (height + r); i++) {	/*draws first column*/
    setPixel(i,c,color);
  }

  for (int i = c; i < (width + c); i++) {	/*draws first row*/
    setPixel(r,i,color);
  }

  for (int i = r; i < (height + r); i++) {  	/*second column*/
    setPixel(i, c + (width - 1), color);
  }

  for (int i = c; i < (width + c); i++) { 	/*second row*/
    setPixel(r + (height - 1), i, color);
  }
}

//A function to draw a pixelated circle
void drawCircle(int r, int c, int radius, u16 color){
	for (int y = -radius; y <= radius; y++){
		for (int x = -radius; x <= radius; x++){
			if ((x*x) + (y*y) <= (radius*radius)){
				setPixel( x+r, y+c, color);
			}
		}
	}
}

//Lecture code on drawing chars onto screen
void drawChar4(int row, int col, char ch, u8 index)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				setPixel4(row+r, col+c, index);
			}
		}
	}
}

//Lecture code leveraging char to make strings
void drawString4(int row, int col, char *str, u8 index)
{
	while(*str)
	{
		drawChar4(row, col, *str++, index);
		col +=6;
	}
}

//interrupt
void waitForVblank()
{
  while(SCANLINECOUNTER > 160);
  while(SCANLINECOUNTER < 160);
}

/*
* Function to draw arbitrary sized image onto screen
* @param r row to draw image
* @param c col to draw image
* @param width width of image
* @param height height of image
* @param image Pointer to first element of image array
*/
void drawImage3(int r, int c, int width, int height, const u16* image){
  int temp;
  for (temp = 0; temp < height; temp++)
  {
    DMA[3].src = &image[OFFSET(temp,0,width)];
    DMA[3].dst = &videoBuffer[OFFSET(temp+r, c, 240)];
    DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
  }
}

//for single color to paint the screen
void drawColorScreen(u8 index){
  volatile u16 color = index<<8 | index;
  DMA[3].src = &color;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_ON;
}

//for full screen images
//set a new palette and paint it on the screen
void drawScreen4(const u16* colors, const u16* image){
  setPalette(colors,256);
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = 19200 | DMA_ON;
}

//iterate over palette and copy into mem location
void setPalette(const u16* colors, int elements){
  DMA[3].src = colors;
  DMA[3].dst = PALETTE;
  DMA[3].cnt = elements | DMA_ON;
}

void drawImage4(int r, int c, int width, int height, const u16* image){
  int temp;
  for (temp = 0; temp < height; temp++)
  {
    DMA[3].src = &image[OFFSET(temp,0,width/2)];
    DMA[3].dst = &videoBuffer[OFFSET(temp+r, c/2, 120)];
    DMA[3].cnt = (width/2) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
  }
}

void drawRect4(int row, int col, int w, int h, u8 index){
  volatile u16 color = index<<8 | index;
  int r;
  for (r=0; r<h; r++){
    DMA[3].src = &color;
    DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)/2];
    DMA[3].cnt = (w/2) | DMA_SOURCE_FIXED | DMA_ON;
  }
}

void flipPage()
{
  if(REG_DISPCNT & BUFFER1FLAG)
  {
    REG_DISPCNT = REG_DISPCNT & ~BUFFER1FLAG;
    videoBuffer = BUFFER1;
  }
  else
  {
    REG_DISPCNT = REG_DISPCNT | BUFFER1FLAG;
    videoBuffer = BUFFER0;
  }
}