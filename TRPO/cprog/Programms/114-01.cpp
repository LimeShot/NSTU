//-----------------------------------------------114-01.cpp
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;
// Базовый класс графических объектов
class GR{
protected:
	int x,y,dx,dy;	// Координаты центра и прямоугольник
public:
	GR(int x0,int y0, int dx0, int dy0){
		x=x0; y=y0;dx=dx0; dy=dy0;
		}
virtual ~GR(){}
virtual	int inside(GR &T){
		return x-dx<=T.x-T.dx 
			&& x+dx>=T.x+T.dx
			&& y-dy<=T.y-T.dy
			&& y+dy>=T.y+T.dy;
		}
virtual void paint()=0;
virtual int save(ostream &O){
		O << x << " " << y << " " << dx << " " << dy << endl;
		return O.good();
		}
virtual int load(istream &O){
		O >> x >> y >> dx >> dy;
		return O.good();
		}
};

class point : public GR{
public:
	point(int x0,int y0):GR(x0,y0,0,0){}
	void paint(){}
};

class circle : public GR{
public:
	circle(int x0,int y0, int r):GR(x0,y0,r,r){}
	void paint(){}
};

class polygon : public GR{
	int *xx,*yy,n;
	void SetGR(){	// Установка параметров базового класса
		int xmin=xx[0],ymin=yy[0],xmax=xx[0],ymax=yy[0];
		for (int i=0;i<n;i++){
			if (xx[i]>xmax) xmax=xx[i];
			if (xx[i]<xmin) xmin=xx[i];
			if (yy[i]>ymax) ymax=yy[i];
			if (yy[i]<ymin) ymin=yy[i];
			}
		x=(xmax+xmin)/2;
		dx=(xmax-xmin)/2;
		y=(ymax+ymin)/2;
		dy=(ymax-ymin)/2;
		}
public:
	polygon(int x0[],int y0[],int nn):GR(0,0,0,0){
		n=nn;
		xx=new int[n];
		yy=new int[n];
		for (int i=0;i<n;i++)
			{ xx[i]=x0[i]; yy[i]=y0[i]; }
		SetGR();
		}
	~polygon(){ delete []xx; delete []yy; }
	void paint(){}
	int save(ostream &O){
		O << n << endl;
		for (int i=0;i<n;i++) 
			O << xx[i] << " " << yy[i] << endl;
		return O.good();
		}
	int load(istream &I){
		delete []xx;
		delete []yy;
		I >> n;
		xx=new int[n];
		yy=new int[n];
		for (int i=0;i<n;i++) 
			I >> xx[i] >> yy[i];
		SetGR();
		return I.good();
		}
};

void main(){
point p0(12,5);
circle c0(15,15,6);
int x0[]={5,8,4},y0[]={45,33,5};
polygon pg(x0,y0,3);
pg.save(cout);
pg.load(cin);
}