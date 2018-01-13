#ifndef _DISK_H_
#define _DISK_H_
#include "Sprites.h"
#include "Animation.h"

class Disk {
	Sprite *sprite;
	static int lala;		// den xreiazetai apla gia na emfanizw kai tous 2 typous diskwn (me kai xwris qbert) sto window
							// to xrhsimopoio apla sthn create alla tha fygei apo ton teliko code 
	std::list<PathEntry> path;

public:
	void Create(string id, int x, int y) {
		AnimationFilm* film;
		//if (lala == 0)
			film = GetFilm();								// fortonei to film tou aplou diskou 
		//else
			//film = GetFilm_withQbert();						// fortonei to film tou diskou me qbert
		sprite = new Sprite(id, film, x, y, 47, 47, 15);	// diastaseis gia aplo disko
		//sprite = new Sprite(id, film, x, y, 66, 66, 15);	// diastaseis gia disko me qbert

		spriteList.Insert(sprite);
		
		//if(lala==1)
			//SetFrameSize(66, 66);		// allazei tis diastaseis toy sprite aytou sthn othinh (mporei na xreiastei gt exoume aythn thn diafora twn diastasewn)
										// edw ta allazw gia na emfanizei komple kai ton disk me qbert
		//++lala;
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
	void Spin() {
		
		PathEntry *p1 = new PathEntry(0, 0, 0,250);
		PathEntry *p2 = new PathEntry(0, 0, 1, 250);
		PathEntry *p3 = new PathEntry(0, 0, 2, 250);
		PathEntry *p4 = new PathEntry(0, 0, 3, 250);
		for (int i = 0; i < 30; ++i) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
		}
		MovingPathAnimation* diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator* diskAnimator = new MovingPathAnimator(sprite, diskAnimation,true);
		diskAnimator->Start(game->GetGameTime());

		path.clear();
		
	}
	void MoveUpLeft() {

		PathEntry *p = new PathEntry(0, 0, 0, 700);
		path.push_back(*p);
		PathEntry *p1 = new PathEntry(20, -20, 0, 100);
		PathEntry *p2 = new PathEntry(20, -20, 1, 100);
		PathEntry *p3 = new PathEntry(20, -20, 2, 100);
		PathEntry *p4 = new PathEntry(20, -20, 3, 100);
		PathEntry *p5 = new PathEntry(20, -20, 4, 100);
		for (int i = 0; i < 3; i++) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
		}
		PathEntry *p6 = new PathEntry(25, -45, 4, 150);
		path.push_back(*p6);


		MovingPathAnimation* diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator* diskAnimator = new MovingPathAnimator(sprite, diskAnimation,false);
		diskAnimator->Start(game->GetGameTime());

		path.clear();
		
	}

	void MoveUpRight() {

		PathEntry *p = new PathEntry(0, 0, 0, 500);
		path.push_back(*p);
		
		PathEntry *p1 = new PathEntry(-20, -20, 0, 100);
		PathEntry *p2 = new PathEntry(-20, -20, 1, 100);
		PathEntry *p3 = new PathEntry(-20, -20, 2, 100);
		PathEntry *p4 = new PathEntry(-20, -20, 3, 100);
		PathEntry *p5 = new PathEntry(-20, -20, 4, 100);
		for (int i = 0; i < 3; i++) {
			path.push_back(*p1);
			path.push_back(*p2);
			path.push_back(*p3);
			path.push_back(*p4);
			path.push_back(*p5);
		}
		PathEntry *p6 = new PathEntry(-25, -45, 4, 150);
		path.push_back(*p6);


		MovingPathAnimation* diskAnimation = new MovingPathAnimation(path, "disk_Animation1");
		MovingPathAnimator* diskAnimator = new MovingPathAnimator(sprite, diskAnimation,false);
		diskAnimator->Start(game->GetGameTime());

		path.clear();

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