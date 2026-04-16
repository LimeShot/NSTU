#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
//-------------------------------------------------112-03.cpp
// Класс целого без знака
class UNS{
protected:
	unsigned val;
public:
	UNS(unsigned v0){ val=v0; }
	void add(UNS &T){ val+=T.val; }
	int  sub(UNS &T){			// Вычитание без знака не всегда корректно
					if (val<T.val) return 0; 
					val-=T.val; 
					return 1; }
	void mul(UNS &T){ val*=T.val; }
	void div(UNS &T){ val/=T.val; }
	UNS operator+(UNS &T){ UNS X=*this; X.add(T); return X; }
	UNS operator-(UNS &T){ UNS X=*this; X.sub(T); return X; }
	UNS operator*(UNS &T){ UNS X=*this; X.mul(T); return X; }
	UNS operator/(UNS &T){ UNS X=*this; X.div(T); return X; }
	friend ostream &operator<<(ostream &O, UNS &D){
		O << D.val;
		return O;}
	};
// Класс целого со знаком
class INT : UNS{
	int sign;			// Конструктор - базовый класс = абс.величина
public:
	INT(int v0):UNS(v0<0 ? -v0 : v0){ sign=(v0<0); }
	void add(INT &T){			// Знаки одинаковые - сложение абс.величин
		if (sign==T.sign) UNS::add(T); 
		else if (!UNS::sub(T)){	// Иначе - вычитание, если получается <0
			UNS X=T;			// надо выполнить наоборот и поменять знак
			X.sub(*this);
			*(UNS*)this=X;		// Копировать объект базового класса обратно
			sign=!sign;			// Поменать знак
			}
		}
	void sub(INT &T){			// Вычитание - сложение с обратным знаком
		T.sign=!T.sign;
		add(T);
		T.sign=!T.sign;}
	void mul(INT &T){ sign=(sign!=T.sign);
		UNS::mul(T);		// Знак '-' при несовпадении знаков	
		}					// Умножение абс. значений
	void div(INT &T){ sign=(sign!=T.sign);
		UNS::div(T);		// Знак '-' при несовпадении знаков	
		}					// Деление абс. значений
	INT operator+(INT &T){ INT X=*this; X.add(T); return X; }
	INT operator-(INT &T){ INT X=*this; X.sub(T); return X; }
	INT operator*(INT &T){ INT X=*this; X.mul(T); return X; }
	INT operator/(INT &T){ INT X=*this; X.div(T); return X; }
	friend ostream &operator<<(ostream &O, INT &D){
		O << (D.sign==0 ? '+' : '-') << D.val;
		return O;}
	};

void main(){
	UNS A(5),B(7);
	cout << A+B <<" " << A-B << " " << B-A << " " << A*B << " " << A/B << " " << A << " " << B <<endl;
	INT C(5),D(-7), E(-16);
	cout << C+D <<" " << C-D << " " << D-C << " " << C*D << " " << C/D << " " << C << " " << D <<endl;
	cout << E+D <<" " << E-D << " " << E-C << " " << E*D << " " << E/D << " " << E << " " << D <<endl;
	}