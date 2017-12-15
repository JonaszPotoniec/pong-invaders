#ifndef ENEMY_H
#define ENEMY_H

class enemy{
public:
  enemy();
  void moveby(int x, int y = 0);
  bool render();
private:
  int positionX;
  int positionY;

};

#endif
