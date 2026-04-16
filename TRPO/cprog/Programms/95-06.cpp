#include <stdio.h>
#include <string.h>
#define FNULL 0
//------------------------------------------------------95-06.cpp
//---- Создание файла с массивом указателей из текстового файла
// Формат файла: ns - размерность МУ (количество указателей)
// p0 - смещение массива указателей
 void save(char *in, char *out)
 { FILE *fdi,*fdo; char c[80]; int ns,i;
 if ((fdi=fopen(in,"r"))==NULL) return;
 if ((fdo=fopen(out,"wb"))==NULL) return;
 for (ns=0; fgets(c,80,fdi)!=NULL; ns++);   // Количество строк
 int sz=ns*1.2;								// Размерность с учетом резерва
 fseek(fdi,0l,SEEK_SET);                    // Вернуться к началу
 long *pp = new long[sz];					// Массив указателей в файле
 for (i=0;i<sz;i++) pp[i]=FNULL;
 long p0=2*sizeof(int)+sizeof(long);        // Начальное смещением МУ
 fwrite(&sz,sizeof(int),1,fdo);             // Записать размерность МУ
 fwrite(&ns,sizeof(int),1,fdo);             // Записать размерность МУ
 fwrite(&p0,sizeof(long),1,fdo);            // Записать смещение МУ
 fwrite(pp,sizeof(long),sz,fdo);            // Записать "пустой" МУ
 for (i=0; i<ns; i++) {						// Повторное чтение строк
	  pp[i]=ftell(fdo);						// Получить адрес i-ой строки
	  fgets(c,80,fdi);
	  int l=strlen(c)+1;					// Переписать в формате ЗПД
	  fwrite(&l,sizeof(int),1,fdo);
	  fwrite(c,l,1,fdo);
	  }
 fseek(fdo,p0,SEEK_SET);                    // Обновить в файле массив
 fwrite(pp,sizeof(long),sz,fdo);			// файловых указателей
 fclose(fdo);}

 void main(){
 save("95-06.cpp","95-06.dat");
 }
