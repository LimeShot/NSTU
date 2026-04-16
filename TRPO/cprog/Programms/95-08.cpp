#include <stdio.h>
#include <windows.h>
//------------------------------------------------------95-08.cpp
//---- Массив указателей на строки, чтение по логическому номеру
 char *load(char *name, int num)		// Возвращается строка =
 { FILE *fd; int i,n,sz; long p0,pp;    // динамический массив
 if ((fd=fopen(name,"rb"))==NULL)
	  return NULL;						// Режим чтения двоичного файла
 fread(&sz,sizeof(int),1,fd);         	// Считать размерность МУ
 fread(&n,sizeof(int),1,fd);         	// Считать количество указателей
 fread(&p0,sizeof(long),1,fd);        	// и начальный адрес МУ в файле
 if (num>=n) return NULL;               // Нет записи с таким номером
 fseek(fd,p0+sizeof(long)*num,SEEK_SET);
 fread(&pp,sizeof(long),1,fd);			// Прочитать указатель с номером num
 fseek(fd,pp,SEEK_SET);					// Установиться на запись
 fread(&sz,sizeof(int),1,fd);			// Прочитать длину записи
 char *p=new char[sz];                  // Создать динамический массив
 fread(p,sz,1,fd);						// Прочитать запись - строку
 fclose(fd); return p; }				// Возвратить указатель на строку

 void main(){
 for (int i=20; i>=10; i--){
	char *s=load("95-06.dat",i); if (s!=NULL) { 
		CharToOemA(s,s);
		printf("[%d] %s",i,s); 
		delete [] s;
		}}
 }
