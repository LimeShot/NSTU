//-----------------------------------------------92-02.cpp
// Система динамического распределения памяти
#include <stdio.h>
#include <malloc.h>
char *pa;
int sz0;
void create(int sz){
	pa=new char[sz];
	*(int*)pa=sz-sizeof(int);		// Размерность свободного куска
	sz0=sz;
	}
//--------------------------------------------------------------
// поиск строго подходящего или отрезание от первого
void *_malloc(int sz){						
	char *p=pa;
	int lnt;
	while(p<pa+sz0){
		lnt=*(int*)p;
		if (lnt<0)					// Занятый блок - пропустить
			p+=-lnt+sizeof(int);
		else{
			if (sz==lnt) {
				*(int*)p=-lnt;		// Занять блок
				return p+sizeof(int);
				}
			p+=lnt+sizeof(int);
			}
		}
	lnt=*(int*)pa;					// Отрезать от первого
	if (sz+sizeof(int)>lnt) 
		return NULL;
	lnt-=sz+sizeof(int);
	*(int*)pa=lnt;					// Остаток длины первого блока
	p=pa+lnt+sizeof(int);			// "Хвост"- выделенный блок
	*(int*)p=-sz;
	return p+sizeof(int);
	}
//--------------------------------------------------------------------
void _show(){						
	puts("---------------------------------------");
	char *p=pa;
	int lnt;
	while(p<pa+sz0){
		lnt=*(int*)p;
		if (lnt<0){					// Занятый блок - пропустить
			lnt=-lnt;
			printf("busy:");
			}
		else printf("free:");
		printf(" addr=%8d sz=%d\n",p,lnt);
		p+=lnt+sizeof(int);
		}
	}
//---------------------------------------------------------------------
void _free(void *q0){
	char *q=(char*)q0-sizeof(int);
	int lnt=*(int*)q;					// Извлечение длины
	lnt=-lnt;
	char *pr=NULL,*p=pa;
	while(p!=q){
		int ln=*(int*)p;
		if (ln<0) ln=-ln;
		pr=p;
		p+=ln+sizeof(int);
		}								// Просмотр до предыдущего
	*(int*)q=lnt;						// Освободить блок
	if (*(int*)pr>0) {
		*(int*)pr+=lnt+sizeof(int);		// Склеить с предыдущим
		p=pr;
		}
	lnt=*(int*)p;
	q=p+lnt+sizeof(int);
	if (q<pa+sz0 && *(int*)q>0)			// Есть следующий и он свободен
		*(int*)p+=*(int*)q+sizeof(int);	// Склеить со следующим
	}
#include <stdio.h>
void main(){
	create(1000);
	_show();
	void *p1=_malloc(15);
	void *p2=_malloc(15);
	void *p3=_malloc(15);
	_free(p2);
	_show();
	_free(p1);
	_show();
	_free(p3);
	_show();
}