#ifndef _TERRAIN_
#define _TERRAIN_ 

#include <SDL.h>
#include <string>
#include "Sprites.h"

class IsometricPyramid final {
	vector<CubeSprite*> sprites;
	unsigned Px;
	unsigned Py;
	unsigned totalRows;
	unsigned h1;
	unsigned h2;

	unsigned iso_cube_y(unsigned row) {
		return Py + (row - 1) * h2;
	}

	void Compute_iso_cube_placement(unsigned row, unsigned col, SDL_Rect* destRect, unsigned* ys, unsigned* xs, unsigned* yc, unsigned* xc) {
		assert(row > 0 && row <= totalRows);
		assert(col > 0 && col <= row);
		destRect->y = iso_cube_y(row);
		*ys = destRect->y;					// the top left pixel of the entire row of isocubes
		*xs = this->Px - (int)(row / 2.0 * destRect->w);
		destRect->x = *xs + (col - 1) * destRect->w;
		*xc = destRect->x + destRect->w / 2; // center
		*yc = destRect->y + h1;
	}
public:
	void Create() {
		// create all the sprites and put them in the vector 
		unsigned row = 0;
		unsigned col = 0;
		for (unsigned i = 0; i < (totalRows*(totalRows + 1)) / 2; ++i) {
			if (row == col) {
				++row;
				col = 1;
			}
			else {
				++col;
			}
			AnimationFilm* film = GetFilm();
			CubeSprite* s = new CubeSprite("cube" + to_string(i), film, 0, 0, 100, 100, 10, row, col);

			// calculate destRect.x,y and x/ys and x/yc for each one with Compute_iso_cube_placement()
			unsigned  ys, xs, yc, xc;
			Compute_iso_cube_placement(row, col, &(s->GetDestinationRect()), &ys, &xs, &yc, &xc);
			s->SetXs(xs);
			s->SetYs(ys);
			s->SetXc(xc);
			s->SetYc(yc);
			sprites.push_back(s);

			//put them in global list with all sprites sorted by zOrder
			spriteList.Insert((Sprite*)s);
		}
	}

	//void Destroy(void) {} // normally at level program end

	unsigned GetTotalWidth(void) const {
		assert(sprites.size());
		return totalRows * (sprites[0]->GetDestinationRect()).w;
	}

	unsigned GetTotalHeight(void) const {
		return totalRows * h2 + h1;
	}
	unsigned int GetTotalRows() {
		return totalRows;
	}
	void SetZOrder(unsigned zOrder) {  // check an ta allazei kai sthn list
		for (auto i = sprites.begin(); i != sprites.end(); ++i) {
			(*i)->SetZOrder(zOrder);
		}
	}

	Sprite* GetIsoCube(unsigned row, unsigned col) {
		assert(row + col - 1 >= 0);
		return sprites[row + col - 1];
	}

	AnimationFilm* GetFilm() {
		AnimationFilm* film = AnimationFilmHolder::Get().GetFilm("cubes");
		if (film == nullptr) {
			SDL_Rect rect;
			vector<SDL_Rect> boxes;
			for (int i = 0; i < 193; i += 32) {
				for (int j = 0; j < 64; j += 32) {
					rect.x = j;
					rect.y = i;
					rect.h = 32;
					rect.w = 32;
					boxes.push_back(rect);
				}
			}
			string id = "cubes";
			AnimationFilmHolder::Get().Load(id, "Sprites/cubes.bmp", boxes);
			film = AnimationFilmHolder::Get().GetFilm("cubes");
		}
		return film;
	}

	IsometricPyramid(unsigned Px, unsigned Py, unsigned totalRows, unsigned h1, unsigned h2) {
		this->Px = Px;
		this->Py = Py;
		this->totalRows = totalRows;
		this->h1 = h1;
		this->h2 = h2;
		Create();
	}
};

#endif
