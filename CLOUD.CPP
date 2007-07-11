#include "pointh.cpp"

#ifndef MY_CLOUD_H
#define MY_CLOUD_H

class Cloud : public PointObj
{
  Point sun;

  void Drawing(const Point* a, const int& r, const int& color) const;

 public:
  Cloud() : PointObj(0, 0, 200.0), sun((int)(getmaxx()*Fi), 0) { }

  Cloud(const Point* a, const Point* sun) : PointObj(a, 200.0), sun(sun) { }

  Cloud(const Point* a, const Point* sun, const int& size) :
   PointObj(a, size), sun(sun) { }

  Cloud(const int& x, const int& y, const Point* sun, const double& size) :
   PointObj(x, y, size), sun(sun) { }

  void Draw(const int& color) //const
   { Drawing(this, size/2.5, color); }
};

void Cloud::Drawing(const Point* a, const int& r, const int& color) const
{
  if(r < 2.222) return;

  setcolor(15);

  if(((a->Range(&sun)*0.931 > Range(&sun) || Range(a) < RND()*size/2.44)
   && RND() < Fi) || RND() < 0.044)
  {
    setcolor(color);
    setfillstyle(1, color);
  }
  else
  {
    setcolor(15);
    setfillstyle(1, 15);
  }

  fillellipse(a->GetX(), a->GetY(), r, r*Fi);

  for(double i=0; i<2*M_PI; i+=M_PI/4)
    if(RND() < Fi)
    {
      Point b(a->GetX()+cos(i)*r, a->GetY()-sin(i)*r*Fi);
      Drawing(&b, r*Fi, color);
    }
}

#endif