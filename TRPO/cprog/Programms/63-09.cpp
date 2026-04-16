#include <stdio.h>
struct list{
	int val;
	list *next,*prev;
};
void show(list *p) {
list *q=p; do{
	printf("%d ",p->val);	p=p->next;
	} while(p!=q);
}

//------------------------------------------------------63-09.cpp
//--- Включение в циклический список с сохранением порядка
 list *InsSort(list *ph, int v)		// Функция возвращает новый заголовок
 { list *q = new list;              // Новый элемент как единственный
 q->val = v; q->next = q->prev = q;
 if (ph == NULL) return q;          // Список пуст вернуть новый
 list *p = ph;
	  do { if (v < p->val) break;   // Место вставки перед первым,
	  p=p->next;                    // большим заданного, иначе -
	  } while (p!=ph);				// перед первым в списке (после последнего)
 q->next = p;                       // следующий за новым = текущий
 q->prev = p->prev;					// предыдущий для нового = предыдущий текущего
 p->prev->next = q;					// следующий для предыдущего = новый
 p->prev = q;						// предыдущий для текущего = новый
 if ( ph->val > v) ph=q;            // включение перед первым -
 return ph; }                       // коррекция заголовка

void main(){
list *ph=NULL;
ph=InsSort(ph,4); ph=InsSort(ph,5); ph=InsSort(ph,2); ph=InsSort(ph,1);
show(ph);
}
