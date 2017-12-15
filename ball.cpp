#include "ball.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

ball::ball(int resX, int resY, SDL_Renderer* windowRenderer){
  positionX = resX/2;
  positionY = resY/2;
  ballTexture = loadTexture(windowRenderer);
}

//pong Pos = x, y, width
void ball::move(int* pongPos, int resX, int deltaTime){
  if(directionX){
    if(positionX <= resX){
      positionX += accelerationX * deltaTime;
    }else{
      accelerationX *= -1;
      directionX = false;
    }
  }else{
    if(positionX >= 0){
      positionX += accelerationX * deltaTime;
    }else{
      accelerationX *= -1;
      directionX = true;
    }
  }

  if(positionY > pongPos[1] && directionY){
    if(positionX > pongPos[0] && positionX > (pongPos[0] + pongPos[3])){
      directionY = false;
      accelerationY *= -1;
    }
  }

  if(positionY <= 0 && !directionY){
    directionY = true;
    accelerationY *= -1;
  }

  positionY += accelerationY * deltaTime;
}

bool ball::render(SDL_Renderer* windowRenderer){
  SDL_Rect* renderRect = new SDL_Rect{positionX, positionY, diameter, diameter};
  SDL_RenderCopyEx(windowRenderer, ballTexture, NULL, renderRect, rotation++, NULL, SDL_FLIP_NONE);
  return 1;
}

SDL_Texture* ball::loadTexture(SDL_Renderer* windowRenderer){
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load("media/ball.png");
  if(loadedSurface == NULL)
    printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
  else{
    newTexture = SDL_CreateTextureFromSurface(windowRenderer, loadedSurface);
      if(newTexture == NULL)
        printf("Unable to convert image to texture. SDL_Error: %s\n", SDL_GetError());
      else{
        SDL_FreeSurface(loadedSurface);
      }
  }
  return newTexture;
}
