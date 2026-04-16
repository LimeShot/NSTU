#include <stdio.h>
#include <stdlib.h>
struct list{
	int val;
	list *next;
};
void show(list *p) {
for (; p!=NULL; p=p->next) printf("%d ",p->val);
puts("");
}

list *create(int n){
list *p=NULL,*q;
while(n--!=0){
   q=new list;
   q->val=rand();
   q->next=p;
   p=q;
	}
return p;
}
//---------------------------------------------------------72-03.cpp
//  сортировка односвязного списка рекурсивным разделением
list *sort(list *p){
list *m,*p1,*p2,*q;
if (p==NULL || p->next==NULL)
return p;					// не более одного - конец разделения
m=p; p=p->next;				// m-медиана - первый элемент
p1=p2=NULL;					// p1,p2 - разделенные списки
while(p!=NULL){
   q=p; p=p->next;			// извлечь очередной из входного
   if (q->val < m->val)
		q->next=p1, p1=q;	// меньше медианы - в начало первого
   else
   		q->next=p2, p2=q;	// иначе - в начало второго
	}
p1=sort(p1);				// рекурсивная сортировка частей
p2=sort(p2);
m->next=p2;					// "склеить" медиану и второй список
if (p1==NULL) return m;		// первый - пустой
for (q=p1;q->next!=NULL; q=q->next);
q->next = m;               // иначе, дойти до конца первого
return p1;                 // и присоединить к нему медиану
}                          // со вторым

void main(){ list *ph=create(50);
show(ph); ph=sort(ph); show(ph);
}
