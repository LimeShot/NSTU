#include <stdio.h>
#include <string.h>
//------------------------------------------------------95-10.cpp
//---- Сохранение дерева в файле "хвостом вперед"
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

//------ Функция записи возвращает адрес размещенной вершины в файле
 long PutTree(tree *q, FILE *fd){
	if (q == NULL) return FNULL;
	ftree CUR; CUR.n=q->n;		// Текущая вершина - локальная переменная
	long pos;
	for (int i=0; i<q->n; i++)	// Рекурсивное сохранение потомков
		CUR.fp[i]=PutTree(q->p[i],fd);
	pos = ftell(fd);            // Адрес вершины
	CUR.sz=strlen(q->str)+1;    // Длина строки (ЗПД)
	fwrite(&CUR,TSZ,1,fd);      // Сохранить вершину
	fwrite(q->str,CUR.sz,1,fd); // Сохранить строку
	return pos;}
// В начало файла записывается указатель на головную
// вершину дерева
void SaveTree(tree *p, char *name){
	FILE *fd; long pos0;		// Указатель на корневую вершину
	if ((fd=fopen(name,"wb")) ==NULL) return;
	fwrite(&pos0,sizeof(long),1,fd); // Резервировать место под указатель
	pos0 = PutTree(p,fd);       // Сохранить дерево
	fseek(fd,0L,SEEK_SET);		// Обновить указатель
	fwrite(&pos0,sizeof(long),1,fd); 
	fclose(fd);
	}

 tree A1={"aaaaa",0};
 tree A2={"bbb",0};
 tree A3={"cccc",0};
 tree A4={"dddd",0};
 tree B1={"eee",2,&A1,&A2};
 tree B2={"ffff",2,&A3,&A4};
 tree C={"gggg",2,&B1,&B2};
 void main(){
 SaveTree(&C,"95-10.dat");
 }
