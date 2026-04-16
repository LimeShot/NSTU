//------------------------------------------------------74-03.cpp
#include <stdio.h>
#include <string.h>

//----- Линейный кроссворд (перебор с обменом строк)
char *w[]={"sinus","prefix","setup","plintus","drop",NULL};
 // k - номер шага
 void step(int k){	
 if (w[k+1]==NULL) throw 1;					// Все слова выбраны - успех
 int l=0; if (k!=-1) l=strlen(w[k])-1;		// Выход из цепочки рекурсивынх вызовов
 for (int n=k+1; w[n]!=NULL;n++)			// через исключение
    if (k==-1 || w[k][l]==w[n][0]){			// совпадение символов или первое слово
		char *q=w[k+1]; w[k+1]=w[n]; w[n]=q;// Обмен найденного со следующим за...
		step(k+1);							// попытка вывести цепочку из нового слова
		q=w[k+1]; w[k+1]=w[n]; w[n]=q;		// Обратный обмен для продолжения поиска
		}}
 void main(){
	 try { step(-1); }
	 catch(int v){ 
		for (int s=0,i=0; w[i]!=NULL; i++){
		for(int j=0;j<s;j++) putchar(' ');
		s+=strlen(w[i])-1;
		puts (w[i]); 
	 }}}
