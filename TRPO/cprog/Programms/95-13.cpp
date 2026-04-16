#include <stdio.h>
#include <string.h>
#define FNULL -1l
//------------------------------------------------------95-13.cpp
//------ Поиск в двоичном дереве по образцу с поэлементной загрузкой
 struct ftree {				// Вершина дерева в файле
 long fl,fr;                // Указатели на потомков в файле
 int sz; };                 // Длина строки в файле (ЗПД)

 char *FindTree(long pos, char *key, FILE *fd){
	 ftree A; char *str;
	if (pos == FNULL) return NULL;
	fseek(fd, pos, SEEK_SET);
	fread(&A, sizeof( ftree), 1, fd);
	str=new char[A.sz];		// Чтение строки в динамический массив
	fread(str,A.sz,1,fd);
	if ( strncmp(str,key,strlen(key))==0)
		return str;         // Совпадение с образцом
	char *pnext;            // Найденная строка от потомка
	if (strcmp(str,key) > 0)
		pnext=FindTree(A.fl,key,fd);
	else
		pnext=FindTree(A.fr,key,fd);
	delete str;             // Уничтожить текущую строку
	return pnext; }         // и вернуть строку потомка

 void main(){
 FILE *fd=fopen("95-14.dat","rb");
 char *s =FindTree(0l,"tt",fd);
 if (s!=NULL) {puts(s); delete s; }
 fclose(fd);}
