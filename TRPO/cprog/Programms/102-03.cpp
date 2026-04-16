#include <stdio.h>
#include <string.h>
//------------------------------------------------------102-03.cpp
//-----Все объекты класса string связаны в односвязный список
 class string{
		char *str;
 static string *fst;	// Указатель заголовок списка ( статический )
		string *next;   // Указатель на следующий элемент (обычный)
 public:
 static void show(){    // Просмотр всех объектов - статическая функция
		string *p;
		for (p=fst; p !=NULL; p=p->next) p->put();
		}
 void put(){puts(str);} // Вывод содержимого объекта обычная функция
 string (char*s){       // Конструктор
		str=strdup(s);
		next = fst; 
		fst = this;}	// Включение в начало статического списка
 ~ string (){           // Деструктор 
		if (fst==this){	// Удаление первого
			fst=fst->next;
			}
		else{			// Поиск предыдущего в списке
			string *p;
			for (p=fst;p->next!=this;p=p->next);
			p->next=this->next;
			}			// и выкусывание текущего из списка
		delete []str;
		}
 };
 
 string *string::fst=NULL; // Определение статического элемента данных
 
 void main()
 {  string a("aaa"),b("bbb"),*p=new string("ddd"),c("ccc"); 
	string::show(); 
	delete p;
	string::show(); 
	} // Вызов статической функции по полному имени
