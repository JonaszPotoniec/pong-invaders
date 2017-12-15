#include "pong.h"
#include <SDL2/SDL.h>

pong::pong(int resY){
  positionY = resY-sizeY-10;
}


bool pong::render(SDL_Renderer* ff){
  SDL_Rect fillRect = {positionX, positionY, sizeX, 15};
  SDL_SetRenderDrawColor(ff, 0x30, 0x30, 0x30, 0xFF);
  SDL_RenderFillRect(ff, &fillRect);
  return 0;
}

//pongPos = x, y, width
int* pong::getPos(){
  pongPos[0] = positionX;
  pongPos[1] = positionY;
  pongPos[2] = sizeX;
  return pongPos;
}

void pong::move(){
   int x, y;
   SDL_GetMouseState( &x, &y );
   positionX = x;
}
