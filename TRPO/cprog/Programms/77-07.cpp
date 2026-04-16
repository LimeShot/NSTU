#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//----------------------------------------------77-07
// Лексикографическая сортировка списка
int dig_len(int dig,int k){
	int i;
	for( i=0;(dig/=k)!=0;i++);
	return i+1;}
int get_dig(int v,int num,int k){
	while(num--!=0) v/=k;
	return v%k;}
int cnt=0;
struct elem {
	int v;
	elem *next;
	elem(int v0){ v=v0; next=NULL; }
	};
struct queue {
	elem *fst,*lst;
	queue(){ fst=lst=NULL; }
	};

void sort(queue &Q, int sz){
		cnt=0;
		elem *q;
		int max_len=0,l;
		queue *A=new queue[sz];					// Очереди - карманы по значениям цифр
		for (q=Q.fst;q!=NULL;q=q->next)
			if ((l=dig_len(q->v,sz))>max_len) max_len=l;
		printf("max_len=%d\n",max_len);
		for(int raz=0;raz < max_len; raz++){	// По всем цифрам, начиная с младшей
			while(Q.fst!=NULL){					// Читать входной сисок
				q=Q.fst; Q.fst=q->next;			// и разбрасывать по "карманам"
				if (Q.fst==NULL) Q.lst=NULL;	// в соответствии с очередной цифрой
				int m=get_dig(q->v,raz,sz);
				q->next=NULL;
				if (A[m].fst==NULL) A[m].fst=A[m].lst=q;
				else { A[m].lst->next=q; A[m].lst=q;} 
				cnt++;
				}
			for (int i=0;i<sz;i++){					// Склеить списка в карманах
				if (A[i].fst==NULL) continue;
				if (Q.fst==NULL){				// Выходная пустая - 
					Q.fst=A[i].fst;				// копировать начало и конец очереди
					Q.lst=A[i].lst;}
				else{
					Q.lst->next=A[i].fst;		// не пустая - присоединить к концу
					Q.lst=A[i].lst; }
				A[i].fst=A[i].lst=NULL;			// Очистить карман
				}}}

void main()
{
int n=20,*A=new int[n];
queue L;
elem *q;
srand(time(NULL));
for(int i=0;i<n;i++) {
	elem *q=new elem(rand()%10000+1);
	if (L.fst==NULL) L.fst=L.lst=q;
	else { L.lst->next=q; L.lst=q; }
	}
for(q=L.fst;q!=NULL;q=q->next) printf("%d ",q->v);
sort(L,10);	
puts("");
for(q=L.fst;q!=NULL;q=q->next) printf("%d ",q->v);
printf("\ncnt=%d\n",cnt);
}