#include <iostream>
#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"
#include "Animation.h"
#include "Disk.h"

//global
Game* game = nullptr;
SpriteList spriteList = SpriteList(); 

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();
AnimatorHolder AnimatorHolder::animatorHolder = AnimatorHolder();
list<Animator*> AnimatorHolder::running;
list<Animator*> AnimatorHolder::suspended;

int Disk::lala = 0;

int main(int argc, char* args[]) {
	game = new Game();
	game->init("Q*bert", 200, 40, 800, 700, 0);

	IsometricPyramid *terrain = new IsometricPyramid(400, 80, 7, 26,74);
	Qbert *qbert = new Qbert(377,56);
	Disk *diskLeft = new Disk("DiskLeft", 70, 350);			// ftiaxnw ta 2 disk sthn othonh (tsekare thn Disk::Create())
	Disk *diskRight = new Disk("DiskRight", 680, 350);


	game->SetSprite(terrain, qbert, diskLeft, diskRight);	//me aythn thn synarthsh ta krataw sto game object
	game->SetGameTime();  // arxhkopoiw to game->currTime (den einai swsto ekei kai prepei na fygei apla to xrhsimopoiw gia na dwkomasw to Qbert::Animation())
	qbert->Animation();

	while (game->running()) {
		game->SetGameTime();
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}


