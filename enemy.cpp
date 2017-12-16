#include "enemy.h"
#include <SDL2/SDL.h>

enemy::enemy(){
  return;
}

void enemy::moveBy(int x, int y){
  positionX += x;
  positionY += y;
}

void enemy::setPosition(int x, int y){
  positionX = x;
  positionY = y;
}

void enemy::setTexture(SDL_Texture* newTexture){
  texture = newTexture;
}

bool enemy::render(SDL_Renderer* windowRenderer){
  SDL_Rect* renderRect = new SDL_Rect{positionX, positionY, sizeX, sizeY};
  SDL_RenderCopy(windowRenderer, texture, NULL, renderRect);
  return 1;
}

bool enemy::isAlive(){
  return alive;
}

int enemy::getPositionX(){
  return positionX;
}

int enemy::getPositionY(){
  return positionY;
}

int enemy::getSizeX(){
  return sizeX;
}

int enemy::getSizeY(){
  return sizeY;
}
