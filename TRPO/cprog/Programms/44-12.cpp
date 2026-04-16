//------------------------------------------------------44-12.cpp
//---- Поиск слова максимальной длины посимвольная обработка
	   // Функция возвращает индекс начала слова или 1, если нет слов
 int find(char s[]) {
 int i,n,lmax,imax;
	  for (i=0,n=0,lmax=0,imax=-1; s[i]!=0; i++){
	  if (s[i]!=' ') n++;            // символ слова увеличить счетчик
		   else {                    // перед сбросом счетчика
				if (n > lmax) { lmax=n; imax=i-n; }
		   n=0;                     // фиксация максимального значения
		   }}						// то же самое для последнего слова
 if (n > lmax) { lmax=n; imax=i-n; }
 return imax; }

 #include <stdio.h>
 void main(){
 char cc[]="aaaaaaa ss  ddddddddddd";
 printf("max word=%s\n",cc+find(cc));
 }
