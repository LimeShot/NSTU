#include <stdio.h>
//------------------------------------------------------95-15.cpp
//--------- Односвязный список в файле. Поэлементная загрузка.
 #define FNULL -1L
 struct flist {			// Определение элемента списка в файле
 int val;				// Значение элемента списка
 long fnext;			// Файловый указатель на следующий элемент
 };						// При поэлементной работе flist *next не нужен
 
 void show(FILE *fd)			// Просмотр списка
 { flist cur;					// Файловый указатель текущего элемента
 long fcur;                     // Текущий элемент 
 fseek(fd,0L,SEEK_SET);
 fread(&fcur,sizeof(long),1,fd);// Загрузить указатель на первый
      for (; fcur!=FNULL; fcur=cur.fnext) { 
      fseek(fd,fcur,SEEK_SET);  // Загрузка текущего элемента
      fread(&cur,sizeof(flist),1,fd);
	  printf("%d ",cur.val);
	  } puts(""); }
								// Включение с сохранением упорядоченности
 void ins_sort(FILE *fd, int vv) {
 flist cur,prev,lnew;			// Текущий и предыдущий и новый элементы списка
 long fnew,fcur,fprev;          // Файловые указатели элементов списка
 fseek(fd,0L,SEEK_SET);
 fread(&fcur,sizeof(long),1,fd);
 for (fprev=FNULL; fcur!=FNULL;
 fprev=fcur, prev=cur, fcur=cur.fnext)
	  {									// Переход к следующему
	  fseek(fd,fcur,SEEK_SET);			// с запоминанием предыдущего
	  fread(&cur,sizeof(flist),1,fd);	// элемента и его адреса
	  if (cur.val > vv) break;			// Поиск места - текущий > нового
	  }
 lnew.val = vv;
 lnew.fnext=fcur;
 fseek(fd,0L,SEEK_END);				// Заполнение нового элемента списка
 fnew=ftell(fd);					// Запись в файл и получение адреса
 fwrite(&lnew,sizeof(flist),1,fd);
	  if (fprev==FNULL) {           // Включение первым -
	  fseek(fd,0L,SEEK_SET);        // обновить заголовок
	  fwrite(&fnew,sizeof(long),1,fd);
	  }
	  else {                        // Включение после предыдущего -
	  prev.fnext=fnew;              // обновить предыдущий
	  fseek(fd,fprev,SEEK_SET);
	  fwrite(&prev,sizeof(flist),1,fd);
	  }}

 void main(){
 FILE *fd=fopen("95-15.dat","wb");
 long pp=FNULL;
 fwrite(&pp,sizeof(long),1,fd);
 fclose(fd);
 fd=fopen("95-15.dat","rb+");
 int A[]={4,78,3,4,65,2,3,56,7};
 for (int i=0; i<sizeof(A)/sizeof(int); i++) ins_sort(fd, A[i]);
 show(fd);
 }
