#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <SDL.h>
#include <ctime>

using namespace std;

class Qbert;
class IsometricPyramid;
class Disk;

class Game {
	unsigned long currTime = 0;
	IsometricPyramid *terrain;
	Qbert *qbert;
	Disk *diskLeft;
	Disk *diskRight;
public:
	Game();
	~Game();
	// simply set the running variable to true  
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	void SetSprite(	IsometricPyramid *terrain,
					Qbert *qbert,
					Disk *diskLeft,
					Disk *diskRight);
	void SetGameTime();
	unsigned long GetGameTime();
	// a function to access the private running variable   
	bool running() { return m_bRunning; }
	SDL_Renderer* GetRenderer();
private:
	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};

extern Game* game;

#endif
