//------------------------------------------------------63-10.cpp
#include <stdio.h>
 struct list { int val; list *next ,*prev; };
 extern list a,b,c;                   	// Статический двусвязный список
 list a={0, &b,NULL}, b={1,&c,&a}, c={2, NULL,&b}, *ph = &a;
 //------------------------------------------------------- 0
 // Включение в конец двусвязного списка
 void F0(list *&ph, int v)				// ph - ссылка на заголовок 
 {  list *p,*q = new list;				// Создать новый элемент списка
	q->val=v; q->next=q->prev = NULL; 	// По умолчанию - единственный
	if (ph == NULL) {ph=p; return; }	// Список пуст - включить новый
	for (p=ph;p->next!=NULL;p=p->next);	// Найти последний
	p->next=q; q->prev=p;}				// Новый - следующий за последним
 //--------------------------------------------------------
 int main(){					
 F0(ph,5); F0(ph,4); F0(ph,6); F0(ph,3);                        
 // Просмотр списка в прямом и обратном направлениях
 list *q;
 for (q=ph; q->next!=NULL; q=q->next) printf("%d ",q->val);
 for (; q!=NULL; q=q->prev) printf("%d ",q->val);
 }
