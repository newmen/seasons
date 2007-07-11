#include "pointh.cpp"

#ifndef MY_TREE_H
#define MY_TREE_H

class Tree : public PointObj
{
  Point center;
  Point sun;

  int color1, color2; // derevo
  int color3, color4; // listva

  int sflowers; // bool show flowers

  double kleafsize, kleafrate;

  Leaf l;
  Flower f;

  void DefaultColor()
  {
    color1 = 5;
    color2 = 6;
    color3 = 2;
    color4 = 10;
  }

  void DefaultSize()
  {
    center.SetXY(x, y-size*Fi);

    l.SetSize(kleafsize*size/35);
    f.SetSize(size/25);
  }

  void Stvol(const Point* begin, const Point* end, const int& color);
  void Divis(const Point* begin, const Point* end, const int& color);

 public:
  Tree() : PointObj(getmaxx()/2, getmaxy()/2+200, 400.0),
   sun((int)(getmaxx()*Fi), 0), sflowers(1),
   kleafsize(1.0), kleafrate(1.0)
  {
    DefaultColor();
    DefaultSize();
    f.SetNumsRandom();
  }

  Tree(const int& x, const int& y, const double& size) :
   PointObj(x, y, size), sflowers(1), kleafsize(1.0), kleafrate(1.0)
  {
    DefaultColor();
    DefaultSize();
    f.SetNumsRandom();

    if(getmaxx()/2-x > 0.0) sun.SetXY(getmaxx(), 0);
    else sun.SetXY(0, 0);
  }

  Tree(const Point* a, const Point* sun, const double& size) :
   PointObj(a, size), sun(sun), sflowers(1), kleafsize(1.0), kleafrate(1.0)
  {
    DefaultColor();
    DefaultSize();
    f.SetNumsRandom();
  }

  void Draw(const int& color)
  {
    double rndAngle = M_PI_2*(random(4)+88)/90;
    Point a(this, size, rndAngle);
    Stvol(this, &a, color);
  }

  void SetSize(const double& size)
  {
    this->size = size;
    DefaultSize();
  }

  void SetLeaf(const double& angle, const double ksize=1.0,
   const double krate=1.0)
  {
    l.SetAngleWidth(angle);
    kleafsize = ksize;
    kleafrate = krate;
  }

  void SetColors(const int l1=2, const int l2=10, const int s1=5,
   const int s2=6)
  {
    color1 = s1;
    color2 = s2;
    color3 = l1;
    color4 = l2;
  }

  void SetShowFlowers(const int& show)
  { sflowers = (show == 0) ? 0 : 1; }

};

void Tree::Stvol(const Point* begin, const Point* end, const int& color)
{
  if(begin->Range(end) < size/6.2) // !!!
  {
    Divis(begin, end, color);
    setcolor(color);
    return;
  }

  Point middle(begin, end, 1-Fi);

  Point* p1 = new Point(begin, begin->Range(end)/55, begin->AngleX(end)+M_PI_2);
  Point* p2 = new Point(begin, begin->Range(end)/55, begin->AngleX(end)-M_PI_2);

  if(middle.Range(&sun) > center.Range(&sun))
  {
    setcolor(color1);
    setfillstyle(1, color1);
  }
  else
  {
    setcolor(color2);
    setfillstyle(1, color2);
  }

  int* mass = new int[6];

  mass[0] = p1->GetX();
  mass[1] = p1->GetY();

  mass[2] = p2->GetX();
  mass[3] = p2->GetY();

  mass[4] = end->GetX();
  mass[5] = end->GetY();

  fillpoly(3, mass);

  delete[] mass;
  delete p2;
  delete p1;

  Stvol(&middle, end, color);

  int krnd = (RND() < 0.5) ? -1 : 1;

  // ranznos vetki 1
  double* temp1 = new double((begin->Range(end) < size/16) ?
   0 : (1/Fi)*random(16*(int)(begin->Range(end)/size))/begin->Range(end));

  middle.Position(begin, end, 1 - Fi + krnd * *temp1);

  delete temp1;

  // zadanie vetki 1
  double angle = M_PI_2*(random(80)+10)/100 + M_PI_2;
  Point away(&middle, middle.Range(end), angle);

  Stvol(&middle, &away, color);

  // ranznos vetki 2
  double* temp2 = new double((begin->Range(end) < size/16) ?
   0 : (1/Fi)*random(16*(int)(begin->Range(end)/size))/begin->Range(end));

  middle.Position(begin, end, 1 - Fi - krnd * *temp2);

  delete temp2;

  // zadanie vetki 1
  angle = M_PI_2*(random(80)+10)/100 - M_PI_2;
  away.Position(&middle, middle.Range(end), -angle);

  Stvol(&middle, &away, color);
}

void Tree::Divis(const Point* begin, const Point* end, const int& color)
{
  double* dl = new double(begin->Range(end));
  if(*dl < kleafrate*size/33.3)
  {
    delete dl;
    return;
  }

  Point middle;

  double* rnd = new double(RND());

  if(begin->GetX() == end->GetX() || begin->GetY() == end->GetY())
  {
    int krnd = (*rnd <= 0.5) ? 1 : -1;

    if(begin->GetX() == end->GetX())
      middle.SetXY(begin->GetX() + ((begin->GetX() + krnd * *dl/2 > 0.0) ?
       krnd : -krnd) * *dl/2, min(begin->GetY(), end->GetY()) + *dl/2);

    if(begin->GetY() == end->GetY())
      middle.SetXY(min(begin->GetX(), end->GetX()) + *dl/2,
       begin->GetY() + ((begin->GetY() + krnd * *dl/2 > 0.0) ?
	krnd : -krnd) * *dl/2);
  }
  else
    if(*rnd <= 0.5) middle.SetXY(begin->GetX(), end->GetY());
    else middle.SetXY(end->GetX(), begin->GetY());

  delete dl;

  double *chance = new double(center.Range(&sun)/middle.Range(&sun));

  if(sflowers != 0 && *rnd < 0.025 * *chance)
  {
    f = middle;
    f.Draw(color);
  }
  else
  {
    l = middle;
    if(*rnd < Fi / *chance / 0.8) l.Draw(color3);
    else l.Draw(color4);
  }

  delete chance;
  delete rnd;

  Divis(begin, &middle, color);
  Divis(&middle, end, color);
}

#endif

/*
int main()
{
  int gdriver = VGA, gmode = VGAHI;
  initgraph(&gdriver, &gmode, "D:\\TC\\BGI\\");

//  setrgbpalette(5, 30, 15, 10);

  Point sunPoint(getmaxx(), 0.0);
  Tree t1(Point(100, getmaxy()/2+50), sunPoint, 130),
       t2(Point(220, getmaxy()/2+188), sunPoint, 300),
       t3(Point(400, getmaxy()/2+120), sunPoint, 230);

  char m;


//  while (!kbhit())
  while(m != 27)
  {
    t1.Draw(4);
    t2.Draw(1);
    t3.Draw(3);

    m = getch();

    cleardevice();
  }

  closegraph();

  return 0;
}
*/