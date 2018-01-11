#ifndef _DISK_H_
#define _DISK_H_
#include "Sprites.h"
#include "Animation.h"

class Disk {
	Sprite *sprite;
	static int lala;		// den xreiazetai apla gia na emfanizw kai tous 2 typous diskwn (me kai xwris qbert) sto window
							// to xrhsimopoio apla sthn create alla tha fygei apo ton teliko code 

public:
	void Create(string id, int x, int y) {
		AnimationFilm* film;
		if (lala == 0)
			film = GetFilm();								// fortonei to film tou aplou diskou 
		else
			film = GetFilm_withQbert();						// fortonei to film tou diskou me qbert
		sprite = new Sprite(id, film, x, y, 47, 47, 15);	// diastaseis gia aplo disko
		//sprite = new Sprite(id, film, x, y, 66, 66, 15);	// diastaseis gia disko me qbert

		spriteList.Insert(sprite);
		
		if(lala==1)
			SetFrameSize(66, 66);		// allazei tis diastaseis toy sprite aytou sthn othinh (mporei na xreiastei gt exoume aythn thn diafora twn diastasewn)
										// edw ta allazw gia na emfanizei komple kai ton disk me qbert
		++lala;
	}

	//void Destroy(void) {} // normally at level program end

	void SetZOrder(unsigned zOrder) { 
		sprite->SetZOrder(zOrder);
	}
	void SetFrameSize(int w, int h) {
		sprite->GetDestinationRect().w = w;
		sprite->GetDestinationRect().h = h;
	}
	
	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("disks");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 16;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 32;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 48;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 64;
			rect.y = 0;
			rect.h = 18;
			rect.w = 16;
			boxes.push_back(rect);
			string id = "disks";
			AnimationFilmHolder::Get().Load(id, "Sprites/DisksFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("disks");
		}
		return film;
	}

	AnimationFilm* GetFilm_withQbert() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("spinning_qbert");
		if (film == nullptr) {
			SDL_Rect rect;
			vector<SDL_Rect> boxes;
			rect.x = 0;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 35;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 67;
			rect.y = 0;
			rect.h = 35;
			rect.w = 34;
			boxes.push_back(rect);
			rect.x = 96;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 128;
			rect.y = 0;
			rect.h = 35;
			rect.w = 35;
			boxes.push_back(rect);
			rect.x = 160;
			rect.y = 0;
			rect.h = 35;
			rect.w = 36;
			boxes.push_back(rect);
			string id = "spinning_qbert";
			AnimationFilmHolder::Get().Load(id, "Sprites/spinning_qbert.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("spinning_qbert");
		}
		return film;
	}

	Disk(string id,int x, int y) {
		Create(id, x, y);
	}

	Disk(char *id, int x, int y) {
		Create(id, x, y);
	}
};


// m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6)); 

#endif