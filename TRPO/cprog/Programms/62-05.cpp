//------------------------------------------------------62-05.cpp
//--- Массив указателей на отсортированные по длине слова
#include <stdio.h>
 int my_strlen(char *p){ int i;
 for (i=0; *p!=0 && *p!=' '; p++,i++);
 return i;}
 char **SortedWords(char *p){
 int nw=0,k; char *q;
 for (q=p; *q!=0; q++)			// Подсчет количества слов по концам слов
 if (q[0]!=' ' && (q[1]== ' '|| q[1]==0)) nw++;
 char **qq=new char*[nw+1];		// Создать ДМУ на строки (символы строки)
 nw=0;
 if (*p!= ' ') qq[nw++]=p;		// Строка начинается со слова
 for (p++; *p!=0; p++)			// Если начало слова - 
 if (p[0]!=' ' && p[-1]==' ')	// запомнить текущий указатель в строке
	  qq[nw++]=p;
 qq[nw]=NULL;
 do {							// Сортировка массива указателей
	 k=0;						// с использование собственной функции
	 for (int i=0; i<nw-1; i++)	// сравнения слов (до пробела)
		if (my_strlen(qq[i])>my_strlen(qq[i+1])){
		   k++;
		   char *g=qq[i]; qq[i]=qq[i+1]; qq[i+1]=g;
		   }
	  } while(k);
 return qq; }

 void main(){
 char **pp=SortedWords("this is a text string of nine words");
 for (int i=0; pp[i]!=NULL; i++){
	for (int j=0;pp[i][j]!=0 && pp[i][j]!=' ';j++)
		putchar(pp[i][j]);
	putchar('\n');
	}
 delete []pp;
 }
