#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <SDL.h>

class Game {
public:
	Game();
	~Game();
	// simply set the running variable to true  
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update() {}
	void handleEvents(int row, int col);
	void clean();
	// a function to access the private running variable   
	bool running() { return m_bRunning; }
	SDL_Renderer* GetRenderer();
private:
	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int m_currentFrame;
	bool m_bRunning;
};

extern Game* game;

#endif
