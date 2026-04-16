#include <stdio.h>
#include <string.h>

 struct tree {				// Вершина дерева в памяти
	char *str;              // Строка в памяти
	int n;					// Количество потомков
	tree *p[4];             // Указатели на потомков в памяти
 };
 struct ftree{				// Вершина дерева в файле
	int n;					// Количество потомков
	long fp[4];             // Указатели на потомков в файле
	int sz; };              // Длина строки в файле (ЗПД)

 #define FNULL -1L
 #define TSZ sizeof(ftree)

 void scan(tree *q,int l){
 if (q==NULL) return;
 printf("%d:%s\n",l,q->str);
 for (int i=0; i<q->n; i++) scan(q->p[i],l+1);
 }

//------------------------------------------------------95-12.cpp
//----- Загрузка вершины дерева и потомков из файла
 tree *GetTree(long pos, FILE *fd){ // Вход - адрес вершины в файле
	if (pos == FNULL) return NULL;  // Результат - указатель на
	tree *q=new tree;               // вершину поддерева в памяти
	ftree A;                        // Текущая вершина из файла -
	fseek(fd,pos,SEEK_SET);         // в локальной переменной
	fread(&A,sizeof(ftree),1,fd);
	q->str=new char[A.sz];          // Загрузка строки - ЗПД
	fread(q->str,A.sz,1,fd);
	q->n=A.n;
	for (int i=0; i<A.n; i++)		// Рекурсивная загрузка потомков
		q->p[i]=GetTree(A.fp[i],fd);// и сохранение указателей
	return q; }
// В начале файла читается файловый указатель
// на головную вершину дерева
tree *LoadTree(char *name){
	FILE *fd; long phead;
	if ((fd = fopen(name,"rb")) ==NULL) return NULL;
	fread(&phead, sizeof(long), 1, fd);
	return GetTree(phead, fd); }

void main(){
	tree *q=LoadTree("95-10.dat");
	scan(q,0);}

