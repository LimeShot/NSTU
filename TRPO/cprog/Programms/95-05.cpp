#include <stdio.h>
//-------------------------------------------------95-05.cpp
// Формирование указателя в файле на массив данных
void main(){
FILE *fd=fopen("95-05.dat","wb");
char k=10,m=6;
short A[10]={6,3,7,3,4,8,300,5,23,64};
int   B[6]={6,3,7,3,56,34};
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
fd=fopen("95-05.dat","rb");
fread(&p,sizeof(long),1,fd);	// Читать указатель - адрес массива
fseek(fd,p,SEEK_SET);			// Позиционирование - переход по указателю
char m1;
fread(&m1,1,1,fd);				// Чтение байта - счетчика
int *qq=new int[m];				// Создание и чтение ДМ из файла
fread(qq,sizeof(int),m,fd);	
for (int i=0;i<m;i++) printf("%d ",qq[i]);
delete []qq;
}