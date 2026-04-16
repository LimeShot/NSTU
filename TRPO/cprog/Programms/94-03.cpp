#include <stdio.h>
//------------------------------------------------------94-03.cpp
//----- "Микрохирургическое" исправление счетчика
 void main() {
	FILE *fd; char cc, name[30]="94-03.txt";
	long POS; int cnt;
 	if ((fd=fopen(name,"r+"))==NULL) return;
	while(1){
		POS=ftell(fd);				// Запомнить адрес символа
		if ((cc=getc(fd))==EOF) break;
		if (cc>='0' && cc<='9'){	// Прочитана цифра
			fseek(fd,POS,SEEK_SET);	// Вернуться на 1 символ
			fscanf(fd,"%d",&cnt);	// и прочитать счетчик - 6 символов
			cnt++;					// Увеличить счетчик
			fseek(fd,POS,SEEK_SET);	// Вернуться на начало счетчика
			fprintf(fd,"%06d",cnt);	// и записать счетчик - 6 символов
			break;
			}
		}
	fclose(fd);}
