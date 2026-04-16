#include <stdio.h>
//------------------------------------------------------81-01.cpp
// Представление дерева в виде массива с индексами предков.
struct mtree{
	char *s;
	int parent;
	};
mtree A1[]={
	{"aa",-1},
	{"bb",0},
	{"cc",1},
	{"dd",0},
	{"ee",8},
	{"ff",1},
	{"gg",3},
	{"hh",5},
	{"ii",3},
	{"jj",7},
	{"kk",7}};

void scan_m(mtree A[], int n, int k,int level){	// k - индекс текущей вершины
	printf("l=%d node=%d s=%s\n",level,k,A[k].s);
	for (int i=0;i<n;i++)
		if (A[i].parent==k) scan_m(A,n,i,level+1);
}

// Представление дерева с двумя потомками в массиве
// с вычисляемыми индексами

void scan_2(int A[], int n, int k,int level){	// k - индекс текущей вершины
	if (k>=n) return;
	if (A[k]==-1) return;
	printf("l=%d node=%d val=%d\n",level,k,A[k]);
	scan_2(A,n,2*k,level+1);
	scan_2(A,n,2*k+1,level+1);
}
//         0 1 2 3 4 5 6 7 8 9 10
int A2[]={-1,1,2,3,4,5,6,7,8,9,10};



// Представление дерева в виде таблицы ветвей
void scan_3(int A[][2],int k,int level){	// k - индекс текущей вершины
	printf("l=%d node=%d\n",level,k);
	for (int i=0;A[i][0]!=-1;i++)
		if (A[i][0]==k) scan_3(A,A[i][1],level+1);
}
int A3[][2]={{0,1},{0,2},{1,3},{1,4},{2,5},{1,6},{3,7},{2,8},{-1,0}};

// Представление дерева в виде разветвляющегося списка
struct ltree{
	char *s;
	ltree *son,*bro;	// Указатели на старшего сына
	};					// и младшего брата

ltree	A={"aa",NULL,NULL},	// Последняя в списке
		B={"bb",NULL,&A},
		C={"cc",NULL,&B},	// Список потомков - концевых вершин A,B,C
		D={"dd",NULL,NULL},
		E={"ee",&C,NULL},
		F={"ff",&D,&E},		// Список потомков G - вершин F,E
		G={"gg",&F,NULL},
		*ph = &G;

void scan_l(ltree *p, int level){
	if (p==NULL) return;
	printf("l=%d val=%s\n",level,p->s);
	for (ltree *q=p->son;q!=NULL;q=q->bro)
		scan_l(q,level+1);
		}

#define N 4
struct tree{
	char *s;
	int n;					// Количество потомков в МУ
	tree *ch[N];
	};

tree	H1={"aa",0},		
		B1={"bb",0},
		C1={"cc",0},
		D1={"dd",0},
		E1={"ee",3,&C1,&B1,&H1},
		F1={"ff",0},		
		G1={"gg",3,&F1,&E1,&D1},
		*ph1 = &G1;


void scan(tree *p, int level){
	if (p==NULL) return;
	printf("l=%d val=%s\n",level,p->s);
	for (int i=0; i<p->n; i++)
		scan(p->ch[i],level+1);
		}

// Представление дерева с массивом указателей в вершине
void main(){
	scan(ph1,1);
	puts("-----------------------------------");
	scan_l(ph,1);
	puts("-----------------------------------");
	scan_m(A1,11,0,0);
	puts("-----------------------------------");
	scan_2(A2,11,1,0);
	puts("-----------------------------------");
	scan_3(A3,0,0);
}