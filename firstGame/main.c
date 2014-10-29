//Justin Luk
//CS 2110 HW 9

#include "mylib.h"
#include "game.h"
#include <stdlib.h>

extern u16 *videoBuffer;

int main (void) {

  REG_DISPCNT = (MODE3 | BG2_ENABLE);
  //counters for game session
  int lives = 3;
  int score = 0;
  int size = 7;
  int esize = 10;
  int oldsize = size;
  //boolean win flag
  int win = 0;
  //avatar attributes
  int avatarX = 95;
  int avatarY = 150;
  int oldAvatarX = avatarX;
  int oldAvatarY = avatarY;
  int avatarVelocity = 2;

  //horizontal enemy1 attributes
  int enemy1X = 10;
  int enemy1Y = rand() % 145;
  int oldEnemy1X = enemy1X;
  int oldEnemy1Y = enemy1Y;
  int enemy1Velocity = 2;

  //fast vertical enemy2 attributes
  int enemy2X = rand()%180;
  int enemy2Y = 10;
  int oldEnemy2X = enemy2X;
  int oldEnemy2Y = enemy2Y;
  int enemy2Velocity = 4;
  int enemy2XVelocity = 2;

  //horizontal enemy3 attributes
  int enemy3X = 100;
  int enemy3Y = rand()%145;
  int oldEnemy3X = enemy3X;
  int oldEnemy3Y = enemy3Y;
  int enemy3Velocity = 2;

//Randomize Pizza!
  int p1x = rand() % 180;
  int p1y = rand() % 140;
  int p2x = rand() % 180;
  int p2y = rand() % 140;
  int p3x = rand() % 180;
  int p3y = rand() % 140;
  int p4x = rand() % 180;
  int p4y = rand() % 140;
  int p5x = rand() % 180;
  int p5y = rand() % 140;

//INTRO SCREEN
  drawString(50, 35, "TEENAGE MUTANT NINJA TURTLES", GREEN);
  drawString(65, 80, "PIZZA FRENZY", RED);
  drawString(85, 15, "Insert coins (hit enter) to continue", WHITE);
  while(!KEY_DOWN_NOW(BUTTON_START));
	
//SETUP GAME SCREEN
  initializeGame();

  while(1){  // The Game Loop

	//draw pizzas
	drawPizza(p1x,p1y);
	drawPizza(p2x,p2y);
	drawPizza(p3x,p3y);
	drawPizza(p4x,p4y);
	drawPizza(p5x,p5y);

	//enemy1 movement
	enemy1X += enemy1Velocity;

	if (enemy1X > 195-size) { //right screen boundary
		enemy1X = 195-size;
		enemy1Velocity = -enemy1Velocity;
	} else if (enemy1X < 0) { //left screen boundary
		enemy1X = 0;
		enemy1Velocity = -enemy1Velocity;
	}

	enemy2Y += enemy2Velocity;
	enemy2X += enemy2XVelocity;

	//enemy2 movement
	if(enemy2Y < 0) //top screen boundary
	{
		enemy2Y = 0;
		enemy2Velocity = -enemy2Velocity; //change direction
	}										
	if(enemy2Y > 149-esize) //bottom screen boundary
	{
		enemy2Y = 149-esize;
		enemy2Velocity = -enemy2Velocity;
	}
	if(enemy2X > 195-esize){
		enemy2X = 195-esize;
		enemy2XVelocity = -enemy2XVelocity;
	} else if (enemy2X < 0) {
		enemy2X = 0;
		enemy2XVelocity = -enemy2XVelocity;
	}

	enemy3X += enemy3Velocity;

	if (enemy3X > 195-size) { //right screen boundary
		enemy3X = 195-size;
		enemy3Velocity = -enemy3Velocity;
	} else if (enemy3X < 0) { //left screen boundary
		enemy3X = 0;
		enemy3Velocity = -enemy3Velocity;
	}

	//enemy collision detection
	//require multiple if without using strucs
	if (collisionDetect(enemy1X,enemy1Y,size,size,avatarX,avatarY,size,size)){
		lives--;
		updateLives(lives);
		if(lives > 0)
		{
			avatarX = 95;
			avatarY = 150;
		} else {
			break;
		}
	}

	if (collisionDetect(enemy2X,enemy2Y,esize,esize,avatarX,avatarY,size,size)){
		lives--;
		updateLives(lives);
		if(lives > 0)
		{
			avatarX = 95;
			avatarY = 150;
		} else {
			break;
		}
	}

	if (collisionDetect(enemy3X,enemy3Y,size,size,avatarX,avatarY,size,size)){
		lives--;
		updateLives(lives);
		if(lives > 0)
		{
			avatarX = 95;
			avatarY = 150;
		} else {
			break;
		}
	}

	//pizza collision detection
	if (collisionDetect(p1x,p1y,7,7,avatarX,avatarY,size,size)){
		drawRect(p1y,p1x,7,7,BLACK);
		p1x = 260;
		p1y = 260;
		score++;
		updateScore(score);
	}
	if (collisionDetect(p2x,p2y,7,7,avatarX,avatarY,size,size)){
		drawRect(p2y,p2x,7,7,BLACK);
		p2x = 260;
		p2y = 260;
		score++;
		updateScore(score);
	}
	if (collisionDetect(p3x,p3y,7,7,avatarX,avatarY,size,size)){
		drawRect(p3y,p3x,7,7,BLACK);
		p3x = 260;
		p3y = 260;	
		score++;
		updateScore(score);
	}
	if (collisionDetect(p4x,p4y,7,7,avatarX,avatarY,size,size)){
		drawRect(p4y,p4x,7,7,BLACK);	
		p4x = 260;
		p4y = 260;	
		score++;
		updateScore(score);
	}
	if (collisionDetect(p5x,p5y,7,7,avatarX,avatarY,size,size)){
		drawRect(p5y,p5x,7,7,BLACK);	
		p5x = 260;
		p5y = 260;	
		score++;
		updateScore(score);
	}
	//condition to check if eaten all pizza
	if (score == 5){
		win = 1;
		break;
	}
		
//Update avatar coordinates for movement	
	if(KEY_DOWN_NOW(BUTTON_UP) && avatarY > 1)
		{
		avatarY-=avatarVelocity;
		}
	if(KEY_DOWN_NOW(BUTTON_DOWN) && avatarY < 159-size)
		{
		avatarY+=avatarVelocity;
		}
	if(KEY_DOWN_NOW(BUTTON_RIGHT) && avatarX < 194-size)
		{
		avatarX+=avatarVelocity;
		}
	if(KEY_DOWN_NOW(BUTTON_LEFT) && avatarX > 1)
		{
		avatarX-=avatarVelocity;
		}

//Draw new blocks based on movement input
	//avatar update
	drawRect(oldAvatarY,oldAvatarX,oldsize,oldsize,BLACK);
	drawRect(avatarY,avatarX,size,size,GREEN);
	drawCircle(avatarY+(size/2),avatarX+(size/2),size/3,PURPLE);
	//enemy 1 update
	drawRect(oldEnemy1Y,oldEnemy1X,oldsize,oldsize,BLACK);
	drawRect(enemy1Y,enemy1X,size,size,RED);
	//enemy 2 update
	drawRect(oldEnemy2Y,oldEnemy2X,esize,esize,BLACK);
	drawRect(enemy2Y,enemy2X,esize,esize,RED);
	drawCircle(enemy2Y+(esize/2),enemy2X+(esize/2),esize/3,WHITE);
	//enemy 3 update
	drawRect(oldEnemy3Y,oldEnemy3X,oldsize,oldsize,BLACK);
	drawRect(enemy3Y,enemy3X,size,size,RED);

  	waitForVblank();

  	//update all coordinates for blocks
 	oldAvatarX = avatarX;
  	oldAvatarY = avatarY;
  	oldEnemy1X = enemy1X;
  	oldEnemy1Y = enemy1Y;
  	oldEnemy2X = enemy2X;
  	oldEnemy2Y = enemy2Y;
  	oldEnemy3X = enemy3X;
  	oldEnemy3Y = enemy3Y;
  	oldsize = size;

  }

//END SCREEN

  if (win){
  	createWinScreen();
	while (!KEY_DOWN_NOW(BUTTON_START) || !KEY_DOWN_NOW(BUTTON_B)){
	  	if(KEY_DOWN_NOW(BUTTON_START)){
			main();
		}
		if (KEY_DOWN_NOW(BUTTON_B)){
			drawRect(0,0,260,260,PURPLE);
			drawString(40,80,"$<(oo)>$", WHITE);
			drawString(60,65,"Kirby has a prize!", WHITE);
			drawString(80,80,"$$", WHITE);
			drawString(90,80,"(^oo)>$", WHITE);
		}
	}
  } else {
	drawRect(0,0,260,50,RED);
	drawRect(50,0,260,50,RED);
	drawRect(100,0,260,50,RED);
	drawRect(150,0,260,50,RED);
	drawString(50,85, "TURTLE DOWN!", BLACK);
	drawString(70, 60, "Hit enter to respawn", BLACK);
	drawString(90, 50, "Hit B for encouragement", BLACK);
	while (!KEY_DOWN_NOW(BUTTON_START) || !KEY_DOWN_NOW(BUTTON_B)){
		 if(KEY_DOWN_NOW(BUTTON_START)){
			main();
		  }
		  if (KEY_DOWN_NOW(BUTTON_B)){
			drawRect(0,0,260,260,BLACK);
			drawString(70,60,"SEND PIZZA TO DEV", RED);
			drawString(80,52,"FOR SWEET CHEAT CODES", RED);
		  }
	  }
	}
}
