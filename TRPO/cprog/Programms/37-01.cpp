#include <stdio.h>

//--------------------------------------------37-01.cpp
// "Склеивание" повтояющихся символов строки.
// Использование счетчика повторений
// "Грязная программа"
void  F1(char in[]){
int i,k;
for (i=0,k=1; in[i]!=0;i++)
	if (in[i]==in[i+1]) k++;
	else
		{
		if (k>1) printf("%d",k);
		printf("%c",in[i]);
		k=1;
		}
}

//--------------------------------------------37-02.cpp
// Использование счетчика повторений
// Переписывание строки
void  F2(char in[], char out[]){
int i,j,k;
for (i=0,j=0,k=1; in[i]!=0;i++)
	if (in[i]==in[i+1]) k++;	// Пара различных - счетчик+1
	else{						// Пара одинаковых
		if (k>1) {				// Есть повторения
			int k1,j1;			// Записать k в виде символов-цифр
			for (k1=k; k1!=0;k1=k1/10,j++);
			for (j1=j-1; k!=0;k=k/10,j1--) 
				out[j1]=k%10+'0';
			}
		out[j++]=in[i];			// Переписать текущий символ
		k=1;
		}
	out[j]=0;}					// Добавить "конец строки"


//--------------------------------------------37-03.cpp
// Отдельный цикл "измерения" повторений
// "Грязная программа"
void  F3(char in[]){
int i,j,k;
for (i=0; in[i]!=0;){
	for(k=1;in[i]==in[i+k];k++);// Измерить длину цепочки
	if (k>1) printf("%d",k);
	printf("%c",in[i]);
	i=i+k;
	}
}
	
//--------------------------------------------37-04.cpp
// Отдельный цикл "измерения" повторений. "Сжатие строки"
void  F4(char in[]){
int i,j,k;
for (i=0; in[i]!=0;){
	for(k=1;in[i]==in[i+k];k++);// Измерить длину цепочки
	if (k==1) i++;				// Нет повторения - пропустить
	else{
		j=i+k;				// Запомнить начало "хвоста"
		int k1,j1;			// Записать k в виде символов-цифр
		for (k1=k; k1!=0;k1=k1/10,i++);
		for (j1=i-1; k!=0;k=k/10,j1--) 
			in[j1]=k%10+'0';// Затереть символы цифрами числа
		i++;				// "Оставить" один символ
		j1=i;				// i - начало следующего шага
		do {in[j1++]=in[j];}// j1 - куда, j - откуда
			while(in[j++]!=0);
		}
	}
}	


void main(){	
	char o[80];
	F1("abcdddddddddddddddefffffffffffffffffffffg");
	puts("");
	F2("abcdddddddddddddddefffffffffffffffffffffg",o);
	puts(o);
	F3("abcdddddddddddddddefffffffffffffffffffffg");
	puts("");
	char ii[]="abcdddddddddddddddefffffffffffffffffffffg";
	F4(ii);
	puts(ii);
}