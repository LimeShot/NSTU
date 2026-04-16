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
//randomize();
while(n--!=0){
   q=new list;
   q->val=rand();
   q->next=p;
   p=q;
	}
return p;
}
//---------------------------------------------------------72-05.cpp
//  сортировка односвязного списка рекурсивным слиянием
list *sort(list *p){
list *out,*p1,*p2,*q;
if (p==NULL || p->next==NULL)	// не более одного - конец разделения
return p;						// найти середину, p2 движется в 2 раза
p1=p2=p;						// "быстрее" p1										
while (p2->next!=NULL && p2->next->next!=NULL)
	{
	p1=p1->next; 				// 1-2-3-4-5-6-7 ==> 1-2-3-4 || 5-6-7
	p2=p2->next;
	p2=p2->next;
	}
q=p1->next;						// разделение списка на две части
p1->next=NULL;
p=sort(p);               		// рекурсивная сортировка частей
q=sort(q);
list OUT;						// для выходного списка - фиктивный
p1=&OUT;						// "последний" элемент
while(p!=NULL || q!=NULL)		// пока оба списка не пусты
	{							// второй пуст или в первом меньше, чем во втором
	if (q==NULL || p!=NULL && p->val < q->val)
   		p1->next=p,				// перенести из первый из первого списка
		p1=p1->next,			// в конец выходного
		p=p->next;
	else
   		p1->next=q,				// перенести из первый из второго списка
		p1=p1->next,			// в конец выходного
		q=q->next;
	}
return OUT.next;}

void main(){ list *ph=create(37);
show(ph); ph=sort(ph); show(ph);
}
