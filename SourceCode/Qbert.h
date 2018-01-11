#ifndef _QBERT_
#define _QBERT_ 
#include "Sprites.h"
#include "Animation.h"

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
	void SetX(int x) {
		sprite->SetX(x);
	}
	void SetY(int y) {
		sprite->SetY(y);
	}

	int GetCurrRow() {
		return currRow;
	}
	int GetCurrCol() {
		return currCol;
	}

	void moveRight() {
		currCol++;
	}
	void moveLeft() {
		currCol--;
	}
	void moveDownRight() {
		currRow++;
		currCol++;
		sprite->Move(50, 75);
	}
	void moveDownLeft() {
		currRow++;
		sprite->Move(-50, 75);
		
	}
	void moveUpRight() {
		currRow--;
		sprite->Move(50, -75);

	}
	void moveUpLeft() {
		currRow--;
		currCol--;
		sprite->Move(-50, -75);
	}

	void PrintPos() {
		cout << "ROW " << currRow << " COLL " << currCol << endl;
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
		}
		return film;
	}

	/*void Animation() {   //!!!!!!!! gia test einai ayth h method
		std::list<PathEntry> path;
		PathEntry *p;
		for (int i = 0; i < 4; ++i) {
			p = new PathEntry(-10, 0, i, 1);
			path.push_back(*p); // oxi polu kalo pou einai pointer alla einai demo
		}

		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");  
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());
	}*/

	Qbert(int x, int y){
		Create(x,y);
		currRow = 1;
		currCol = 1;
	}
};

#endif