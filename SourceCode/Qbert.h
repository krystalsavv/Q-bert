#ifndef _QBERT_
#define _QBERT_ 
#include "Sprites.h"
#include "Animation.h"

//the Qbert's position for cube with center (xc,yc) is xc-25,yc-50

class Qbert {
	Sprite *sprite;
	int currRow;
	int currCol;
	std::list<PathEntry> path;
public:
	void Create(int x, int y) {
		AnimationFilm* film = GetFilm();
		sprite = new Sprite("Qbert",film,x, y, 50, 50, 20); //48,48
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

	void moveRight() {
		currCol++;
	}
	void moveLeft() {
		currCol--;
	}
	void moveDownRight() {
		currRow++;
		currCol++;
		PathEntry *p1 = new PathEntry(0, 0, 0, 70);
		
		PathEntry *p4 = new PathEntry(0,0, 1,70);
		PathEntry *p5 = new PathEntry(0, -30, 1,70);
		PathEntry *p6 = new PathEntry(40, 0, 0, 70);

		PathEntry *p2 = new PathEntry(10,105,0,50);
		PathEntry *p3 = new PathEntry(0, 0,0,0);
		path.push_back(*p1);
		path.push_back(*p4);
		path.push_back(*p5);
		path.push_back(*p6);
		path.push_back(*p2);
		path.push_back(*p3);

		

		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());
		
		path.clear();
		path.push_back(*p1);
		
		
		

		
		
		//sprite->Move(50, 75);
		


	}
	void moveDownLeft() {
		currRow++;
		//sprite->Move(-50, 75);
		
		PathEntry *p1 = new PathEntry(0, 0, 2, 70);
		
		PathEntry *p4 = new PathEntry(0,0, 3,70);
		PathEntry *p5 = new PathEntry(0, -30, 3,70);
		PathEntry *p6 = new PathEntry(-40, 0, 2, 70);

		PathEntry *p2 = new PathEntry(-10,105,2,50);
		PathEntry *p3 = new PathEntry(0, 0,2,0);
		path.push_back(*p1);
		path.push_back(*p4);
		path.push_back(*p5);
		path.push_back(*p6);
		path.push_back(*p2);
		path.push_back(*p3);

		

		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());
		
		path.clear();
		path.push_back(*p1);
		
		
		
	}
	void moveUpRight() {
		currRow--;
		//sprite->Move(50, -75);
		PathEntry *p1 = new PathEntry(0, 0, 0, 70);

		PathEntry *p4 = new PathEntry(0, 0, 1, 70);
		PathEntry *p5 = new PathEntry(0, -20, 1, 70);
		PathEntry *p6 = new PathEntry(0,-50, 1, 70);

		PathEntry *p2 = new PathEntry(50, -5, 0, 50);
		PathEntry *p3 = new PathEntry(0, 0, 0, 0);
		path.push_back(*p1);
		path.push_back(*p4);
		path.push_back(*p5);
		path.push_back(*p6);
		path.push_back(*p2);
		path.push_back(*p3);



		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());

		path.clear();
		path.push_back(*p1);





	}
	void moveUpLeft() {
		currRow--;
		currCol--;
		//sprite->Move(-50, -75);
		PathEntry *p1 = new PathEntry(0, 0, 2, 70);

		PathEntry *p4 = new PathEntry(0, 0, 3, 70);
		PathEntry *p5 = new PathEntry(0, -20, 3, 70);
		PathEntry *p6 = new PathEntry(0, -50, 3, 70);

		PathEntry *p2 = new PathEntry(-50, -5, 2, 50);
		PathEntry *p3 = new PathEntry(0, 0, 2, 0);
		path.push_back(*p1);
		path.push_back(*p4);
		path.push_back(*p5);
		path.push_back(*p6);
		path.push_back(*p2);
		path.push_back(*p3);



		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());

		path.clear();
		path.push_back(*p1);



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

	void Animation() {   //!!!!!!!! gia test einai ayth h method
		/*std::list<PathEntry> path;
		PathEntry *p;
		for (int i = 0; i < 4; ++i) {
			p = new PathEntry(-10, 0, i, 300);
			path.push_back(*p); // oxi polu kalo pou einai pointer alla einai demo
		}

		MovingPathAnimation* qbertAnimation = new MovingPathAnimation(path, "qbert_Animation1");  
		MovingPathAnimator* qbertAnimator = new MovingPathAnimator(sprite, qbertAnimation);
		qbertAnimator->Start(game->GetGameTime());
	*/
	}

	Qbert(int x, int y){
		Create(x,y);
		currRow = 1;
		currCol = 1;
	}
};

#endif