#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
//-------------------------------------------------112-01.cpp
// Иерархия данных - конструирование, присваивание, копирование
class string1{
	char *str;
public:
	string1(){ str=strdup("");}
	string1(char *s){ str=strdup(s); }
	string1(string1 &T){ str=strdup(T.str); }	// КК
	~string1(){ delete []str; }
	string1 &operator=(string1 &T){			// Присваивание
		delete []str;
		str=strdup(T.str);
		return *this;
		}
	friend ostream&operator<<(ostream &O, string1 &D){
		O << D.str << endl; return O; }
};
class date{
	int dd,mm,yy;
public:
	date(int d=1,int m=1,int y=2000)
		{ dd=d; mm=m; yy=y; }
	// КК и = переопределять не требуется
	friend ostream&operator<<(ostream &O, date &D){
		O << D.dd << " " << D.mm << " " << D.yy << endl; return O; }
	};

#define N 10
class user{
	string1 name,addr;
	date birth;
	int sz,n,n2;
	string1 *P;		// Динамический массив string1[]
	string1 Q[N];		// Статический массив string1[]
public:
	user(){ sz=5; n=0; n2=0; P=new string1[sz]; }
	user(char nm[], char a[],int d0, int m0, int y0):
		name(nm), addr(a), birth(d0,m0,y0)
		{ sz=5; n=0; n2=0; P=new string1[sz]; }
	user(user &T){		// Конструктор копирования - копии всех
		name=T.name;	// компонент через переопределенное =
		addr=T.addr;
		birth=T.birth;
		sz=T.sz; n=T.n; n2=T.n2;
		P=new string1[sz];	// Копия динамического и статического массивов
		int i;
		for (i=0;i<n;i++) P[i]=T.P[i];
		for (i=0;i<N;i++) Q[i]=T.Q[i];
		}
	user &operator=(user &T){
		name=T.name;	// Переопределение присваивания
		addr=T.addr;	// Копирование всех компонент
		birth=T.birth;	// через переопределенное =
		delete []P;		// Копирование динамического
		sz=T.sz; n=T.n;	n2=T.n2;
		P=new string1[sz];	// и статического массивов
		int i;
		for (i=0;i<n;i++) P[i]=T.P[i];
		for (i=0;i<T.n2;i++) Q[i]=T.Q[i];
		return *this;
		}				// Переопределение вывода в поток
	friend ostream&operator<<(ostream &O, user &D){
		O << D.name << D.addr << D.birth;
		int i;
		for (i=0;i<D.n; i++) O << D.P[i];
		for (i=0;i<D.n2; i++) O << D.Q[i];
		return O; }
	void add(string1 &D){ P[n++]=D; }
	void add2(string1 &D){ Q[n2++]=D; }
	};

void main(){
	user A,B("Ivanov","there",5,12,1986),C(B);
	B.add(string1("a-a-a-a-a-a"));
	B.add2(string1("1111111111111"));
	B.add2(string1("555"));
	A=B;
	cout << A << B << C;
	}