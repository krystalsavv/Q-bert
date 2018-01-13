#ifndef _AI_H_
#define _AI_H_
#include <list>
#include "Ball.h"
#include "Animation.h"

class Snace {
	Sprite *sprite;
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
	Snace *snace;
	unsigned delay = 3700; 
	unsigned long lastTime;
	static int sum;

public:
	void logic(unsigned long currTime) {
		srand(time(0));
		while (currTime > lastTime && currTime - lastTime >= delay && (BallsWithState(ANIMATOR_RUNNING)+ BallsWithState(ANIMATOR_READY)) < 3 ){
			int col = rand() % 2 + 1;
			BallAnim* ballAnim = nullptr;
			if (BallsWithState(ANIMATOR_FINISHED)) {    // + BallsWithState(ANIMATOR_STOPPED)
				for (auto i = Balls.begin(); i != Balls.end(); ++i) {
					if ((*i)->GetBallAnimator()->GetState() == ANIMATOR_FINISHED) {
						ballAnim = (*i);
						ballAnim->GetBallAnimator()->SetState(ANIMATOR_READY);
						ballAnim->GetBall()->SetX(330 +((col - 1) * 100));
						ballAnim->GetBall()->SetY(140);
						break;
					}
				}
				assert(ballAnim);
			}
			else {
				Ball* ball = new Ball("Ball" + to_string(sum), 330 + ((col - 1) * 100), 140);


				list<PathEntry> path;
				PathEntry *p;
				p = new PathEntry(0, 0, 1, 1000);  // current position
				path.push_back(*p);
				for (int i = 0; i < 5; ++i) {
					if (rand() % 2)
						p = new PathEntry(-50, 74, 1, 1000);  //  x +/- 50, y + 74;
					else
						p = new PathEntry(50, 74, 1, 1000);

					// thelei kai endiamesa gia na kanei omala to jump

					path.push_back(*p);
				}

				for (int i = 0; i < 30; ++i) {
					p = new PathEntry(0, 10, 1, 70);
					path.push_back(*p);
				}
				MovingPathAnimation* BallAnimation = new MovingPathAnimation(path, "Ball" + to_string(sum));
				MovingPathAnimator* BallAnimator = new MovingPathAnimator(ball->GetSprite(), BallAnimation);
				ballAnim = new BallAnim(ball, BallAnimation, BallAnimator);
				Balls.push_back(ballAnim);
			}
			ballAnim->GetBallAnimator()->Start(game->GetGameTime());
			sum++;
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
		snace = nullptr;
		lastTime = t;
	}
};


#endif
