#include <stdio.h>
struct list{
	int val;
	list *next,*prev;
};
void show(list *p) {
for (; p->next!=NULL; p=p->next) printf("%d ",p->val);
for (; p!=NULL; p=p->prev) printf("%d ",p->val);
}

 //--------------------------------------------------------------63-07
 //--------Включение в двусвязный список с сохранением порядка
 void InsSort(list *&ph, int v)		// ссылка на заголовок
 { list *q , *p=new list;			// новый элемент списка
 p->val = v;
 p->prev = p->next = NULL;
	  if (ph == NULL) {             // включение в пустой список
	  ph=p; return ;
	  }                             // поиск места включения - q
 for (q=ph; q !=NULL && v > q->val; q=q->next);
 if (q == NULL)                     // включение в конец списка
	  {								// восстановить указатель на последний
	  for (q=ph; q->next!=NULL; q=q->next);
	  p->prev = q;
	  q->next = p;
	  return;
	  }                             // включить перед текущим
 p->next=q;							// следующий за новым = текущий
 p->prev=q->prev;					// предыдущий нового = предыдущий текущего
 if (q->prev == NULL)               // включение в начало списка
	ph = p;
 else                               // включение в середину
	q->prev->next = p;				// следующий за предыдущим = новый
 q->prev=p;							// предыдущий текущего = новый
 }

void main(){
list *ph=NULL;
InsSort(ph,4); InsSort(ph,5); InsSort(ph,2); InsSort(ph,1);
show(ph);
}
