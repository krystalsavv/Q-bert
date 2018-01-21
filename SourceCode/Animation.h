#ifndef _ANIMATION_
#define _ANIMATION_ 
#include "Sprites.h"

class Animator;
void AnimatorHolder_Register(Animator* a);
void AnimatorHolder_Cancel(Animator* a);
void AnimatorHolder_MarkAsRunning(Animator* a);
void AnimatorHolder_MarkAsSuspended(Animator* a);


class Animation {
	//unsigned id;
	string id;
public:
	string GetId(void) {
		return id; 
	}

	virtual Animation* Clone(string newId) const = 0;
	virtual Animation* Clone(char * newId) const = 0;
	
	Animation(string _id) : id(_id) {}
	Animation(char* _id) : id(_id) {}
	virtual ~Animation() {}
};



struct PathEntry {
	int dx, dy;  //offset
	unsigned frame;
	unsigned delay;

	PathEntry(void) : dx(0), dy(0), frame(0xff), delay(0) {}
	PathEntry(const PathEntry& p) :
		dx(p.dx), dy(p.dy), frame(p.frame), delay(p.delay) {}
	PathEntry(int _dx, int _dy, int _frame, int _delay) :
		dx(_dx), dy(_dy), frame(_frame), delay(_delay) {}
};

class MovingPathAnimation : public Animation {
	list<PathEntry> path;
public:
	const list<PathEntry>& GetPath(void) const{
		return path;
	}
	void SetPath(const list<PathEntry>& p){
		path.clear();
		path = p;
	}

	PathEntry* GetStartPathFrame() {
		assert(!path.empty());
		return &(path.front());
	}
	PathEntry* GetEndPathFrame() {
		assert(!path.empty());
		return &(path.back());
	}
	PathEntry* GetNextPathFrame(PathEntry* curr) {
		int flag = 0;
		for (auto i = path.begin(); i != path.end(); ++i) {
			if (flag == 1)
				return &*i;
			if (curr ==  &*i)
				flag = 1;
		}
		return nullptr;
		//return &(path.back());
	}

	Animation* Clone(string newId) const{
		return new MovingPathAnimation(path, newId);
	}
	Animation* Clone(char * newId) const {
		return new MovingPathAnimation(path, newId);
	}
	MovingPathAnimation(const std::list<PathEntry>& path, char * id) : Animation(id) {
		this->path.assign(path.begin(), path.end());
	}

	MovingPathAnimation(const std::list<PathEntry>& path, string id) : Animation(id) {
		this->path.assign(path.begin(), path.end());
	}
};



enum animatorstate_t {
	ANIMATOR_FINISHED = 0,
	ANIMATOR_RUNNING = 1,
	ANIMATOR_STOPPED = 2,
	ANIMATOR_READY = 3
};

class Animator {
public:
	typedef void(*FinishCallback)(Animator*, void*);
protected:
	unsigned long lastTime; 
	animatorstate_t state;
	FinishCallback onFinish;
	void* finishClosure;
	void NotifyStopped(void) {
		if (onFinish)
			(*onFinish)(this, finishClosure);
	}
public:
	void SetState(animatorstate_t s) {
		state = s;
	}
	animatorstate_t GetState() {
		return state;
	}

	void Stop(void) {
		if (!HasFinished()) {
			state = ANIMATOR_STOPPED;
			NotifyStopped();
		}

	}

	bool HasFinished(void) const	{
		return state != ANIMATOR_RUNNING;
	}

	virtual void TimeShift(unsigned long offset) {
		lastTime += offset;
	}

	virtual bool Progress(unsigned long currTime) = 0;

	void SetOnFinish(FinishCallback f, void* c = nullptr){
		onFinish = f, finishClosure = c;
	}

	Animator() {
		lastTime = 0;
		state = ANIMATOR_READY;
		SetOnFinish(nullptr,nullptr);
	}
	virtual ~Animator() {};
};



class MovingPathAnimator : public Animator {
	Sprite*	sprite;
	MovingPathAnimation* anim;
	PathEntry *currPathFrame; 
	bool cont;
public:
	void SetCont(bool c) {
		cont = c;
	}

	bool Progress(unsigned long currTime) {
		assert(currPathFrame);
		assert(anim);
		assert(sprite);
		while (currTime > lastTime && currTime - lastTime >= currPathFrame->delay) {
			currPathFrame = anim->GetNextPathFrame(currPathFrame);
			assert(currPathFrame);															 //NULL an den yparxei 
			sprite->Move(currPathFrame->dx, currPathFrame->dy);
			sprite->SetFrame(currPathFrame->frame);
			lastTime += currPathFrame->delay;

			if (currPathFrame == anim->GetEndPathFrame()) {
				if (cont)
					currPathFrame = anim->GetStartPathFrame();
				else {
					state = ANIMATOR_FINISHED;
					NotifyStopped();
					return true;
				}
			}
		}
		return false;
	}

	void Start(Sprite* s, MovingPathAnimation* a, unsigned long t) {
		assert(s);
		assert(a);
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currPathFrame = anim->GetStartPathFrame();
		sprite->SetFrame(currPathFrame->frame); // pairnei to 1o frame tou animation
		AnimatorHolder_MarkAsRunning(this);
	}

	void Start(unsigned long t) {
		assert(sprite);
		assert(anim);
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currPathFrame = anim->GetStartPathFrame();
		sprite->SetFrame(currPathFrame->frame); // pairnei to 1o frame tou animation
		AnimatorHolder_MarkAsRunning(this);
	}

	MovingPathAnimator() {   
		sprite = nullptr;
		anim = nullptr;
		currPathFrame = nullptr;
		cont = false;
		AnimatorHolder_Register(this); 
	}

	MovingPathAnimator(Sprite* s, MovingPathAnimation* a) {
		sprite = s;
		anim = a;
		currPathFrame = nullptr;
		cont = false;
		AnimatorHolder_Register(this);
	}
	~MovingPathAnimator() {}
};



class AnimatorHolder {
	static list<Animator*> running;
	static list<Animator*>  suspended;
	static AnimatorHolder animatorHolder; // singleton

	AnimatorHolder() {};
	~AnimatorHolder() {};
public:
	static AnimatorHolder&  Get() {
		return animatorHolder;
	}

	static void Register(Animator* a) {
		suspended.push_back(a);
	}
	static void Cancel(Animator* a) {
		suspended.remove(a);
	}
	static void MarkAsRunning(Animator* a) {
		suspended.remove(a);
		running.push_back(a);
	}
	static void MarkAsSuspended(Animator* a) {
		running.remove(a);
		suspended.push_back(a);
	}

	static void Progress(unsigned long currTime) {
		auto i = running.begin();
		while (!running.empty() && i != running.end()) {
			bool remove = (*i)->Progress(currTime);
			auto prev = i;
			++i;
			if (remove) {
				MarkAsSuspended(*prev);
			}
		}
	}
};

#endif
