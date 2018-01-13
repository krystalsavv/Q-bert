#include <iostream>
#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"
#include "Animation.h"
#include "Disk.h"
#include "Ball.h"
#include "AI.h"

//global
Game* game = nullptr;
SpriteList spriteList = SpriteList(); 

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();
AnimatorHolder AnimatorHolder::animatorHolder = AnimatorHolder();
list<Animator*> AnimatorHolder::running;
list<Animator*> AnimatorHolder::suspended;

int Disk::lala = 0;

int AI::sum = 0;


int main(int argc, char* args[]) {
	game = new Game();
	game->init("Q*bert", 200, 40, 800, 700, 0);

	IsometricPyramid *terrain = new IsometricPyramid(400, 80, 7, 26,74);
	Qbert *qbert = new Qbert(377,56);
	Disk *diskLeft = new Disk("DiskLeft", 70, 350);
	Disk *diskRight = new Disk("DiskRight", 680, 350);
	
	game->SetGameTime();  // arxhkopoiw to game->currTime (den einai swsto ekei kai prepei na fygei apla to xrhsimopoiw gia na dwkomasw to Qbert::Animation())
	diskLeft->Spin();
	diskRight->Spin();
	AI* ai = new AI(game->GetGameTime());
	game->SetSprite(terrain, qbert, diskLeft, diskRight, ai);
	while (game->running()) {
		game->SetGameTime();
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}


