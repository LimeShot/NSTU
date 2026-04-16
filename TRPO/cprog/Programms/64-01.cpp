#include <stdio.h>
//-------------------------------------------64-01.cpp
// Циклическое слияние списка 
// Две последовательно идущие группы по s элементов сливаются
// по тем же самым координатам в выходной массив

struct list{
	int val;
	list *next;
	};

void show(list *ph){
	for (list *q=ph;q!=NULL;q=q->next) printf("%d ",q->val);
	puts("");
	}

list *sort(list *in){
	int n,s,k,i;
	list *i1,*i2,*q,*p,*out;
	for (p=in, n=0; p!=NULL; n++, p=p->next);
	for (s=1;s<n;s*=2){				// Размер группы
		p=in;
		show(p);
		list XX;
		out=&XX;
		while(p!=NULL){				// Нарезать 2 списка по s
			i1=p;
			for(i=0;p->next!=NULL && i<s-1;i++) p=p->next;
			if (p->next==NULL)		// Окончился на первой половине
				out->next=i1,p=NULL;
			else {
				i2=p->next;
				p->next=NULL;
				p=i2;
				for(i=0;p->next!=NULL && i<s-1;i++) p=p->next;
				q=p->next;
				p->next=NULL;
				p=q;
				show(i1); show(i2);
				//--------------- Слияние i1 i2
				while(i1!=NULL || i2!=NULL)
					if (i2==NULL  || i1!=NULL && i1->val < i2->val)
						out->next=i1, out=i1, i1=i1->next;
					else
						out->next=i2, out=i2, i2=i2->next;
				show(XX.next);
				}
			}
			in=XX.next;
		}
	return in;
	}					

void main(){
	int A[]={4,3,7,34,7,4,3,5,5,8,4,5,8,56,6,8,5,6,32,6,23,4,5,3,6,1,54,6,3,4};
	list *ph=NULL;
	for (int i=0;i<30;i++){ list *q=new list; q->val=A[i]; q->next=ph; ph=q; }
	ph=sort(ph);
	show(ph);
	}