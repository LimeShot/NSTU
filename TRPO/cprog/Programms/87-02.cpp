#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
//--------------------------------------------------------------87-02.cpp
// Хеширование - списки конфликтующих ключей
struct cell{			// Ячейка хэш-таблицы - элемент списка
	int ckey;			// Значение ключа
	cell *next;
};
struct HASH{			// Структура со встроенными функциями
	cell **hash;		// Хеш-таблица - массив указателей на списки
	int POW,sz;			// Размерность таблицы sz=10^POW
	int KSIZE,w;		// Размерность ключа (кол-во цифр) w=10^KSIZE
	int s1;				// Простое число, следующее за sz
void reset(){			// Разрушение хеш-таблицы
	cell *p,*q;
	for (int i=0;i<sz;i++)
		for (p=hash[i];p!=NULL;){
			q=p; p=p->next; delete q;
			}
	delete []hash;
	}
void init(int p0, int ksz0){
	int i;
	srand(time(NULL));
	POW=p0;
	sz=pow(10,(double)POW);
	KSIZE=ksz0;
	w=pow(10.,KSIZE);
	for(s1=sz+1;1;s1++){// Простое число, следующее за sz
		for (i=2;i<s1 && s1%i!=0;i++);
		if (i==s1) break;
		}
	hash=new cell*[sz];
	for (int i=0;i<sz;i++) hash[i]=NULL;
	}
// хэш-функция - остаток от деления на s1
int hash_fun(int key){ return (key%s1) %sz; }
void insert(int val){
	int v=hash_fun(val);
	cell *q;
	for (q=hash[v];q!=NULL;q=q->next)
   		if (q->ckey==val) break;
	if (q==NULL)			// Значения в таблице нет
   		{
		q=new cell;			// Вставка в начало списка
		q->ckey=val;
		q->next=hash[v];
		hash[v]=q;
		}
	}
void show(){
	int cnt=0,cnt1=0;
	for (int i=0;i<sz;i++){
		printf("\n[%d]=",i);
		if (hash[i]!=NULL){
			cnt++;
			for (cell *q=hash[i]; q!=NULL; q=q->next,cnt1++)
				printf("%d ",q->ckey);
		}}
	printf("\nT=%lf\n",(double)cnt1/cnt);
	getch();
	}
void load_rand(double proc){ // Процент загрузки таблицы
	for (int i=0;i<sz*proc;i++)
		insert(rand()%w);
	}
};

void main(){
	HASH TB;
	TB.init(2,4);
	TB.load_rand(0.50);	TB.show();
	TB.load_rand(0.25);	TB.show();
	TB.load_rand(0.10);	TB.show();
	TB.load_rand(0.05);	TB.show();
	TB.load_rand(0.05);	TB.show();
	TB.load_rand(0.05);	TB.show();
}
