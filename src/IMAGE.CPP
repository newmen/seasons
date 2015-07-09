//#include "pointh.cpp"
#include "tree.cpp"
#include "sun.cpp"
#include "cloud.cpp"
#include "bird.cpp"
#include "grass.cpp"

int main()
{
  int gdriver = VGA, gmode = VGAHI;
  initgraph(&gdriver, &gmode, "D:\\TC30\\BGI");

  randomize();

  int x, y;
  double size;

  int flowers[5] = { 11, 12, 13, 14, 15 };
  int finums[6] = { 1, 2, 3, 5, 8, 13 };

  Point sun, back;

  while(!kbhit())
  {
    sun.SetXY(random(getmaxx()), random(50));

// global
    Sun s(&sun, 40);
    Tree t(&back, &sun, 200);
    Grass g(&back, 10);

    t.SetColors(2, 4, 5, 6);

    int clouds = 1;
    int birds = 3;
    int grasses = 0;

//vremena goda (:
    int time = random(4);

    if(time == 0) // vesna
    {
      setrgbpalette(7, 54, 54, 54);
      setrgbpalette(5, 34, 27, 12);
      setrgbpalette(4, 36, 56, 30);
      setrgbpalette(3, 37, 56, 17);
      setrgbpalette(2, 15, 52, 23);
      setrgbpalette(1, 26, 47, 8);

      s.SetSize(40);
      t.SetLeaf(M_PI/6.66, 0.88, 1.01);
      t.SetShowFlowers(1);
      g.SetShowFlowers(1);

      clouds = random(4)+2;
      birds = finums[random(3)+3];
      grasses = random(300)+1500;
    }
    else if(time == 1) // leto
    {
      setrgbpalette(7, 57, 57, 57);
      setrgbpalette(5, 33, 26, 12);
      setrgbpalette(4, 26, 56, 16);
      setrgbpalette(3, 32, 50, 11);
      setrgbpalette(2, 1, 49, 8);
      setrgbpalette(1, 22, 37, 17);

      s.SetSize(45);
      t.SetLeaf(M_PI/5.22, 1.0, 0.98);
      t.SetShowFlowers(0);
      g.SetShowFlowers(1);

      clouds = random(3)+1;
      birds = finums[random(3)+2];
      grasses = random(400)+1800;
    }
    else if(time == 2) // osen'
    {
      setrgbpalette(7, 50, 50, 50);
      setrgbpalette(5, 32, 25, 11);
      setrgbpalette(4, 60, 60, 0);
      setrgbpalette(3, 55, 48, 5);
      setrgbpalette(2, 53, 13, 2);
      setrgbpalette(1, 51, 42, 7);

      s.SetSize(35);
      t.SetLeaf(M_PI/5.777, 0.96, 1.5);
      t.SetShowFlowers(0);
      g.SetShowFlowers(0);

      clouds = random(3)+4;
      birds = finums[random(4)+2];
      grasses = random(200)+1400;
    }
    else // zima
    {
      setrgbpalette(7, 45, 45, 45);
      setrgbpalette(5, 31, 24, 10);
      setrgbpalette(4, 54, 54, 60);
      setrgbpalette(3, 51, 51, 58);
      setrgbpalette(2, 43, 43, 51);
      setrgbpalette(1, 40, 41, 44);

      s.SetSize(30);
      t.SetLeaf(M_PI/13.13, 0.1333, 0.51);
      t.SetShowFlowers(0);
      g.SetShowFlowers(0);

      clouds = random(1);
      birds = finums[random(2)];
      grasses = random(25)+25;
    }

// nebo
    setfillstyle(1, 9);
    floodfill(2, 2, 9);

// solnce
   s.Draw(14);

// oblaka
    Cloud c(&back, &sun);

    y = random(getmaxy()/2-25)+25;
    double size;

    while(clouds > 0)
    {
      x = random(getmaxx()-25)+50;
      size = 50*(double)(random(125)+75)/(y+50*(clouds-4));

      back.SetXY(x, y + 50*(clouds-4));
      if(sun.Range(&back) < size/Fi)
      {
	y += 10;
	continue;
      }

      c.SetXY(x, y + 50*(clouds-4));
      c.SetSize(size);
      c.Draw(7);

      clouds--;
    }

// ptici
    for(; birds>0; birds--)
    {
      x = random(getmaxx()-50)+100;
      y = random(getmaxy()/2-100)+50;
      size = random(10)+10;

      back.SetXY(x, y+size);
      if(sun.Range(&back) < 60) y+=30;

      Bird b(x, y, size);
      b.Draw(8);
    }

// zemlya
    setcolor(3);
    setfillstyle(1, 3);

    x = random(300);
    y = random(30);

    back.SetXY(0, getmaxy());

    for(double i=M_PI; i>=0; i-=2*M_PI/(getmaxx()+300))
    {
      line(back.GetX(), back.GetY(),
       x+getmaxx()/2-150+cos(i)*500, y+getmaxy()/2+15-sin(i)*50);
      back.SetXY(x+getmaxx()/2-150+cos(i)*500, y+getmaxy()/2+15-sin(i)*50);
    }

    floodfill(x, y+getmaxy()/2, 3);

// derev'ya i trava
    int Tflowerscolor = flowers[random(5)];
    int Gflowerscolor;
    do
      Gflowerscolor = flowers[random(5)];
    while(Gflowerscolor == Tflowerscolor);

    int trees = random(21)+3;
    int yG;

    y = getmaxy()/2-70;

    for(i=0; i<trees; i++)
    {
      x = random(getmaxx()-20)+10;

      while(getpixel(x, y) != 3)
      {
	x = random(getmaxx()-20)+10;
	y += random(10)+8;
      }

      t.SetXY(x, y);
      t.SetSize(pow(y, 1.333)*0.0666);
      t.Draw(Tflowerscolor);

      for(int j=0; j<grasses/trees; j++)
      {
	do
	{
	  x = random(getmaxx());
	  yG = y+random(2*(getmaxy()/2+50)/trees)-(getmaxy()/2+50)/trees;
	}
	while(getpixel(x, yG) != 3);
	g.SetXY(x, yG);
	g.SetSize((double)(pow(yG, (2-Fi)))/450);
	g.Draw(Gflowerscolor);
      }

      y += (getmaxy()/2+50)/trees;
    }

// solnce
    s.Draw(14);

// copyright
    setcolor(9);
    outtextxy(getmaxx()-175, getmaxy()-12, "(c) AlterMann 2007 (:");

    delay(7000);

//    size = 0.0;
//    while(!kbhit() || size < 1000000.0) size += 0.01;
    cleardevice();
  }

  closegraph();

  return 0;
}
