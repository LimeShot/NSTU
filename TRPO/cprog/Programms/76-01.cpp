#include <stdio.h>
//------------------------------------------------------76-01.cpp
//  алькул€тор арифметических выражений со ()
int calc(char *s){
int inside=0,n;				// уровень вложенности ()
char *p1=NULL,*p2=NULL,*q;	// указатели на символы операций + и * вне ()
for (q=s;*q!=NULL;q++)
	switch(*q)
		{
case '*':
case '/':	if (inside==0 && p2==NULL) p2=q; 
			break;				// «апоминание первой * вне ()
case '+':
case '-':	if (inside==0 && p1==NULL) p1=q; 
			break;				// «апоминание первго + вне ()
case '(':	inside++; break;
case ')':	inside--; break;
		}
if (p1!=NULL) p2=p1;			// «апоминание самой низкоприоритетной 
if (p2!=NULL){					// операции
	char c=*p2; *p2=0;			// "разрезать" строку на две части
	switch(c)					// и выполнить операцию над результатом
		{						// дл€ полученных частей
case '*':	return calc(s) * calc(p2+1);
case '/':	return calc(s) / calc(p2+1);
case '+':	return calc(s) + calc(p2+1);
case '-':	return calc(s) - calc(p2+1);
		}}
if (*s=='(' && *(q-1)==')'){	// выражение в () - сн€ть () 
	*(q-1)=0; return calc(s+1);	// и вызвать рекурсивно дл€ выражени€ в ()
	}							// накопление константы
for (n=0;*s>='0' && *s<='9';s++)
	n=n*10+*s-'0';
	return n;					// все остальное игнорируетс€
}

void main(){ char c[]="12*(5+5*6)"; printf("V=%d\n",calc(c)); }
