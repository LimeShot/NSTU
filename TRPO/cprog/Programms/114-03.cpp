//-----------------------------------------------114-03.cpp
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
// Внутрениий полиморфизм - отложенное программирование
// Исправление ошибки - деление на 0
class REAL{
	double val;
public:
	REAL(double v=0){ val=v; }
virtual void on_error(REAL &TWO){}
void set(double v){ val=v; }
	void div(REAL &R){
		if (R.val==0) 
			on_error(R);
		val/=R.val;
		}
	void show(){ printf("%lf\n",val); }
};

class MY_REAL : public REAL{		
public:
	MY_REAL(double v=0):REAL(v){}
	void on_error(REAL &TWO)
		{
		printf("0-exit,1-set,default-ignore\n");
		switch (getch()){
case '0':	exit(0); 
		break;			// Завершить программу
case '1':	TWO.set(0.000000001); 
		break;			// Исправить - деление на "очень маленькое"
		}				// Игнорировать
	}
};

void main(){
	MY_REAL a(5),b(0);
	a.div(b);
	a.show();
}