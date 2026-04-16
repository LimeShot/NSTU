#ifndef Str_def
#define Str_def 0
#include <stdio.h>
#include <string.h>
#include "ADT_mem.h"
// Класс целого числа, построенный на классе непрерывной памяти
class String : public ADT_mem{
public:
	String(char s[]): ADT_mem(s,strlen(s)+1){}
	~String(){}
// Интерфейсные методы
	int type(){return 2;}			// Возвращает ID класса
	char* name(){ return "String";}	// Возвравщает имя класса
	int get(char c[]){				// Ввод из внешнего представления
		delete []pd;
		pd=strdup(c);
		n=strlen(c)+1;
		return 1;
	}
	char *put(){					// Вывод во внешнее представление
		return strdup((char*)pd);
	}
	ADT_mem *clone(){ return new String((char*)pd);
	}								// Создание копии (клона) объекта
	int cmp(ADT_mem *q){			// Сравнение объектов	
		if (type()!=q->type())		// Разные классы - сравнение ID
			return type()-q->type();
		return strcmp((char*)pd,(char*)(q->pd)); 
	}
	int add(ADT_mem *q){			// Сложение объектов
		if (type()!=q->type())		// Разные классы - 0
			return 0;
		int n1=n+q->n-1;
		char *p=new char[n1];
		strcpy(p,(char*)pd);
		strcat(p,(char*)q->pd);
		delete []pd;
		n=n1;
		pd=p;
		return 1;
	}
};
#endif