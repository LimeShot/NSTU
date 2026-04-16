#include <stdio.h>
struct list{
	int val;
	list *next;
};
void show(list *p) {
for (; p!=NULL; p=p->next) printf("%d ",p->val);
}

//------------------------------------------------------63-04.cpp
//--- Включение в односвязный с сохранением порядка
// pr указатель на предыдущий элемент списка
 void InsSort(list *&ph, int v)
 { list *q ,*pr,*p;			// перед переходом к следующему указатель на текущий
 q=new list; q->val=v;		// запоминается как указатель на предыдущий
 for ( p=ph,pr=NULL; p!=NULL && v>p->val; pr=p,p=p->next);
 if (pr==NULL)              // включение перед первым
	  { q->next=ph; ph=q; }
 else                       // иначе после предыдущего
	  { q->next=p;          // следующий для нового = текущий
	  pr->next=q; }}        // следующий для предыдущего = новый

void main(){
list *ph=NULL;
InsSort(ph,4); InsSort(ph,5); InsSort(ph,2); InsSort(ph,1);
show(ph);
}
