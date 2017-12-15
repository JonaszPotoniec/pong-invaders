#ifndef PONG_H
#define PONG_H

#include <SDL2/SDL.h>

class pong{

public:
  pong(int resY);
  bool render(SDL_Renderer* ff);
  int* getPos();
  void move();

private:
  int sizeY = 15;
  int sizeX = 80;
  int positionX = 400;
  int positionY;
  int pongPos[3] = {positionX, positionY, sizeX}; //pongPos = x, y, width
};

#endif
