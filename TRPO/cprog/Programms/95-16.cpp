#include <stdio.h>
//------------------------------------------------------95-16.cpp
//------------------------------------------------------ 
 #define FNULL -1L
 struct tree { tree *p[4]; char *s; };	// Вершина дерева в памяти
 struct ftree { long fp[4]; int sz; };  // Вершина дерева в файле
 
 tree *F(FILE *fd, long pos) 
 { ftree A;                             // Текущая вершина из файла
 if (pos==FNULL) return NULL;           // NULL-указатель - выйти
 tree *q = new tree;					// Создать вершину в динам. памяти 
 fseek(fd,pos,SEEK_SET);				// Позиционироваться на вершину
 fread( (void*)&A, sizeof(ftree),1,fd); // в файле и читать ее
 q->s= new char[A.sz+1];				// Строка запись переменной длины
 fread(q->s,A.sz,1,fd);                 // следует сразу за вершиной
 q->s[A.sz]=0;							// Добавить ограничитель конца строки
 for (int i=0; i<4; i++)                // рекурсивная загрузка потомков
 q->p[i]=F(fd,A .fp[i]);
 return q; }							// В начале файла корневая вершина
 void main() { FILE *fd=fopen("a.dat","rb"); tree *head = F(fd,0L); } 
 
