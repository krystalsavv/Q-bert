#ifndef _BALL_H_
#define _BALL_H_
#include "Sprites.h"
#include <ctime>

class Ball {
	Sprite *sprite;
public:
	void Create(string id, int x, int y) {
		AnimationFilm* film = GetFilm();
		sprite = new Sprite(id, film, x, y, 38, 43, 20); 
		spriteList.Insert(sprite);
	}
	
	void SetFrame(unsigned FrameNo) {
		sprite->SetFrame(FrameNo);
	}
	void SetX(int x) {
		sprite->SetX(x);
	}
	void SetY(int y) {
		sprite->SetY(y);
	}
	Sprite* GetSprite() {
		return sprite;
	}

	void Destroy(){} //!!!!!!!!!!!! kathe fora pou feygei kapoio ball apo to window

	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("balls");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 13;
			rect.w = 13;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 13;
			rect.y = 0;
			rect.h = 13;
			rect.w = 13;
			boxes.push_back(rect);
			rect.x = 26;
			rect.y = 0;
			rect.h = 13;
			rect.w = 10;
			boxes.push_back(rect);
			rect.x = 36;
			rect.y = 0;
			rect.h = 13;
			rect.w = 10;
			boxes.push_back(rect);
			rect.x = 46;
			rect.y = 0;
			rect.h = 13;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 62;
			rect.y = 0;
			rect.h = 13;
			rect.w = 18;
			boxes.push_back(rect);
			string id = "balls";
			AnimationFilmHolder::Get().Load(id, "Sprites/BallsFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("balls");
		}
		return film;
	}

	Ball(char *id, int x, int y){
		Create(id, x, y);
		SetFrame(1);
	}

	Ball(string id, int x, int y) {
		Create(id, x, y);
		SetFrame(1);
	}


};


#endif