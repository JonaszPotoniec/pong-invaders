#include "pong.h"

pong::pong(int resY){
  positionY = resY-sizeY-10;
}


bool pong::render(){
  return 0;
}

//pongPos = x, y, width
int* pong::getPos(){
  return pongPos;
}
