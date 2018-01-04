#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <SDL.h>
#include <iostream>
#include <map>
#include <assert.h>
#include <vector>
#include "Game.h"

using namespace std;

typedef SDL_Texture* Bitmap;
typedef SDL_Rect Rect;

class AnimationFilm;
class AnimationFilmHolder;
class BitmapLoader;


class AnimationFilm {
	vector<SDL_Rect> boxes; //SDL_Rect sourceRect for each frame
	SDL_Texture* bitmap; // to film
	string id;
public:
	int GetTotalFrames() {
		return boxes.size();
	}

	const string GetId(void) const {
		return id;
	}
	SDL_Texture* GetBitmap() {
		return bitmap;
	}

	const SDL_Rect GetFrameBox(unsigned frameNo) const {
		assert(frameNo < boxes.size());
		return boxes[frameNo];
	}

	void DisplayFrame(const int x, const int y, SDL_Rect& sousceRect, SDL_Rect& destRect, unsigned frameNo) const { //x , y -->at
		sousceRect = boxes[frameNo];
		SDL_QueryTexture(this->bitmap, NULL, NULL, &sousceRect.w, &sousceRect.h);
		sousceRect.x = 0;
		sousceRect.y = 0;
		destRect.x = x;
		destRect.y = y;
		destRect.w = 70;
		destRect.h = 70;

	}

	AnimationFilm(SDL_Texture* bitmap, const vector<SDL_Rect> boxes, string& id) {
		this->bitmap = bitmap;
		this->boxes = boxes;
		this->id = id;
	}

};


class BitmapLoader {
	typedef map<string, SDL_Texture*> Bitmaps;
	Bitmaps bitmaps;

	SDL_Texture* GetBitmap(const string path) {
		Bitmaps::const_iterator i = bitmaps.find(path);
		return i != bitmaps.end() ? i->second : nullptr;
	}

	SDL_Texture*  LoadBitmap(const char *path) {
		SDL_Surface* TempSurface = SDL_LoadBMP(path);
		SDL_Texture* Texture = SDL_CreateTextureFromSurface(game->GetRenderer(), TempSurface);
		SDL_FreeSurface(TempSurface);
		return Texture;
	}

	void DestroyBitmap(SDL_Texture* bitmap) {
		///// elena prepei na kanei kati sto telos gia destroe twn texture??
	}

public:
	SDL_Texture * Load(const char *path) {
		SDL_Texture* b = GetBitmap(path);
		if (!b) {
			b = LoadBitmap(path);
			bitmaps[path] = b;
			assert(b);
		}
		return b;
	}

	void CleanUp() {
		for (Bitmaps::iterator i = bitmaps.begin(); i != bitmaps.end(); ++i) {
			DestroyBitmap(i->second);
		}
		bitmaps.clear();
	}

	BitmapLoader() {}
	~BitmapLoader() { CleanUp(); }
};





class AnimationFilmHolder {
	typedef map<string, AnimationFilm*> Films;
	Films films;
	BitmapLoader bitmaps; // for loading 
	static AnimationFilmHolder holder; // singleton

	AnimationFilmHolder() {};
	~AnimationFilmHolder() { CleanUp(); };

public:
	static AnimationFilmHolder& Get() {
		return holder;
	}

	void Load(string& id, const char * path, vector<SDL_Rect> boxes) {
		SDL_Texture* bmp = bitmaps.Load(path);
		assert(!GetFilm(id));
		films[id] = new AnimationFilm(bmp, boxes, id);
	}

	void CleanUp() {
		for (Films::iterator i = films.begin(); i != films.end(); ++i) {
			delete(i->second); 
		}
		films.clear();
	}

	AnimationFilm* GetFilm(const string id) const {
		Films::const_iterator i = films.find(id);
		return i != films.end() ? i->second : nullptr;
	}
};






class Sprite {
	unsigned frameNo; // se pio frame ftanw apo to Animation film
	SDL_Rect destinationRect;
	SDL_Rect sourceRect; // framebox
	AnimationFilm *currFilm;
	string id;
	unsigned zOrder;
	bool isVisible;

public:
	void SetFrame(int i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameNo = i;
			sourceRect = currFilm->GetFrameBox(i);
		}
	}
	void SetVisibility(bool v) {
		isVisible = v;
	}

	unsigned GetFrame(void) const {
		return frameNo;
	}
	SDL_Rect GetDestinationRect() {
		return destinationRect;
	}
	SDL_Rect GetSourceRect() {
		return sourceRect;
	}
	AnimationFilm *GetCurrFilm() {
		return currFilm;
	}
	bool IsVisible(void) const {
		return isVisible;
	}

	//virtual bool CollisionCheck(Sprite* s); // TO DO!!!

	Sprite(const char *id, AnimationFilm* film, int x, int y, int w, int h, unsigned zorder) {
		id = id;
		destinationRect.x = x;	// pou na mpei sto window
		destinationRect.y = y;
		destinationRect.w = w;
		destinationRect.h = h;
		isVisible = true;
		currFilm = film;
		zOrder = zorder;
		SetFrame(0);
	}

	void Display(const int x, const int y) {
		currFilm->DisplayFrame(x, y, sourceRect, destinationRect, frameNo);
		SDL_RenderCopy(game->GetRenderer(), this->currFilm->GetBitmap(), &sourceRect, &destinationRect);
	}
};

#endif
