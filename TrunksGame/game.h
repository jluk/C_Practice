//Justin Luk
//CS 2110 HW11

//Struc definitions
struct avatar {
	int x;
	int y;
	int oldx;
	int oldy;
	int height;
	int width;
	int velocity;
	int yvelocity;
	int state;
};

typedef struct avatar Avatar;
//Function Prototypes
void initializeTitle();
int collisionDetectPlayer(Avatar p, Avatar att);
void updateLives(int lives, int enemyLives);
void gameOverLose();
void gameOverWin();
void drawTrunks(Avatar p);
