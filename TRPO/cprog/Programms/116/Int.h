#ifndef Int_def
#define Int_def 0
#include <stdio.h>
#include <iostream>
#include <strstream>
using namespace std;
#include "ADT_mem.h"
// Класс целого числа, построенный на классе непрерывной памяти
class Int : public ADT_mem{
public:
	Int(int a): ADT_mem(&a,sizeof(int)){}
	~Int(){}
// Интерфейсные методы
	int type(){return 1;}			// Возвращает ID класса
	char* name(){ return "Int";}	// Возвравщает имя класса
	int get(char c[]){				// Ввод из внешнего представления
		istrstream S(c);
		S >> *(int*)pd;
		return 1;
	}
	char *put(){					// Вывод во внешнее представление
		char *c=new char[10];
		ostrstream S(c,10);
		S << *(int*)pd << '\0';
		return c;
	}
	ADT_mem *clone(){ return new Int(*(int*)pd);
	}								// Создание копии (клона) объекта
	int cmp(ADT_mem *q){			// Сравнение объектов	
		if (type()!=q->type())		// Разные классы - сравнение ID
			return type()-q->type();
		return *(int*)pd - *(int*)(q->pd); 
	}
	int add(ADT_mem *q){			// Сложение объектов
		if (type()!=q->type())		// Разные классы - 0
			return 0;
		*(int*)pd+=*(int*)(q->pd); 
		return 1;
	}
};
#endif