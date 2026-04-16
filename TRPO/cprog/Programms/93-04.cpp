#include <stdio.h>
#include <string.h>
//------------------------------------------------------93-04.cpp
//----- Итераторы foreach, firstthat и поиска минимального для списка
 struct list { list *next;						// Указатель на следующий
 void *pdata; };								// Указатель на данные
 //----- Итератор: для каждого элемента списка
 void ForEach(list *pv, void (*pf)(void*) ) {
 for (; pv !=NULL; pv = pv->next)
      (*pf)(pv->pdata);
 }
 //----- Итератор: поиск первого в списке по условию
 void *FirstThat(list *pv, int (*pf)(void*)) {
 for (; pv !=NULL; pv = pv->next)
      if ((*pf)(pv->pdata)) return pv ->pdata;
 return NULL; }
 //----- Итератор: поиск минимального в списке
 void *FindMin(list *pv, int (*pf)(void* ,void*))
 { list *pmin;
 for ( pmin=pv; pv !=NULL; pv = pv->next)
      if ((*pf)(pv->pdata ,pmin->pdata) <0) pmin=pv;
 return pmin; }
 //----- Примеры использования итератора ------------------
 //----- Функция вывода строки
 void print(void *p) { puts((char*)p); }
 //----- Функция проверки : длины строки >5
 int bigstr(void *p) { return strlen((char*)p ) > 5; }
 //----- Функция сравнения строк по длине
 int scmp(void *p1, void *p2)
 { return strlen((char*)p1)- strlen((char*)p2); }
 //----- Вызов итераторов для статического списка,
 // содержащего указатели на строки
	   list a1={NULL,"aaaa"}, a2={&a1,"bbbbbb"}, a3={&a2,"ccccc"}, *PH=&a3;

 //----- Итератор сортировки для массива указателей
 void Sort(void **pp, int (*pf)(void*,void*))
 { int i,k;
 do
 for (k=0,i=1; pp[i] !=NULL; i++)
      if ( (*pf)(pp[i-1],pp[i])>=0)        // вызов функции сравнения
      { void *q;                           // перестановка указателей
      k++; q = pp[i-1]; pp[i-1] = pp[i]; pp[i] = q;
      }
 while(k); }
 // Пример вызова итератора сортировки для массива
 // указателей на целые переменные
 int cmp_int(void *p1, void *p2)
 { return *(int*)p1-*(int*)p2; }
 int b1=5, b2=6, b3=3, b4=2;
 void *PP[] = {&b1, &b2, &b3, &b4, NULL};
 void main()
 { char *pp;
 ForEach(PH,print);
 pp = (char*) FirstThat(PH,bigstr);
 if (pp !=NULL) puts(pp);
 pp = (char*) FindMin(PH,scmp);
 if (pp !=NULL) puts(pp);
 Sort(PP,cmp_int);
 for (int i=0; PP[i]!=NULL;i++) printf("%d ",*(int*)PP[i]);
 puts("");}
