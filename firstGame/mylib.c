//Justin Luk
//CS 2110 HW 9

#include "mylib.h"
#include "game.h"

u16 *videoBuffer = (u16 *)0x6000000;

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color) {
  videoBuffer[OFFSET(r,c, 240)] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color) {
  for (int i = r ; i < (height + r) ; i++){
    for (int j = c; j < (width + c) ; j++){
      setPixel(i,j,color);
    }
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

// A function to draw a line moving into the bottom left quadrant
void plotLine(int x0, int y0, int x1, int y1, u16 color){
  int dx = x1 - x0;
  int dy = y1 - y0;

  int D = (dy+dy) - dx;

  setPixel(x0,y0,color);

  int y = y0;
  for (int i = x0+1 ; i <= x1 ; i++){
    if (D > 0){
      y++;
      setPixel(i,y,color);
      D += (dy+dy) - (dx+dx);
    } else {
      setPixel(i,y,color);
      D += (dy+dy);
    }
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
void drawChar(int row, int col, char ch, unsigned short color)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

//Lecture code leveraging char to make strings
void drawString(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col +=6;

	}
}

//draw a yellow pizza with 5 pepperonis
void drawPizza(int x, int y){
  drawRect(y,x,7,7,YELLOW);
  drawCircle(y+1,x+3,1,RED);
  drawCircle(y+4,x+5,1,RED);
  drawCircle(y+4,x+1,1,RED);
}

//interrupt
void waitForVblank()
{
  while(SCANLINECOUNTER > 160);
  while(SCANLINECOUNTER < 160);
}
