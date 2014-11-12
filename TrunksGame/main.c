//Justin Luk
//CS 2110 HW 11

#include "mylib.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include "imageArr.h"

#define NUMEN 5
#define MAXROW 159

int startGame();

int main (void) {
  REG_DISPCNT = (MODE4 | BG2_ENABLE);
  int gameState = 0;
	while(1) {
		switch(gameState){
			case 0: 
				initializeTitle();
				gameState = 1;
				break;
			case 1:
				gameState = startGame();
				break;
			case 2:
				gameOverLose();
				gameState = 0;
				break;
			case 3:
				gameOverWin();
				gameState = 0;
				break;
		}
		flipPage();
	}
}

int startGame(){

  int rightOn = 0;
  int SS = 0;
  int ssLength = 5;
  int lives = 3;
  int score = 0;

  //player contains attributes of the trunks image
  Avatar player;
  player.x = 20;
  player.y = 80;
  player.height = 32;
  player.width = 22;
  player.oldx = player.x;
  player.oldy = player.y;
  player.velocity = 3;
  player.yvelocity = 0;
  player.state = 0;
  //player kiAtt attack
  Avatar kiAtt;
  kiAtt.x = 200;
  kiAtt.y = 200;
  kiAtt.height = 16;
  kiAtt.width = 20;
  kiAtt.oldx = kiAtt.x;
  kiAtt.oldy = kiAtt.y;
  kiAtt.velocity = 2;
  kiAtt.yvelocity = 0;
  kiAtt.state = 0;

//set in game palette
  setPalette(imageArr_palette, 256);
//randomize speeds of enemies
  int speeds[] = {1,2};
  int numspeeds = sizeof(speeds)/sizeof(speeds[0]);

  Avatar enemies[NUMEN];
  for (int i = 0; i < NUMEN; i++) {
  	enemies[i].y = 1 + rand()%160;
  	enemies[i].x = 229;
  	enemies[i].velocity = 1;
  	enemies[i].yvelocity = speeds[rand()%numspeeds];
  	enemies[i].width = 10;
  	enemies[i].height = 10;
  	enemies[i].state = 1;
  }

  Avatar *cur; //pointer to iterate over enemy arr
  int frames = 5; //counter for animation
  //int waves = 3; //counter for waves
  while (1){

	flipPage();
	waitForVblank();
	drawColorScreen(5);
	//draw SS bar (30 = bright org, 31 = dark org)
	drawString4(1,20,"POWER LVL:",32);
	drawRect4(2,90,15*ssLength,5,33);
	//draw ocean front
	drawRect4(0,0,8,160,3);
	//draw scoreboard
	drawString4(150,15,"LIVES:",7);
	if (lives == 3){
		drawString4(150,55,"***",8);
	} else if (lives==2){
		drawString4(150,55,"**",9);
	} else if (lives == 1){
		drawString4(150,55,"*",12);
	}

	drawString4(150,160, "SCORE:",4);
	char str[4];
	sprintf(str, "%d", score);
	drawString4(150,200,str,4);

//wait x amount of frames for each animation frame
	if (frames) 
	{ 
		frames--; 
	} 
	else 
	{
		if (player.state == 1){
			player.state = 2;
		} else if (player.state == 2){
			player.state = 3;
		} else if (player.state == 3) {
			player.state = 4;
		} else if (player.state == 4){
			player.state = 5;
		} 
		frames = 5;
	}

//draw trunks depending on his current state
	drawTrunks(player);

//player is SS, speed up movement + attack
//otherwise normal settings
  	if (SS) {
  		player.velocity = 5;
  		kiAtt.velocity = 5;
  	} else {
  		player.velocity = 3;
  		kiAtt.velocity = 2;
  	}

//if attack is engaged, animate ball
//if it reaches end of screen, erase and reset flag to
//renable shooting again
	if (rightOn){ //flag to decide if player can shoot again
		//if size of ball is not on end of screen, keep animating
		drawImage4(kiAtt.y,kiAtt.x,kiAtt.width,kiAtt.height,ki);
		if (kiAtt.x < 240-(kiAtt.width)){
			kiAtt.x += kiAtt.velocity;
		} else if (kiAtt.x >= 240-kiAtt.width){
			rightOn = 0;
			kiAtt.x = 200;
			kiAtt.y = 200;
		}
	}

/*
* Controls/User Input
*
*/
  	//Update avatar coordinates for movement	
	if(KEY_DOWN_NOW(BUTTON_UP) && player.y > 10)
		{
			player.y -= player.velocity;
		}
	if(KEY_DOWN_NOW(BUTTON_DOWN) && player.y < 145-player.height)
		{
			player.y += player.velocity;
		}
	if(KEY_DOWN_NOW(BUTTON_RIGHT) && player.x < 120-player.width)
		{
			player.x += player.velocity;
		}
	if(KEY_DOWN_NOW(BUTTON_LEFT) && player.x > 10)
		{
			player.x -= player.velocity;
		}
	if (KEY_DOWN_NOW(BUTTON_R) && rightOn == 0)
		{
			//Fire attack, set flag to wait until gone
			//until you can fire again
			rightOn = 1;
			kiAtt.x = player.x+player.width;
	  		kiAtt.y = player.y+(player.height/2);
	  		//counter to shoot in SS
	  		if (SS){
	  			ssLength--;
	  		}
		}
	if (KEY_DOWN_NOW(BUTTON_L) && SS == 0)
		{
			player.state = 2; //initiate powerup
			SS = 1; //turn on SS mode
		}
	if (KEY_DOWN_NOW(BUTTON_SELECT)) //RESET GAME
		{
		return 0;
		}

/*
* After player shoots x times, revert to normal
*/
	if (ssLength <= 1){
		player.state = 0;
		SS = 0;
		ssLength = 5;
	}

/* ITERATE OVER ENEMY ARRAY
* enemy update positions
* enemy drawing
*/
	for(int i = 0; i < NUMEN; i++) {
		cur = enemies + i;
		cur->y = cur->y + cur->yvelocity;
		cur->x = cur->x - cur->velocity;

		//alter horizontal movement
		if (cur->y < 10){
			cur->y = 10;
			cur->yvelocity = -cur->yvelocity;
		}
		if (cur->y > (MAXROW-10) - cur->width){
			cur->y =  MAXROW-10-cur->width;
			cur->yvelocity = -cur->yvelocity;
		}

		//force vertical movement
		if (cur->x < 0){
			cur->x = 0;
			drawRect4(cur->y,cur->x,cur->width,cur->height,5);
			cur->state = 0;
			lives--;
		}
		if (collisionDetectPlayer(enemies[i], kiAtt)){
			score += 100;
			cur->state = 0;
			drawImage4(kiAtt.y,kiAtt.x,24,24,ki2);
			rightOn = 0;
			kiAtt.x = 200;
			kiAtt.y = 200;
		}
	}

/*
* DRAW ENEMIES STILL ALIVE
*/
	for(int i = 0; i < NUMEN; i++) {
		cur = enemies + i;
		if (cur->state){
			drawRect4(cur->y,cur->x,cur->width,cur->height,17);
		}
	}
//LOSING CONDITION
	if (lives < 1){
		return 2;
	}
//WINNING CONDITION
	if (score > 399) {
		return 3;
	}

//update trunks position
	player.oldx = player.x;
	player.oldy = player.y;

  }

  return 0;

}
