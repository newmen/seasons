#include <pointh.cpp>

class Grass : public PointObj
{
  int color1;
  int sflowers;

  Leaf l;
  Flower f;

  void Default()
  {
    color1 = 1;
    l.SetSize(size/2);
    f.SetSize(size/1.2);
  }

 public:
  Grass() : PointObj(0, 0, 10.0)
  {
    Default();
    f.SetNumsRandom();
  }

  Grass(const Point* a, const double& size) : PointObj(a, size), sflowers(1)
  {
    Default();
    f.SetNumsRandom();
  }

  Grass(const int& x, const int& y, const double& size) :
   PointObj(x, y, size), sflowers(1)
  {
    Default();
    f.SetNumsRandom();
  }

  void Draw(const int& color);

  void SetSize(const double& size)
  {
    this->size = size;
    Default();
  }

  void SetShowFlowers(const int& show)
  {
    sflowers = (show == 0) ? 0 : 1;
  }
};


void Grass::Draw(const int& color)
{
  double angle = M_PI_2*((double)random(30)/90+0.833);
  Point a(this, Fi*(size+random(size)), angle);

  setcolor(color1);
  this->LineTo(&a);

  if(sflowers != 0 && RND() < pow(Fi, 7.0))
  {
    a.Position(this, size+random(size), angle);
    l.Position(this, &a, 1-Fi);
    this->LineTo(&a);

    int leafs = random(2)+1;

    for(; leafs >= 0; leafs--)
    {
      l.SetAngle(((this->AngleX(&a)<0) ?
       -1 : 1)*this->AngleX(&a)+((RND()<0.5) ?
	-1 : 1)*M_PI_2*random(45)/90);
      l.Draw(color1);
    }

    f = a;
    f.Draw(color);
  }
}

/*
int main()
{
  int gdriver = VGA, gmode = VGAHI;
  initgraph(&gdriver, &gmode, "L:\\TC30\\BGI");

  randomize();

  Grass g1(200,300,50);
  g1.SetSize(50);
  Grass g2(400,300,50);
  g2.SetSize(100);

  do
  {
    cleardevice();
    g1.Draw(4);
    g2.Draw(3);
  }
  while(getch() != 27);

  closegraph();

  return 0;
}
*/