#ifndef PONG_H
#define PONG_H

class pong{

public:
  pong(int resY);
  bool render();
  int* getPos();

private:
  int sizeY = 15;
  int sizeX = 80;
  int position = 400;
  int positionY;
  int pongPos[3] = {position, positionY, sizeX}; //pongPos = x, y, width
};

#endif
