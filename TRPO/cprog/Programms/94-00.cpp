#include <stdio.h>
//-------------------------------------------------94-00.cpp
// Формирование ДАМПА для чтения файла
void main(){
FILE *fd=fopen("94-00.dat","wb");
char k=10,m=4;
short A[10]={6,3,7,3,4,8,300,5,23,64};
int   B[4]={6,3,7,3};
long p=0,offset;
fwrite(&p,sizeof(long),1,fd);	// Занять место под указатель
fwrite(&k,1,1,fd);				// Записать один байт - счетчик
fwrite(A,sizeof(short),k,fd);	// Записать массив коротких целых (2B)
p=ftell(fd);					// Получить значение указателя	
fwrite(&m,1,1,fd);				// Записать один байт - счетчик
fwrite(B,sizeof(int),m,fd);	// Записать массив целых
fseek(fd,0,SEEK_SET);			// К началу файла
fwrite(&p,sizeof(long),1,fd);	// Обновить указатель на второй массив
fclose(fd);
}