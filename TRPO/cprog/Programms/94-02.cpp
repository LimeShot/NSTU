#include <stdio.h>
//------------------------------------------------------94-02.cpp
//----- Вывод текста с заданной страницы
 void main() {
	FILE *fd; char name[30]="94.txt" , str[80];
	int i,n,NP;						// Количество страниц в файле
	long *POS;							// Массив указателей начала страниц в файле
 	if ((fd=fopen(name,"r"))==NULL) return;
	for (n=0;fgets(str,80,fd)!=NULL;n++);
	NP=n/20; if (n%20!=0) NP++;		// Кол-во строк - кол-во-страниц
	fseek(fd,0,SEEK_SET);			// Вернуться в начало файла
	POS=new long[NP];				// Динаимческий масссив "закладок"
    for (n=0; n < NP; n++){			// Просмотр страниц файла
		POS[n]=ftell(fd);			// Запомнить начало страницы
		for (i=0; i<20; i++)        // Чтение строк страницы
			if (fgets(str,80,fd)==NULL) 
				break;                // Конец файла - выход из цикла
		if (i < 20) break;            // Неполная страница - выход 
		}
	while(1){
	printf("page number(0..%d):",NP-1); scanf("%d",&n);
	if ((n >= NP) || (n <0)) break;
	fseek(fd,POS[n],SEEK_SET);    // Позиционироваться на страницу
	for (i=0; i<20; i++) {		// Повторное чтение страницы
		if (fgets(str,80,fd)==NULL) break;
        printf("%s",str);
        }}}
