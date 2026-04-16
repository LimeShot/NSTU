#include <stdio.h>
//-------------------------------------------------45-01.cpp
// "Перевертывание" идентификаторов
int isalpha(char cc){ 
	return cc>='a' && cc<='z' || cc>='A' && cc<='Z'; }
void main(){
	char c[100];
	int i,j;
	FILE *fd1=fopen("45-01.cpp","r");	// Чтение файла
	FILE *fd2=fopen("45-01.txt","w");	// Создание и запись файла
	if (fd1==NULL || fd2==NULL) return;
	while((c[0]=getc(fd1))!=EOF){		// Посимвольное чтение
		if (isalpha(c[0])){				// Первая буква слова
			i=1;						// Читать слово в массив
			char ss;
			while(isalpha(ss=getc(fd1))) c[i++]=ss;
			for(i--;i>=0;i--) putc(c[i],fd2);
			putc(ss,fd2);
			}							// Вывести в обратном порядке
		else putc(c[0],fd2);
		}
	fclose(fd1);
	fclose(fd2);
	}