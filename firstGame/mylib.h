//Justin Luk
//CS 2110 HW 9

typedef unsigned short u16;

#define REG_DISPCNT *(u16 *)0x4000000


extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OFFSET(r, c, rowlen)  ((r)*(rowlen)+(c))
#define COLOR(r, g, b)  ((r) | (g)<<5 | (b)<<10)

// C O L O R S

#define RED COLOR(31,0,0)
#define GREEN COLOR(0, 31,0)
#define BLUE COLOR(0, 0, 31)
#define LIGHTBLUE COLOR(10,15,28)
#define CYAN COLOR(0, 31, 31)
#define PURPLE COLOR(31, 0, 31)
#define YELLOW COLOR(31, 31, 0)
#define WHITE COLOR(31, 31, 31)
#define BLACK 0

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT		(1<<2)
#define BUTTON_START		(1<<3)
#define BUTTON_RIGHT		(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS *(volatile unsigned int *)0x4000130

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006


//Function Prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void drawCircle(int r, int c, int radius, u16 color);
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void drawPizza(int x, int y);
void waitForVblank();
