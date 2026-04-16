#include <stdio.h>
//-------------------------------------------------foo1.cpp
// Безымянные объекты
struct A{
	int a;
	A(int a1){a=a1;}
	A(A &b){ a=b.a;}		// КК
	A &INC(){ a++;  return *this; }
	void show(){ printf("%d\n",a); }
	};

void F(A bb){ 
	bb.a++; 
	bb.show();
	}
void main(){
	F(A(5));
	A(2).INC().INC().show();
	}