//Justin Luk
//CS 2110 HW11

#include "game.h"
#include "mylib.h"
#include "title.h"
#include "overWin.h"
#include "overLose.h"
#include "imageArr.h"

//title screen
void initializeTitle() {
  while(!KEY_DOWN_NOW(BUTTON_START)){
    flipPage();
    drawScreen4(title_palette,TrunksTitle);
    drawString4(25, 60, "DRAGONBALL Z", 0);
    drawString4(35, 50, "HISTORY OF TRUNKS", 0);
    drawString4(85, 15, "HIT ENTER TO BEGIN", 0);
    drawString4(25, 61, "DRAGONBALL Z", 0);
    drawString4(35, 51, "HISTORY OF TRUNKS", 0);
    drawString4(85, 16, "HIT ENTER TO BEGIN", 0);
    waitForVblank();
  }
}

//lose screen
void gameOverLose() {
  while(!KEY_DOWN_NOW(BUTTON_START)){
    flipPage();
    drawScreen4(overLose_palette,GameOverLose);
    drawString4(25,140,"EARTH IS LOST...", 0);
    drawString4(25,141,"EARTH IS LOST...", 0);  
    drawString4(145,40,"PRESS ENTER TO REVIVE TRUNKS!", 0);
    drawString4(145,41,"PRESS ENTER TO REVIVE TRUNKS!", 0);  
  }
}

//win screen
void gameOverWin() {
  while(!KEY_DOWN_NOW(BUTTON_START)){
    flipPage();
    drawScreen4(overWin_palette,GameOverWin);
    drawString4(145,40,"PRESS ENTER TO FIGHT AGAIN!", 2);
    drawString4(145,41,"PRESS ENTER TO FIGHT AGAIN!", 2);  
  }
}

//four corner box collision check creating O(1) check
int collisionDetectPlayer(Avatar p, Avatar att) {
  if (p.x < att.x+att.width && p.x+p.width > att.x &&
    p.y < att.y+att.height && p.height+p.y > att.y){
    return 1;
  }
  return 0;
}

//check states of avatar for animation
//ensures sucessive drawing through completion
//also handles drawing which sprite we need
void drawTrunks(Avatar p){
  if (p.state == 0){
    drawImage4(p.y,p.x,p.width,p.height,FutureTrunks);
  } else if (p.state == 1){
    drawImage4(p.y,p.x,p.width,p.height,trunks2);
  } else if (p.state == 2){
    drawImage4(p.y,p.x,p.width,p.height,trunks3);
  } else if (p.state == 3) {
    drawImage4(p.y,p.x,p.width,p.height,trunks4);
  } else if (p.state == 4) {
    drawImage4(p.y,p.x,p.width,p.height,trunks5);
  } else if (p.state == 5) {
    drawImage4(p.y,p.x,p.width,p.height,sstrunks);
  }

}