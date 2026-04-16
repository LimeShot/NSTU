//------------------------------------------------------62-06.cpp
//------- Создание ДМУ из строк файла
 #include <stdio.h>
 #include <string.h>
 #include <malloc.h>
 #include <time.h>
 #include <windows.h>
 #define SIZE0 100					// Начальная размерность ДМУ
 char **loadfile(FILE *fd){
 int cnt=0;
 long T0=clock();
 char str[1000];
 int i,j,n=0,sz=SIZE0;				// Кол-во строк и размерность ДМУ
 char **pp = new char*[sz];			// Создать ДМУ
 while (fscanf(fd,"%s",str)==1){
	for (i=0;i<n;i++){
		cnt++;						// Счетчик сравнений
		if (strcmp(str,pp[i])<0) break;
		}
		for (j=n-1;j>=i;j--) 
			pp[j+1]=pp[j];
		pp[i]=strdup(str);			// Копия строки в ДМ
		n++;
		if (n%5000==0) printf("%d\t%d\t%ld\n",n,cnt,clock()-T0);
		if (n+1==sz){				// Будет переполнение - 
			sz*=2;					// удвоить размерность
			pp=(char**)realloc(pp,sizeof(char*)*sz);
			}}
 pp[n] = NULL;                      // Ограничитель массива указателей
 printf("%d\t%d\t%ld\n",n,cnt,clock()-T0);
 return pp; }

 void main(){ 
 int i;
 FILE *fd=fopen("text.txt","r");
 char cc[80];
 char **pp=loadfile(fd);
 puts("---------------------------------------------");
 gets(cc);
 for (i=0; pp[i]!=NULL; i++){
	CharToOemA(pp[i],cc);
	printf("%s\n",cc);
	}
 for (i=0; pp[i]!=NULL; i++) delete []pp[i];
 delete []pp; fclose(fd);
 }
