#include <stdio.h>
#include <string.h>
//------------------------------------------------------95-02.cpp
//------ Структура + строка = запись переменной длины
struct vrec {
	int dd,mm,yy;
	char name[20];				// Строка фиксированной длины
	char *addr; };			    // Строка переменной длины

void put(FILE *fd, vrec &R){
	int sz=sizeof(vrec)+strlen(R.addr)+1;
	fwrite(&sz,sizeof(int),1,fd);
	fwrite(&R,sizeof(vrec),1,fd);
	fwrite(R.addr,strlen(R.addr)+1,1,fd);
	}
vrec *get(FILE *fd){
	int size=0; vrec *p;
	if (fread(&size,sizeof(int),1,fd)==0)
		return NULL;;			// Чтение счетчика длины - конец файла
	if (size < sizeof(vrec)) 
		return NULL;			// Короткая запись
	p=new vrec;
	fread(p,sizeof(vrec),1,fd); // Постоянная часть записи
	size -= sizeof( vrec);      // Остаток записи - строка
	p->addr=new char[size];
	fread(p->addr,size,1,fd);	// Переменная часть записи
	return p; }

void main(){
	vrec R[5]={
		{3,12,1986,"Ivanov","aaaaaaaaaaaaaaaaaaaaaaaaaa"},
		{1,11,1990,"Sidorov","bbb"},
		{13,1,2007,"Petrov","ccccccc"},
		{3,1,1888,"Aksakal","ddddddddddddddddddddddddddd"},
		{35,35,9999,"Kto tam?",""},
		};
	FILE *fd=fopen("95-02.dat","wb");
	for (int i=0; i<5; i++) put(fd,R[i]);
	fclose(fd);
	fd=fopen("95-02.dat","rb");
	vrec *p;
	while((p=get(fd))!=NULL){
		printf("%d-%d-%d %s %s\n",p->dd,p->mm,p->yy,p->name,p->addr);
		delete []p->addr;
		delete p;
		}
	}