#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "ball.h"
#include "ball.cpp"
#include "pong.h"
#include "pong.cpp"
#include "enemy.h"
#include "enemy.cpp"

//variables
const int resolutionX = 1280;
const int resolutionY = 720;
SDL_Window* window = NULL;
SDL_Renderer* windowRenderer = NULL;
bool run = true;
SDL_Event evnt;
int ticks;

//functions
bool init();
void close();
void input();

int main( int argc, char* args[] ){
  run = init();

  //objects
  pong pongo(resolutionY);
  ball ballo(resolutionX, resolutionY, windowRenderer);

  while(run){
    input(); //handle input

    //move things
    ballo.move(pongo.getPos(), resolutionX, SDL_GetTicks() - ticks);
    pongo.move();

    ticks = SDL_GetTicks();

    //render things
    SDL_SetRenderDrawColor( windowRenderer, 230, 235, 190, 0xFF );
    SDL_RenderClear( windowRenderer );
    ballo.render(windowRenderer);
    pongo.render(windowRenderer);
    SDL_RenderPresent( windowRenderer );
  }
}

void input(){
  while(SDL_PollEvent(&evnt)){
    if(evnt.type == SDL_QUIT)
      run = false;
    else if( evnt.type == SDL_KEYDOWN )
      switch(evnt.key.keysym.sym){
        case SDLK_LEFT:
          break;
        case SDLK_RIGHT:
          break;
      }
  }
}


bool init(){
	//init everything
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
  		printf("Failed to initialize SDL, error: %s\n", SDL_GetError());
      return 0;
  }
/*                             I don't need fonts for now
	if (TTF_Init() == -1)
		printf("Failed to initialize SDL_ttf, error: %s\n", TTF_GetError());
*/
	window = SDL_CreateWindow("Pong invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolutionX, resolutionY, SDL_WINDOW_SHOWN/* | SDL_WINDOW_FULLSCREEN_DESKTOP*/);
	if (window == 0){
    printf("Failed to create window, error: %s\n", SDL_GetError());
    return 0;
  }

	windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (windowRenderer == 0){
    printf("Can't create renderer, error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}



void close(){
  SDL_DestroyWindow(window);
  SDL_Quit();
}
