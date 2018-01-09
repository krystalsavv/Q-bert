#include <iostream>
#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"

//if (dynamic_cast<Var&>(v))

//global
Game* game = nullptr;
SpriteList spriteList = SpriteList(); 

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();

int main(int argc, char* args[]) {
	game = new Game();
	game->init("Q*bert", 200, 40, 800, 700, 0);

	IsometricPyramid *terrain = new IsometricPyramid(400, 80, 7, 26,74);
	Qbert *qbert = new Qbert(375,56);

	game->SetSprite(terrain, qbert);


	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}


