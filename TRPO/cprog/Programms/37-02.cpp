#include <stdio.h>

//--------------------------------------------37-02.cpp
// Пословная обработка: "1 шаг = 1 слово"
// "Грязная программа"
void  F1(char in[]){
int i=0,k;
while (in[i]==' ')i++;
while(in[i]!=0){		// 1 шаг = 1 слово
	// Начало слова
	printf("%d\n",i);
	while (in[i]!=' ' && in[i]!=0)
		i++;
	// Конец  слова
	while (in[i]==' ')i++;
	}
}



void main(){	
	char o[80];
	F1("   this is a text string");
	puts("");
}