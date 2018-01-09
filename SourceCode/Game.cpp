#include "Game.h"
#include "Sprites.h"
#include "Terrain.h"

Game::Game(){
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	m_bRunning = true;
}

Game::~Game(){}

bool Game::init(const char * title, int xpos, int ypos, int width, int height, int flags){
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow == nullptr) {

			std::cout << "SDL Error: Failed to create window: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		if (m_pRenderer == nullptr) {
			std::cout << "SDL Error: Failed to create renderer: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_pWindow);
			SDL_Quit();
			return false;
		}
	}
	else {
		std::cout << "SDL Error: Failed to initialize: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Game::render() {
	SDL_RenderClear(m_pRenderer);
	spriteList.Display();
	SDL_RenderPresent(m_pRenderer); 
}

void Game::handleEvents(int row, int col) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
			{
				cout << "Up arrow pressed" << endl;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				cout << "Down arrow pressed" << endl;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				cout << "Right arrow pressed" << endl;
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				cout << "Left arrow pressed" << endl;
			}
			break;

		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}


void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
	return m_pRenderer;
}



//gia thn SpriteList (einai ligo akyrh edw alla den exw allo cpp arxeio na thn balw)
//sort apo to mikrotero zOrder sto megalytero
bool compare(Sprite* s1, Sprite* s2) {
	return s1->GetzOrder() < s2->GetzOrder();
}