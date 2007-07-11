#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream.h>
#include <math.h>
#include <dos.h>

#ifndef MY_POINT_H
#define MY_POINT_H


// functions

const double Fi = (sqrt(5)-1)/2;

inline double RND() // return double number of 0-1 range
{ return (double)rand()/RAND_MAX; }

template <class T> T min(T a, T b)
 { return (a < b) ? a : b; }


/////////////////////////////////////////////////////////////////////////////
// classes

class Point
{
 protected:
  int x, y;

  void RandomXY() { SetXY(random(getmaxx()), random(getmaxy())); }

 public:
  Point() : x(0), y(0) { }

  Point(const int& x, const int& y) : x(x), y(y) { }

  Point(const Point* a) : x(a->x), y(a->y) { }

  Point(const Point* a, const double& range, const double& angle) :
   x(a->x + range*cos(angle)), y(a->y - range*sin(angle)) { }

  Point(const Point* a, const Point* b, const double& persent)
  { Position(a, b, persent); }


  int GetX() const { return x; }
  int GetY() const { return y; }

  void SetX(const int& x) { this->x = x; }
  void SetY(const int& y) { this->y = y; }
  void SetXY(const int& x, const int& y)
  {
    this->x = x;
    this->y = y;
  }

  virtual void Draw(const int& color) //const
   { putpixel(x, y, color); }
  virtual void Random() { RandomXY(); }
  virtual void ShowInfo() const { cout << "X=" << x << " Y=" << y << endl; }

  int Valid() const
   { return (x > 0 && x < getmaxx() && y > 0 && y < getmaxy()) ? 1 : 0; }

  void LineTo(const Point* a) const { line(x, y, a->x, a->y); }

  double Range(const Point* a) const
   { return sqrt(pow(x - a->x, 2.0) + pow(y - a->y, 2.0)); }

  double AngleX(const Point* a) const
   { return (x - a->x == 0) ? M_PI_2 : atan((double)(y - a->y)/(a->x - x)); }

  double AngleY(const Point* a) const
   { return (y - a->y == 0) ? M_PI_2 : atan((double)(a->x - x)/(y - a->y)); }

  void Position(const Point* a, const double& range, const double& angle)
   { SetXY(a->x + range*cos(angle), a->y - range*sin(angle)); }

  void Position(const Point* a, const Point* b, const double& persent);

//  void FR1(const Point& a, const double& acc, const int& pause,
//   const int& color1, const int& color2, const int& color3);

  virtual void operator = (const Point& a)
  {
    x = a.x;
    y = a.y;
  }

  virtual void operator = (const Point* a)
  {
    x = a->x;
    y = a->y;
  }

  virtual int operator == (const Point* a) const
   { return (x == a->x && y == a->y); }
};

void Point::Position(const Point* a, const Point* b, const double& persent)
{
  x = (a->x < b->x) ?
   a->x + abs(a->x - b->x) * persent :
   b->x + abs(a->x - b->x) * (1-persent);

  y = (a->y < b->y) ?
   a->y + abs(a->y - b->y) * persent :
   b->y + abs(a->y - b->y) * (1-persent);
}

/*
void Point::FR1(const Point& a, const double& acc, const int& pause,
 const int& color1, const int& color2, const int& color3)
{
  Point b;

  double rnd = RND();
  double dl = sqrt(pow(x-a.GetX(),2)+pow(y-a.GetY(),2));

  if(dl < acc) return;

  if(x == a.GetX() || y == a.GetY())
  {
    int koef = (rnd <= 0.5) ? 1 : -1;

    if(x == a.GetX())
      if(x-koef*dl/2 > 0.0 && x-koef*dl/2 < getmaxx())
	b.SetXY(x-koef*dl/2, min(y, a.GetY())+dl/2);
      else b.SetXY(x+koef*dl/2, min(y, a.GetY())+dl/2);

    if(y == a.GetY())
      if(y-koef*dl/2 > 0.0 && y-koef*dl/2 < getmaxy())
	b.SetXY(min(x, a.GetX())+dl/2, y-koef*dl/2);
      else b.SetXY(min(x, a.GetX())+dl/2, y+koef*dl/2);
  }
  else
    if(rnd <= 0.5) b.SetXY(x, a.GetY());
    else b.SetXY(a.GetX(), y);

  int color = (rnd <= 0.77) ? color1 : ((rnd <= 0.95) ? color2 : color3);

  b.Draw(color);

  delay(pause);

  FR1(b, acc, pause, color1, color2, color3);
  b.FR1(a, acc, pause, color1, color2, color3);
}
*/

//////////////////////////////////////////////////////////////////////////////

class PointObj : public Point
{
 protected:
  double size;

 public:
  PointObj(): Point(), size(0.0) { }

  PointObj(const Point* a, const double& size): Point(a), size(size) { }

  PointObj(const int& x, const int& y, const double& size):
   Point(x, y), size(size) { }

  virtual void Draw(const int& color) = 0; //const = 0;

  virtual void SetSize(const double& size) { this->size = size; }
};

//////////////////////////////////////////////////////////////////////////////

class Leaf : public PointObj
{
 private:
  double angle, angle_width;


 public:
  Leaf() : PointObj(0, 0, 10.0), angle(0.0), angle_width(M_PI/6.777) { }
//  Leaf(const Point& a) : PointObj(&a, 10.0), angle(0.0), angle_width(M_PI/6.777) { }
//  Leaf(const Point* a) : PointObj(a, 10.0), angle(0.0), angle_width(M_PI/6.777) { }

  Leaf(const int& x, const int& y, const double& size,
   const double& angle, const double& angle_width) :
    PointObj(x, y, size), angle(angle), angle_width(angle_width) { }

  virtual void Draw(const int& color); //const;
  virtual void Random()
  {
    SetAngleRandom();
    RandomXY();
  }

  void SetAngle(const double& angle) { this->angle = angle; }

  void SetAngleWidth(const double& angle_width)
   { this->angle_width = angle_width; }

  void SetAngleRandom() { angle = random(360) * M_PI / 180; }

  virtual void operator = (const Point& a)
  {
    SetAngleRandom();
    SetXY(a.GetX(), a.GetY());
  }

  virtual void operator = (const Point* a)
  {
    SetAngleRandom();
    SetXY(a->GetX(), a->GetY());
  }
};

void Leaf::Draw(const int& color) //const
{
  setcolor(color);
  setfillstyle(1, color);

  Point a(this, Fi*size, angle+angle_width/2);
  Point b(this, size, angle);
  Point c(this, Fi*size, angle-angle_width/2);

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

//////////////////////////////////////////////////////////////////////////////

class Flower : public PointObj
{
 private:
  static const int Fi[];
  int nums;

 public:
  Flower() : PointObj(0, 0, 15.0), nums(0) { }
//  Flower(const Point& a) : PointObj(&a, 15.0), nums(0) { }

  Flower(const int& x, const int& y, const double& size, const int& nums) :
   PointObj(x, y, size), nums(nums) { }

  virtual void Draw(const int& color); //const;
  virtual void Random()
  {
    SetNumsRandom();
    RandomXY();
  }

  void SetNums(const int& nums)
   { this->nums = (nums < 0) ? 0 : ((nums > 3) ? 3 : nums); }
  void SetNumsRandom() { nums = random(4); }

  virtual void operator = (const Point& a)
  {
    SetXY(a.GetX(), a.GetY());
  }

  virtual void operator = (const Point* a)
  {
//   SetNumsRandom();
    SetXY(a->GetX(), a->GetY());
  }
};
const int Flower::Fi[] = { 5, 8, 13, 21, 34, 55 };

void Flower::Draw(const int& color) //const
{
  double angle = random(90)*M_PI/180;

  for(double i=angle;i<2*M_PI+angle;i+=2*M_PI/Fi[nums])
  {
    Leaf leaf(x, y, size/2, i, 2*M_PI/Fi[nums+1]);

    leaf.Draw(color);
  }

  if(getpixel(x, y) != 14)
  {
    setcolor(14);
    setfillstyle(1, 14);
  }
  else
  {
    setcolor(12);
    setfillstyle(1, 12);
  }
  pieslice(x, y, 0, 360, size/8);
}

#endif