#ifndef _QBERT_
#define _QBERT_ 
#include "Sprites.h"

//the Qbert's position for cube with center (xc,yc) is xc-25,yc-50

class Qbert {
	Sprite *sprite;
	int currRow;
	int currCol;
public:
	void Create(int x, int y) {
		AnimationFilm* film = GetFilm();
		sprite = new Sprite("Qbert",film,x, y, 50, 50, 20);
		spriteList.Insert(sprite);		
	}

	void SetZOrder(unsigned zOrder) {  // check an ta allazei kai sthn list
		sprite->SetZOrder(zOrder);
	}
	void SetFrame(unsigned FrameNo) {
		sprite->SetFrame(FrameNo);
	}
	int GetCurrRow() {
		return currRow;
	}
	int GetCurrCol() {
		return currCol;
	}

	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("Qbert");
		if (film == nullptr) {
			SDL_Rect rect;
			vector<SDL_Rect> boxes;
			for (int i = 0; i < 120; i += 15) {
				rect.x = i;
				rect.y = 0;
				rect.h = 16;
				rect.w = 15;
				boxes.push_back(rect);
			}
			string id = "Qbert";
			AnimationFilmHolder::Get().Load(id, "Sprites/QbertFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("Qbert");
			return film;
		}
	}

	Qbert(int x, int y){
		Create(x,y);
		currRow = 1;
		currCol = 1;
	}
};



#endif