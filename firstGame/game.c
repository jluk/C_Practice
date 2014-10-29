//Justin Luk
//CS 2110 HW9

#include "game.h"
#include "mylib.h"

//initialize game screen
void initializeGame(){
	for(int i=0; i<38400; i++) {
		videoBuffer[i] = BLACK;
	}
		
	drawRect(0,195,45,260,BLUE);
	drawString(10,200,"SCORE:",WHITE);
	drawString(20,200,"N/A",YELLOW);
	drawString(80,200, "LIVES:", WHITE);
	drawString(90,200, "***", GREEN);
}

//draw win screen when score == 5
void createWinScreen() {
	drawRect(0,0,260,160,GREEN);
  	drawString(55,80,"KILLER DUDE!", PURPLE);
  	drawString(70,55,"YOUR TURTLE IS FULL!", PURPLE);
  	drawString(90,55, "Hit enter to continue", PURPLE);
	drawString(100,65, "Hit B for a prize!", PURPLE);
}

//four corner box collision check creating O(1) check
int collisionDetect(int eX, int eY, int eW, int eH, int aX, int aY, int aW, int aH) {

//if left half of avatar (top left, bottom left) corners enter enemy object return true
  if ((aX >= eX && aX <= eX+eW) && ((aY >= eY && aY <= eY+eH) || (aY+aH >= eY && aY+aH <= eY+eH))){
    return 1;
  }
//if right half of avatar (top right, bottom right) corners enter enemy object return true
  if ((aX+aW >= eX && aX+aW <= eX+eW) && ((aY >= eY && aY <= eY+eH) || (aY+aH >= eY && aY+aH <= eY+eH))) {
    return 1;
  }

//otherwise did not collide
  return 0;
}

//paint over game screen to decrement lives
void updateLives(int lives) {
	if (lives == 2) {
		drawRect(90,200,20,40,BLUE);
		drawString(90,200,"**",GREEN);
	} else if (lives == 1){
		drawRect(90,200,20,20,BLUE);
		drawString(90,200,"*",GREEN);
	}
}

//paint over game screen to update score of pizzas eaten
void updateScore(int score) {
  if (score == 1){
	    drawRect(20,200,20,20,BLUE);
	    drawPizza(200,20);
  } else if (score == 2){
	    drawPizza(210,20);
  } else if (score ==3){
    	drawPizza(220,20);
  } else if (score == 4) {
    	drawPizza(205,30);
  } else if (score == 5) {
    	drawPizza(215,30);
  }
}