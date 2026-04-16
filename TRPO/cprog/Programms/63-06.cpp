#include <stdio.h>
struct list{
	int val;
	list *next,*prev;
};
void show(list *p) {
for (; p!=NULL; p=p->next) printf("%d ",p->val);
}

//------------------------------------------------------63-06.cpp
//-------- Удаление элемента списка по заданному логическому номеру
 list *Remove(list *&pp, int n)
 { list *q;											// Указатель на текущий элемент
 for (q = pp; q!=NULL && n!=0; q = q->next, n--);	// Отсчитать n -ый
 if (q==NULL) return NULL;								// нет элемента с таким номером
 if (q->prev==NULL)									// удаление первого -
 pp=q->next;										// коррекция заголовка
 else q->prev->next = q->next;						// следующий для предыдущего  =
													// следующий за текущим
 if (q->next!=NULL)									// удаление не последнего -
 q-> next->prev = q->prev;							// предыдущий для следующего  =											 
 return q; }										// предыдущий текущего

extern list A,B,C;
list A={1,&B,NULL}, B={2,&C,&A}, C={5,NULL,&B}, *ph=&A;
void main(){
list *q=Remove(ph,1); show(ph);
}
