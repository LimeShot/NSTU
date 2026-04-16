#ifndef Float_def
#define Float_def 0
#include <stdio.h>
#include "ADT_mem.h"
// Класс вещественного числа, построенный на классе непрерывной памяти
class Float : public ADT_mem{
public:
	Float(double a): ADT_mem(&a,sizeof(double)){}
	~Float(){}
// Интерфейсные методы
	int type(){return 3;}			// Возвращает ID класса
	char* name(){ return "Float";}	// Возвравщает имя класса
	int get(char c[]){				// Ввод из внешнего представления
		istrstream S(c);
		S >> *(double*)pd;
		return 1;
	}
	char *put(){					// Вывод во внешнее представление
		char *c=new char[20];
		ostrstream S(c,20);
		S << *(double*)pd << '\0';
		return c;
	}
	ADT_mem *clone(){ return new Float(*(double*)pd);
	}								// Создание копии (клона) объекта
	int cmp(ADT_mem *q){			// Сравнение объектов	
	if (type()!=q->type())			// Разные классы - сравнение ID
		return type()-q->type();
	return *(double*)pd - *(double*)(q->pd); 
	}
	int add(ADT_mem *q){			// Сложение объектов
	if (type()!=q->type())			// Разные классы - 0
		return 0;
	*(double*)pd+=*(double*)(q->pd); 
	return 1;
	}
};
#endif