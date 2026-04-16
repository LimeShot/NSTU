#ifndef Mat_def
#define Mat_def 0
#include <stdio.h>
#include <iostream>
#include <strstream>
using namespace std;
#include "ADT_mem.h"
// Класс целого числа, построенный на классе непрерывной памяти
class Matrix : public ADT_mem{
	int nn,mm;						// Размерности в ПК, данные в БК
public:
	Matrix(int n0, int m0, double d[]): ADT_mem(d,n0*m0*sizeof(double)){
		nn=n0; mm=m0;
		}
	~Matrix(){}
// Интерфейсные методы
	int type(){return 4;}			// Возвращает ID класса
	char* name(){ return "Matrix";}	// Возвравщает имя класса
	int get(char c[]){				// Ввод из внешнего представления
		istrstream S(c);
		delete []pd;
		S >> nn >> mm;
		pd=new double[nn*mm];
		n=nn*mm*sizeof(double);
		for (int i=0;i<nn*mm;i++) S >> ((double*)pd)[i];
		return 1;
	}
	char *put(){					// Вывод во внешнее представление
		char *c=new char[1000];
		ostrstream S(c,10000);
		S << "[" << nn << "," << mm << "]";
		for (int i=0;i<nn;i++){
			S << "{";
			for (int j=0;j<mm;j++){
				S << ((double*)pd)[i*mm+j];
				S << (j==mm-1 ? "}" : ",");
				}
			}
		S << '\0';
		return c;
	}
	ADT_mem *clone(){ 
		return new Matrix(nn,mm,(double*)pd);}
	int cmp(ADT_mem *q){			// Сравнение объектов	
		if (type()!=q->type())		// Разные классы - сравнение ID
			return type()-q->type();
		Matrix *p1=(Matrix *)this;
		Matrix *p2=(Matrix *)q;
		return p1->nn*p1->mm - p2->nn*p2->mm; 
	}
	int add(ADT_mem *q){			// Сложение объектов
		if (type()!=q->type())		// Разные классы - 0
			return 0;
		//?????????????????????????????????????????????????????
		return 1;
	}
	int load(fstream &F){
		F.read((char*)&nn,sizeof(int));
		F.read((char*)&mm,sizeof(int));
		return ADT_mem::load(F);
		}
	int save(fstream &F){
		F.write((char*)&nn,sizeof(int));
		F.write((char*)&mm,sizeof(int));
		return ADT_mem::save(F);
		}
	};
#endif