#ifndef BALL_H
#define BALL_H

class ball{

public:
  ball(int resX, int resY);
  void move(int* pongPos, int resX);
  bool render();

private:
  int positionX;
  int positionY;
  int diameter = 10;
  double accelerationX = 10;
  double accelerationY = 5;
  bool directionX = true;
  bool directionY = true;
};

#endif
