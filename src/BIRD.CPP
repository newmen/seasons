#include "pointh.cpp"

#ifndef MY_BIRD_H
#define MY_BIRD_H

class Bird : public PointObj
{
 public:
  Bird() : PointObj(0, 0, 30.0) { }

  Bird(const Point* a, const double& size) : PointObj(a, size) { }

  Bird(const int& x, const int& y, const double& size) :
   PointObj(x, y, size) { }

  void Draw(const int& color); //const;
};

void Bird::Draw(const int& color) //const
{
  double angle = M_PI_2*((double)(random(60)+15)/90+1);
  Point a(this, size/2, angle);

  angle = M_PI_2*((double)random(20)/90+0.777);
  Point b(this, size/8, angle);

  angle = M_PI_2*(double)(random(60)+15)/90;
  Point c(this, size/2, angle);

  setcolor(color);
  setfillstyle(1, color);

  int mass[8];

  mass[0] = x;
  mass[1] = y;
  mass[2] = a.GetX();
  mass[3] = a.GetY();
  mass[4] = b.GetX();
  mass[5] = b.GetY();
  mass[6] = c.GetX();
  mass[7] = c.GetY();

  fillpoly(4, mass);
}

#endif

/*
int main()
{
  int gdriver = VGA, gmode = VGAHI;
  initgraph(&gdriver, &gmode, "D:\\TC\\BGI");

  randomize();


  Bird b(100,100,40);

  do
  {
    cleardevice();
    b.Draw(8);
  }
  while(getch() != 27);

  closegraph();

  return 1;
}
*/