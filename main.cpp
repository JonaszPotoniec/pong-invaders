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
int enemyTicks = 0;
SDL_Texture* enemyTexture;
bool enemyDirection = 1; // 1=right 0=left
bool won = 0;

//functions
bool init();
void close();
void input();
void moveEnemies(enemy enemyo[][3]);
void killEnemies(enemy enemyo[][3], ball ballo);

int main( int argc, char* args[] ){
  run = init();

  //objects
  pong pongo(resolutionY);
  ball ballo(resolutionX, resolutionY, windowRenderer);
  enemy enemyo[10][3];

  for(int x = 0; x < 10; x++)
    for(int y = 0; y < 3; y++){
        enemyo[x][y].setTexture(enemyTexture);
        enemyo[x][y].setPosition(x * enemyo[x][y].getSizeX() * 1.3, (resolutionY/10) + (y * enemyo[x][y].getSizeY() * 1.3));
    }

  while(run){
    input(); //handle input

    //move things
    ballo.move(pongo.getPos(), resolutionX, resolutionY, SDL_GetTicks() - ticks);
    pongo.move();
    if(SDL_GetTicks() - enemyTicks > 1000){
      moveEnemies(enemyo);
      enemyTicks = SDL_GetTicks();
    }

    //logic
    killEnemies(enemyo, ballo);
    ticks = SDL_GetTicks();

    //render things
    SDL_SetRenderDrawColor( windowRenderer, 230, 235, 190, 0xFF );
    SDL_RenderClear( windowRenderer );
    ballo.render(windowRenderer);
    pongo.render(windowRenderer);
    for(int x = 0; x < 10; x++)
      for(int y = 0; y < 3; y++)
        if(enemyo[x][y].isAlive())
          enemyo[x][y].render(windowRenderer);
    SDL_RenderPresent( windowRenderer );
  }
}

void input(){
  while(SDL_PollEvent(&evnt)){
    if(evnt.type == SDL_QUIT)
      run = false;
  }
}

bool init(){
	//init everything
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
  		printf("Failed to initialize SDL, error: %s\n", SDL_GetError());
      return 0;
  }

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

  SDL_Surface* loadedSurface = IMG_Load("media/enemy.png");
  if(loadedSurface == NULL)
    printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
  else{
    enemyTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
      if(enemyTexture == NULL)
        printf("Unable to convert image to texture. SDL_Error: %s\n", SDL_GetError());
      else{
        SDL_FreeSurface(loadedSurface);
      }
  }

  return 1;
}

void close(){
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void moveEnemies(enemy enemyo[][3]){

  int skipRowes = 0;
  bool moveY = 0;

  if( !enemyDirection ){ //left
    for(int x = 0; x < 10; x++){
      int notAlive = 0;
      for(int y = 0; y < 3; y++){
          if(!enemyo[x][y].isAlive())
            notAlive++;
      }
      if(notAlive == 3)
        skipRowes++;
      else
        x = 10;

      if(
        (enemyo[0+skipRowes][0].isAlive() && enemyo[0+skipRowes][0].getPositionX() < enemyo[0+skipRowes][0].getSizeX()) ||
        (enemyo[0+skipRowes][1].isAlive() && enemyo[0+skipRowes][1].getPositionX() < enemyo[0+skipRowes][1].getSizeX()) ||
        (enemyo[0+skipRowes][2].isAlive() && enemyo[0+skipRowes][2].getPositionX() < enemyo[0+skipRowes][2].getSizeX())
        ){
          moveY = 1;
          enemyDirection = 1;
      }
    }
  }else{ //right
    for(int x = 9; x >= 0; x--){
      int notAlive = 0;
      for(int y = 0; y < 3; y++){
          if(!enemyo[x][y].isAlive())
            notAlive++;
      }
      if(notAlive == 3)
        skipRowes++;
      else
        x = -1;
    }

      if(
        (enemyo[9-skipRowes][0].isAlive() && enemyo[9-skipRowes][0].getPositionX() > resolutionX - enemyo[9-skipRowes][0].getSizeX()) ||
        (enemyo[9-skipRowes][1].isAlive() && enemyo[9-skipRowes][1].getPositionX() > resolutionX - enemyo[9-skipRowes][1].getSizeX()) ||
        (enemyo[9-skipRowes][2].isAlive() && enemyo[9-skipRowes][2].getPositionX() > resolutionX - enemyo[9-skipRowes][2].getSizeX())
        ){
          moveY = 1;
          enemyDirection = 0;
      }
  }

  if(moveY)
    for(int x = 0; x < 10; x++)
      for(int y = 0; y < 3; y++)
        enemyo[x][y].moveBy(0, enemyo[x][y].getSizeY());
  else
    if(enemyDirection)
      for(int x = 0; x < 10; x++)
        for(int y = 0; y < 3; y++)
          enemyo[x][y].moveBy(enemyo[x][y].getSizeX()/2);
    else
      for(int x = 0; x < 10; x++)
        for(int y = 0; y < 3; y++)
          enemyo[x][y].moveBy(enemyo[x][y].getSizeX()/-2);

  if(skipRowes == 10){
    run = 0;
    won = 1;
  }

  return;
}

void killEnemies(enemy enemyo[][3], ball ballo){
  for(int x = 0; x < 10; x++)
      if(ballo.getPositionX() > enemyo[x][0].getPositionX() && ballo.getPositionX() < enemyo[x][0].getPositionX() + enemyo[x][0].getSizeX())
        for(int y = 0; y < 3; y++)
          if(ballo.getPositionY() > enemyo[x][y].getPositionY() && ballo.getPositionY() < enemyo[x][y].getPositionY() + enemyo[x][y].getSizeY()){
            if(enemyo[x][y].isAlive()){
              ballo.changeDirections(1, 1);
              enemyo[x][y].kill();
            }
          }
}
