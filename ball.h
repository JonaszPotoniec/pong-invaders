#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <unistd.h>

class ball{

public:
  ball(int resX, int resY, SDL_Renderer* windowRenderer);
  void move(int* pongPos, int resX, int resY, int deltaTime);
  bool render(SDL_Renderer* windowRenderer);
  void changeDirections(bool x = 0, bool y = 0);
  int getPositionX();
  int getPositionY();

private:
  SDL_Texture* loadTexture(SDL_Renderer* windowRenderer);
  SDL_Texture* ballTexture;
  float positionX;
  float positionY;
  int diameter = 10;
  int rotation;
  float accelerationX = 0.5f;
  float accelerationY = 0.5f;
  bool directionX = true;
  bool directionY = true;
};

#endif
