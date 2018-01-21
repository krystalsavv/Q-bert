#ifndef _AI_H_
#define _AI_H_
#include <list>
#include "Ball.h"
#include "Animation.h"



class Snake {
	Sprite *sprite;
	Sprite * SnakeSprite;
	MovingPathAnimation* Animation;
	MovingPathAnimator* Animator;
	MovingPathAnimation* SnakeAnimation;
	MovingPathAnimator* SnakeAnimator;
	int currRow;
	int currCol;
public:
	void Create(int x, int y) {
		AnimationFilm* film = GetFilmBall();
		sprite = new Sprite("SnakeBall", film, x, y, 38, 43, 20);
		AnimationFilm* film2 = GetFilmSnake();
		SnakeSprite = new Sprite("Snake", film2, 0, 0, 38, 50, 20);  //  den to vazw sthn sprite list  -- prepei na allaksw kai position
		spriteList.Insert(sprite);
	}

	void SetFrame(unsigned FrameNo) {
		sprite->SetFrame(FrameNo);
	}
	void SetBallX(int x) {
		sprite->SetX(x);
	}
	void SetBallY(int y) {
		sprite->SetY(y);
	}
	void SetFilmSnake() {
		sprite->SetFilm(GetFilmSnake());
	}
	void SetFilmBall() {
		sprite->SetFilm(GetFilmBall());
	}
	void SetAnimation(MovingPathAnimation* a) {
		Animation = a;
	}
	void SetAnimator(MovingPathAnimator* a) {
		Animator = a;
	}
	void SetSnakeAnimation(MovingPathAnimation* a) {
		SnakeAnimation = a;
	}
	void SetSnakeAnimator(MovingPathAnimator* a) {
		SnakeAnimator = a;
	}

	void SetRow(int row) {
		currRow = row;
	}
	void SetCol(int col) {
		currCol = col;
	}

	Sprite* GetSprite() {
		return sprite;
	}
	Sprite * GetSnakeSprite() {
		return SnakeSprite;
	}
	MovingPathAnimation * GetAnimation() {
		return Animation;
	}
	MovingPathAnimator* GetAnimator() {
		return Animator;
	}
	MovingPathAnimation * GetSnakeAnimation() {
		return SnakeAnimation;
	}
	MovingPathAnimator* GetSnakeAnimator() {
		return SnakeAnimator;
	}

	void SnakeAI() {
		int qbertRow = game->qbert->GetCurrRow();
		int qbertCol = game->qbert->GetCurrCol();
		list<PathEntry> path;
		//poso x thelw na kounhsei,poso y,poio sprite na paei kai 1000 poso na meinei sthn othonh
		PathEntry *p = new PathEntry(0, 0, 5, 1000); // panta prwta to cuurPosition
		path.push_back(*p);
		/*		p = new PathEntry(50, -74, 1, 1000);
				path.push_back(*p);
				SnakeAnimation->SetPath(path);
				*/
				// na dw poia prepei na einai h arxikh timh gia currCol/Row

		// ananewnw kai ta currCol/row se ola
		std::cout << currRow;
		std::cout << "\n" << currCol << "\n";
		std::cout << qbertRow;
		std::cout << "\n" << qbertCol << "\n";
		if (currRow >= qbertRow) {
			if (currCol <= qbertCol) {
				//pathUpRight(&path);
				p = new PathEntry(50, -74, 1, 1000);
				path.push_back(*p);
				currRow--;
			}
			else {
				//pathUpLeft(&path);
				p = new PathEntry(-50, -74, 1, 1000);
				path.push_back(*p);
				currRow--;
				currCol--;
			}
		}
		if(currRow < qbertRow) {
			if (currCol >= qbertCol) {
				//pathDownRight(&path);
				p = new PathEntry(-50, 74, 1, 1000);
				path.push_back(*p);
				currRow++;
			}
			else {
				//pathDownLeft(&path);
				p = new PathEntry(50, 74, 1, 1000);
				path.push_back(*p);
				currRow++;
				currCol++;
			}
		}
		SnakeAnimation->SetPath(path);
	}


	void pathUpRight(list<PathEntry>* path) {}
	void pathUpLeft(list<PathEntry>* path) {}
	void pathDownLeft(list<PathEntry>* path) {}
	void pathDownRignt(list<PathEntry>* path) {}


	void Destroy() {} 

	AnimationFilm* GetFilmSnake() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("snake");
		if (film == nullptr) {
			SDL_Rect rect;
			rect.x = 0;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			vector<SDL_Rect> boxes;
			boxes.push_back(rect);
			rect.x = 14;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 30;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 44;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 60;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 74;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			rect.x = 90;
			rect.y = 0;
			rect.h = 32;
			rect.w = 14;
			boxes.push_back(rect);
			rect.x = 104;
			rect.y = 0;
			rect.h = 32;
			rect.w = 16;
			boxes.push_back(rect);
			string id = "snake";
			AnimationFilmHolder::Get().Load(id, "Sprites/SnakeFilm.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("snake");
		}
		return film;
	}

	AnimationFilm* GetFilmBall() {
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

	void Reset() {
		currRow = 8; // na dw poia prpei na einai h arxikh timh
		currCol = 8; //
	}

	Snake( int x, int y) {
		Create( x, y);
		SetFrame(4);
		Animation = nullptr;
		Animator = nullptr;
		currRow = 8;
		currCol = 8;
	}
};


class BallAnim {
	Ball* ball;
	MovingPathAnimation* BallAnimation;
	MovingPathAnimator* BallAnimator;

public:
	Ball * GetBall() {
		return ball;
	}
	MovingPathAnimation* GetBallAnimation() {
		return BallAnimation;
	}
	MovingPathAnimator* GetBallAnimator() {
		return BallAnimator;
	}
	BallAnim(Ball* ball, MovingPathAnimation* BallAnimation, MovingPathAnimator* BallAnimator) {
		this->ball = ball;
		this->BallAnimation = BallAnimation;
		this->BallAnimator = BallAnimator;
	}
};

class AI {
	list<BallAnim*> Balls;  
	Snake *snake;
	unsigned delay = 3700; 
	unsigned long lastTime;
	static int sum;

public:
	void logic(unsigned long currTime) {
		srand(time(0));

		if (snake && snake->GetAnimator()->GetState() == ANIMATOR_FINISHED && snake->GetSnakeAnimator()->GetState() == ANIMATOR_READY) { // ksekinaei to fidi
			snake->GetSnakeSprite()->GetDestinationRect().x = snake->GetSprite()->GetDestinationRect().x;
			snake->GetSnakeSprite()->GetDestinationRect().y = snake->GetSprite()->GetDestinationRect().y;
			spriteList.Insert(snake->GetSnakeSprite());
			spriteList.Remove(snake->GetSprite());
			//snake->SetRow(7);
			//snake->SetCol(); 
			snake->GetSnakeAnimator()->Start(game->GetGameTime());
		}
		else if (snake && snake->GetAnimator()->GetState() == ANIMATOR_FINISHED && snake->GetSnakeAnimator()->GetState() == ANIMATOR_FINISHED) { // AI for snake
			snake->SnakeAI();
			snake->GetSnakeAnimator()->Start(game->GetGameTime());
			// tha to kanw ayto gia na ksexwrizw tis periptwseis
			// tha ANIMATOR_READY to sprite ths ball otan rip to snake
			// alliws tha to exw ANIMATOR_FINISHED opote tote to snake zei kai ananewnei path gia na "piasei" ton qbert
			//snake->GetAnimator()->SetState(ANIMATOR_READY);
		}

		while (currTime > lastTime && currTime - lastTime >= delay && (BallsWithState(ANIMATOR_RUNNING)+ BallsWithState(ANIMATOR_READY)) < 3 ){
			int col = rand() % 2 + 1;
			BallAnim* ballAnim = nullptr;
			
			

			if (!snake) {
				snake = new Snake(330 + ((col - 1) * 100), 0);
				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 5, 0);  // current position
				path.push_back(*p);
				for (int i = 0; i < 4; ++i) {
					p = new PathEntry(0, 28, 5, 70);
					path.push_back(*p);
				}
				p = new PathEntry(0, 28, 4, 70);
				path.push_back(*p);

				for (int i = 0; i < 5; ++i) {
					if (rand() % 2) {				// aristera
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(-40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(-10, 105,5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
					}
					else {							
						PathEntry *p1 = new PathEntry(0, 0, 5, 150);
						PathEntry *p4 = new PathEntry(0, 0, 5, 150);
						PathEntry *p5 = new PathEntry(0, -30, 5, 150);
						PathEntry *p6 = new PathEntry(40, 0, 5, 150);
						PathEntry *p2 = new PathEntry(10, 105, 5, 150);
						PathEntry *p3 = new PathEntry(0, 0, 4, 500);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						path.push_back(*p3);
					}
				}

				p = new PathEntry(-4, 0, 4, 200);
				for (int i = 0; i < 5; ++i) {
					p = new PathEntry(-8, 0, 4, 200);
					path.push_back(*p);
					p = new PathEntry(8, 0, 4, 200);
					path.push_back(*p);
				}
				p = new PathEntry(-4, 0, 4, 200);
				path.push_back(*p);

				MovingPathAnimation* SnakeBallAnimation = new MovingPathAnimation(path, "Snake1");
				MovingPathAnimator* SnakeBallAnimator = new MovingPathAnimator(snake->GetSprite(), SnakeBallAnimation);
				snake->SetAnimation(SnakeBallAnimation);
				snake->SetAnimator(SnakeBallAnimator);
				snake->GetAnimator()->Start(game->GetGameTime());


				list<PathEntry> path2;
				PathEntry *p2;
				p2 = new PathEntry(0, 0, 4, 500);
				path2.push_back(*p2);
				p2 = new PathEntry(0, 0, 5, 500);
				path2.push_back(*p2);

				MovingPathAnimation* SnakeAnimation = new MovingPathAnimation(path2, "Snake2");
				MovingPathAnimator* SnakeAnimator = new MovingPathAnimator(snake->GetSnakeSprite(), SnakeAnimation);
				snake->SetSnakeAnimation(SnakeAnimation);
				snake->SetSnakeAnimator(SnakeAnimator);
			}
			else if (snake->GetAnimator()->GetState() == ANIMATOR_READY && snake->GetSnakeAnimator()->GetState() == ANIMATOR_FINISHED) {
				snake->Reset();
				snake->GetSnakeAnimator()->SetState(ANIMATOR_READY);
			}
			else if (snake->GetAnimator()->GetState() == ANIMATOR_READY) { // an kathysterei poly ta kanw ena me to apopanw
				spriteList.Insert(snake->GetSprite());
				spriteList.Remove(snake->GetSnakeSprite());
				snake->SetBallX(330 + ((col - 1) * 100));
				snake->SetBallY(0);
				snake->GetAnimator()->Start(game->GetGameTime());
			}
			else if (BallsWithState(ANIMATOR_FINISHED)) {    // + BallsWithState(ANIMATOR_STOPPED)
				for (auto i = Balls.begin(); i != Balls.end(); ++i) {
					if ((*i)->GetBallAnimator()->GetState() == ANIMATOR_FINISHED) {
						ballAnim = (*i);
						ballAnim->GetBallAnimator()->SetState(ANIMATOR_READY);
						ballAnim->GetBall()->SetX(330 +((col - 1) * 100));
						ballAnim->GetBall()->SetY(0);
						ballAnim->GetBallAnimator()->Start(game->GetGameTime());
						break;
					}
				}
				assert(ballAnim);
			}
			else {
				Ball* ball = new Ball("Ball" + to_string(sum), 330 + ((col - 1) * 100), 0);

				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 1, 0);  // current position
				path.push_back(*p);
				for (int i = 0; i < 4; ++i) {
					p = new PathEntry(0, 28, 1, 70);
					path.push_back(*p);
				}
				p = new PathEntry(0, 28, 0, 70);
				path.push_back(*p);

				for (int i = 0; i < 6; ++i) {
					if (rand() % 2) {				// aristera
						//p = new PathEntry(-50, 74, 1, 1000);
						PathEntry *p1 = new PathEntry(0, 0, 1, 150);
						PathEntry *p4 = new PathEntry(0, 0, 1, 150);
						PathEntry *p5 = new PathEntry(0, -30, 1, 150);
						PathEntry *p6 = new PathEntry(-40, 0, 1, 150);
						PathEntry *p2 = new PathEntry(-10, 105, 1, 150);
						PathEntry *p3 = new PathEntry(0, 0, 0, 500);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						if (i == 5) break;
						path.push_back(*p3);
					}
					else {							//deksia
						//p = new PathEntry(50, 74, 1, 1000);
						// thelei kai endiamesa gia na kanei omala to jump
						//path.push_back(*p);
						PathEntry *p1 = new PathEntry(0, 0, 1, 150);
						PathEntry *p4 = new PathEntry(0, 0, 1, 150);
						PathEntry *p5 = new PathEntry(0, -30, 1, 150);
						PathEntry *p6 = new PathEntry(40, 0, 1, 150);
						PathEntry *p2 = new PathEntry(10, 105, 1, 150);
						PathEntry *p3 = new PathEntry(0, 0, 0, 500);
						path.push_back(*p1);
						path.push_back(*p4);
						path.push_back(*p5);
						path.push_back(*p6);
						path.push_back(*p2);
						if (i == 5) break;
						path.push_back(*p3);
					}
				}
				for (int i = 0; i < 10; ++i) {
					p = new PathEntry(0, 25, 1, 70);
					path.push_back(*p);
				}

				MovingPathAnimation* BallAnimation = new MovingPathAnimation(path, "Ball" + to_string(sum));
				MovingPathAnimator* BallAnimator = new MovingPathAnimator(ball->GetSprite(), BallAnimation);
				ballAnim = new BallAnim(ball, BallAnimation, BallAnimator);
				Balls.push_back(ballAnim);
				ballAnim->GetBallAnimator()->Start(game->GetGameTime());
				sum++;
			}

			lastTime += delay;
		}
	}

	int BallsWithState(animatorstate_t state) {
		int count = 0;
		for (auto i = Balls.begin(); i != Balls.end(); ++i) {
			if ((*i)->GetBallAnimator()->GetState() == state) ++count;
		}
		return count;
	}

	AI(unsigned long t) {
		snake = nullptr;
		lastTime = t;
	}
};


#endif