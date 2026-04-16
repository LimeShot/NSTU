#include <stdio.h>
#include <windows.h>
//------------------------------------------------------95-07.cpp
//----- Загрузка массива указателей на строки из двоичного файла
 char **load(char *name)		// Функция возвращает динамический
 { FILE *fd; int i,sz,ns;       // массив указателей на строки
 long *pp,p0;					// Динамический массив файловых указателей
 char **p;                      // Динамический МУ на строки
 if ((fd=fopen(name,"rb"))==NULL) return NULL;
 fread(&sz,sizeof(int),1,fd);   // Прочитать размерность
 fread(&ns,sizeof(int),1,fd);   // Прочитать количество строк
 fread(&p0,sizeof(long),1,fd);  // и адрес массива файловых указателей
 pp=new long[ns];               // Создать динамический массив
 p=new char*[ns+1];              // файловых указателей и указателей на строки
 fseek(fd,p0,SEEK_SET);         // Позиционироваться на МУ в файле
 fread(pp,sizeof(long),ns,fd);	// Читать массив файловых указателей
 for (i=0; i<ns; i++)
	  { int sz;
	  fseek(fd,pp[i],SEEK_SET);		// Установиться по i-му файловому
	  fread(&sz,sizeof(int),1,fd);	// указателю и прочитать запись
	  p[i]=new char[sz];            // переменной длины - строку
	  fread(p[i],sz,1,fd);
	  }
 p[ns]=NULL; fclose(fd); return p;}

void main(){
char **pp=load("95-06.dat");
for (int i=0; pp[i]!=NULL; i++) {
	char c[80];
	CharToOemA(pp[i],c);
	printf("%s",c);
	}
}
