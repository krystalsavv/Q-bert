#include <iostream>
#include "Game.h"
#include "Sprites.h"

Game* game = nullptr;

//static 
AnimationFilmHolder AnimationFilmHolder::holder = AnimationFilmHolder();
Sprite *s;

int main(int argc, char* args[]) {
	game = new Game();
	game->init("Q*bert", 200, 40, 800, 700, 0);
	/****************/
	AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("cube");
	if (film == nullptr) {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.h = 100;
		rect.w = 100;
		vector<SDL_Rect> boxes;
		boxes.push_back(rect);
		string id = "cube";
		AnimationFilmHolder::Get().Load(id ,"Sprites/Active_1.bmp", boxes); //vector<SDL_Rect> boxes??? ton ftiaxnw ap eksw
		film = AnimationFilmHolder::Get().GetFilm("cube");
	}
	s = new Sprite("cube",film, 0,0,100,100,100);

	/***************/
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}


