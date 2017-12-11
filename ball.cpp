#include "ball.h"

ball::ball(int resX, int resY){
  positionX = resX/2;
  positionY = resY/2;
}

//pong Pos = x, y, width
void ball::move(int* pongPos, int resX){
  if(directionX){
    if(positionX <= resX){
      positionX += accelerationX;
    }else{
      accelerationX *= -1;
      directionX = false;
    }
  }else{
    if(positionX >= 0){
      positionX += accelerationX;
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

  positionY += accelerationY;
}

bool ball::render(){
  return 0;
}
