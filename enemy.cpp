#include "enemy.h"

enemy::enemy(){
  return;
}

void enemy::moveby(int x, int y){
  positionX += x;
  positionY += y;
}

bool render(){
  return 1;
}
