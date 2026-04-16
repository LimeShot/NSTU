#include <iostream>
#include <fstream>
using namespace std;
#ifndef ADT_mem_def
#define ADT_mem_def 0
//--- Абстрактный базовый класс объектов,
// основанный на непрерывной области памяти
class ADT_mem{
protected:
public:
	int	n;		// текущая размерность
	void *pd;	// область данных
public:
ADT_mem(void *q, int n0){	// Конструктор
		n=n0;
		pd=new char[n];
		char *q1,*q2;
		for (q1=(char*)q,q2=(char*)pd; n0!=0; n0--)
			*q2++ = *q1++;
		}
// Вируальный деструктор для полиморфного 
// удаления по указателю на БК
virtual ~ADT_mem(){ delete []pd; }
// Интерфейсные методы
virtual int type()=0;			// Возвращает ID класса
virtual char* name()=0;			// Возвравщает имя класса
virtual int get(char[])=0;		// Ввод из внешнего представления
virtual char *put()=0;			// Вывод во внешнее представление
virtual int save(fstream &F){	// Сохранение в двоичный поток
	F.write((char*)&n,sizeof(int));
	F.write((char*)pd,n);
	return F.good();}
virtual int load(fstream &F){	// Загрузка из в двоичного потока
	delete []pd;
	pd=NULL;
	F.read((char*)&n,sizeof(int));
	if (!F.good()) return 0;
	pd=new char[n];
	F.read((char*)pd,n);
	return F.good();}
virtual ADT_mem *clone()=NULL;	// Создание копии (клона) объекта
virtual int cmp(ADT_mem*)=NULL;	// Сравнение объектов
virtual int add(ADT_mem*)=NULL;	// Сложение объектов 1=1+2
virtual int fsize()				// Возвращает размер объекта в файле
	{ return n+sizeof(void*); }
	};
//-------------------------------------------------
#endif