#include <iostream>
#include <fstream>
using namespace std;
#ifndef ADT_def
#define ADT_def 0
//--- "Пустой" абстрактный базовый класс
// для произвольного типа данных
class ADT{
public:
ADT(){}
// Вируальный деструктор для полиморфного 
// удаления по указателю на БК
virtual ~ADT(){}
// Интерфейсные методы
virtual int type()=0;			// Возвращает ID класса
virtual char* name()=0;			// Возвравщает имя класса
virtual int get(char[])=0;		// Ввод из внешнего представления
virtual char *put()=0;			// Вывод во внешнее представление
virtual int save(fstream &F)=0;	// Сохранение в двоичный поток
virtual int load(fstream &F)=0;	// Загрузка из в двоичного потока
virtual ADT *clone()=NULL;		// Создание копии (клона) объекта
virtual int cmp(ADT*)=NULL;		// Сравнение объектов
virtual int add(ADT*)=NULL;		// Сложение объектов 1=1+2
virtual int fsize()=0;			// Возвращает размер объекта в файле
};
//-------------------------------------------------
#endif