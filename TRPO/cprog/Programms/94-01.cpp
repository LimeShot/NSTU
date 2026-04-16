#include <stdio.h>
#include <ctype.h>
//--------------------------------------------------------94-01.cpp
void more(FILE *fd){
long pp;					// Текущая позиция фрагмента повторения
char c; int n=0;			// Количество повторов
while(1){
	pp=ftell(fd);			// Запомнить текущую позицию
	char c=getc(fd);			//
	if (!isdigit(c)) break;		//
	n=n*10+c-'0';			// Накопление константы
	}
if (n==0) n=1;				// Отсутствие константы - повторить 1 раз
while(n--!=0){				// Повторять фрагмент
	fseek(fd,pp,SEEK_SET);	// Вернуться на начало
	while 	((c=getc(fd)) !=EOF && c!=')'){
		if (c=='(') more(fd);	// Вложенный фрагмент -
		else				// рекурсивный вызов после '('
			putchar(c);		// Перечитать фрагмент до ')'	
		}
}
}
void main(){
FILE *fd=fopen("94-01.txt","r"); more(fd); fclose(fd);
}

