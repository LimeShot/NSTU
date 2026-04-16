//------------------------------------------------------62-06.cpp
//------- Создание ДМУ из строк файла
 #include <stdio.h>
 #include <string.h>
 #include <malloc.h>
 #define SIZE0 10					// Начальная размерность ДМУ
 char **loadfile(FILE *fd){
 char str[1000];
 int n,sz=SIZE0;					// Кол-во строк и размерность ДМУ
 char **pp = new char*[sz];			// Создать ДМУ
 for (n=0;fgets(str,1000,fd)!=NULL; n++){
		pp[n]=strdup(str);			// Копия строки в ДМ
		if (n+1==sz){				// Будет переполнение - 
			sz*=2;					// удвоить размерность
			pp=(char**)realloc(pp,sizeof(char*)*sz);
			}}
 pp[n] = NULL;                      // Ограничитель массива указателей
 return pp; }

 void main(){
 FILE *fd=fopen("62-06.cpp","r");
 char **pp=loadfile(fd); int i;
 for (i=0; pp[i]!=NULL; i++) printf("%s",pp[i]);
 for (i=0; pp[i]!=NULL; i++) delete []pp[i];
 delete []pp; fclose(fd);
 }
