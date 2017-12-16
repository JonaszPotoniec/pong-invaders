#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

class enemy{
public:
  enemy();
  void moveBy(int x, int y = 0);
  void setPosition(int x, int y);
  void setTexture(SDL_Texture* newTexture);
  bool render(SDL_Renderer* windowRenderer);
  bool isAlive();
  int getPositionX();
  int getPositionY();
  int getSizeX();
  int getSizeY();
private:
  int positionX;
  int positionY;
  int sizeX = 75;
  int sizeY = 50;
  bool alive = 1;
  SDL_Texture* texture;
};

#endif
