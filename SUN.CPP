#include "pointh.cpp"

#ifndef MY_SUN_H
#define MY_SUN_H

class Sun : public PointObj
{
 public:
  Sun() : PointObj(0, 0, 50.0) { }
  Sun(const Point* a) : PointObj(a, 50.0) { }
  Sun(const Point* a, const double& r) : PointObj(a, r) { }
  Sun(const int& x, const int& y, const double& r) : PointObj(x, y, r) { }

  virtual void Draw(const int& color); //const;
};

void Sun::Draw(const int& color) //const
{
  setcolor(color);
  setfillstyle(1, color);
  pieslice(x, y, 0, 360, size);

  Point l1, l2;

  for(double i=0; i<2*M_PI; i+=M_PI/size)
    if(RND() < 0.15)
    {
      l1.Position(this, random(getmaxy() - y - size) + y+size/Fi, i);
      if(l1.Valid())
      {
	l2.Position(this, random(getmaxy() - y - size - this -> Range(&l1))
	 + y + size/Fi + this->Range(&l1), i);

	l1.LineTo(&l2);
      }
    }
}


#endif

/*
int main()
{
  int gdriver = VGA,
      gmode = VGAHI;
  initgraph(&gdriver, &gmode, "D:\\TC\\BGI");

  randomize();

  Cloud s(Point(400, 100), Point(20, 20), 100);
  s.Draw(8);

  do
  {
    cleardevice();
    s.Draw(8);
  }
  while(getch() != 27);

  closegraph();

  return 0;
}
*/