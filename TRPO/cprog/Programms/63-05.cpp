#include <stdio.h>
struct list{
	int val;
	list *next;
};
void show(list *p) {
for (; p!=NULL; p=p->next) printf("%d ",p->val);
}

//------------------------------------------------------63-05.cpp
//--- Сортировка односвязного списка вставками
 list *sort(list *ph)			// функция возвращает заголовок нового списка
 { list *q, *out, *p , *pr;
 out = NULL;                    // выходной список пуст
 while (ph !=NULL)              // пока не пуст входной список
	  { q = ph; ph = ph->next;  // исключить очередной
								// поиск места включения
	  for ( p=out,pr=NULL; p!=NULL && q->val>p->val; pr=p,p=p->next);
	  if (pr==NULL)             // включение перед первым
		   { q->next=out; out=q; }
	  else                      // иначе после предыдущего
		   { q->next=p; pr->next=q; }
	  }
 return out; }

list A={3,NULL}, B={5,&A}, C={1,&B}, D={4,&C},*ph=&D;
void main(){
ph=sort(ph); show(ph);
}
