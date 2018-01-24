#include <iostream>
#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Qbert.h"
#include "Animation.h"
#include "Disk.h"
#include "Ball.h"
#include "AI.h"

#include "SDL.h"

//global
Game* game = nullptr;
SpriteList spriteList = SpriteList(); 

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();
AnimatorHolder AnimatorHolder::animatorHolder = AnimatorHolder();
list<Animator*> AnimatorHolder::running;
list<Animator*> AnimatorHolder::suspended;

int AI::sum = 0;

void f() {
	game->init("Q*bert", 200, 40, 800, 700, 0, 0);
	SDL_Event event;
	int la = 1;
	while (la) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP) {
					//	game->init("Q*bert", 200, 40, 800, 700, 0, 1);
					la = 0;
					break;
				}
			case SDL_QUIT:
				game->SetRunning(false);
				break;
			default:
				break;
			}
		}
		game->render();
	}

}

int main(int argc, char* args[]) {
	game = new Game();
	while (true) {
		f();
		game->init("Q*bert", 200, 40, 800, 700, 0, 1);
		IsometricPyramid *terrain = new IsometricPyramid(400, 80, 7, 26, 74);
		Qbert *qbert = new Qbert(377, 56);
		Disk *diskLeft = new Disk("DiskLeft", 70, 350);
		Disk *diskRight = new Disk("DiskRight", 680, 350);
		diskLeft->Spin();
		diskRight->Spin();
		game->SetGameTime();  // arxhkopoiw to game->currTime (den einai swsto ekei kai prepei na fygei apla to xrhsimopoiw gia na dwkomasw to Qbert::Animation())

		AI* ai = new AI(game->GetGameTime());
		game->SetSprite(terrain, qbert, diskLeft, diskRight, ai);
		unsigned count = 0;
		while (game->running()) {
			game->SetGameTime();
			game->handleEvents();
			game->update();
			game->render();
			game->Collision();
			if (game->lose) {
				(game->GameLife)--;
				game->Lose();
				if (!(game->GameLife)) break;
				game->Restart();
			}
			if (game->win)
				count++;
			if (count == 800) {
				game->Lose();
				break;
			}
		}
	}
	game->clean();
	return 0;
}


