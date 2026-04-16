//-----------------------------------------------114-02.cpp
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

// Интерфейсный абстрактный класс упорядоченных данных
class Data{
public:
virtual	int cmp(Data *)=0;
virtual	void in(istream &)=0;
virtual	void out(ostream &)=0;
};
// Класс целых с интерфейсом ввода/вывода/сравнения
class INT : public Data{
	int val;
public:
	INT(int v=0){ val=v; }
virtual	int cmp(Data *p){ return val - ((INT*)p)->val;  }
virtual	void in(istream &I){ I >> val; }
virtual	void out(ostream &O){ O << val; }
};
// Класс списка упорядоченных данных
class list{
	struct elem{
		Data *pd;
		elem *next;
		elem(Data *p){ next=NULL; pd=p; }
		};
	elem *hd;
public:
	list(){ hd=NULL; }
	void out(ostream &O){
		for (elem *p=hd; p!=NULL; p=p->next)
			{ p->pd->out(O); O << endl; }
		}
	void inssort(Data *p){
		elem *q=new elem(p);
		if (hd==NULL) { hd=q; return; }
		if (p->cmp(hd->pd)<0){
			q->next=hd; hd=q; return;
			}
		elem *s;
		for (s=hd; s->next!=NULL; s=s->next)
			if (p->cmp(s->next->pd)<0) break;
		q->next=s->next;
		s->next=q;
		}
	};

void main(){
int A[]={5,4,8,2,6,3,7,23,76,5,3,4,0};
list X;
for (int i=0;A[i]!=0;i++)
	X.inssort(new INT(A[i]));
X.out(cout);
}