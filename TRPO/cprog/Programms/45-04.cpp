#include <stdio.h>
//-------------------------------------------------45-04.cpp
// Чтение последовательностей различных форматов
double F1(char c[]){
	FILE *fd=fopen(c,"r");		// Открыть файл
	if (fd==NULL) return 0;
	double s=0;
	while(1){					// Цикл чтения последовательности
		int v;
		double dd;
		fscanf(fd,"%d",&v);		// Читать очередное значение
		if (v==0) break;		// Ограничитель - 0 
		if (v>0) s+=v;			// Если >0 - добавить к сумме
		else{					// Если <0 - читать следующее
			fscanf(fd,"%lf",&dd);
			s+=dd;				// за ним - вещественное
			}}
		fclose(fd); return s;}
//----------------------------------------------
int F2(char c[],int d[]){
	FILE *fd=fopen(c,"r");		// Открыть файл
	if (fd==NULL) return 0;
	double s=0;
	int n=0;
	while(1){					// Цикл чтения последовательности
		int v;
		double dd;
		fscanf(fd,"%d",&v);		// Читать очередное значение
		if (v==0) break;		// Ограничитель - 0
		if (v>0) d[n++]=v;		// Если >0 - добавить в массив
		else{
			int k=-v;			// Если <0 - счетчик повторений
			fscanf(fd,"%d",&v);	// Следующее значение - повторяющееся
			while(k--!=0)		// Цикл копирования повторяющегося
				d[n++]=v;		// значения
			}}
		fclose(fd); return n;}
void main(){
	printf("F1=%lf\n",F1("45-041.txt"));
	int dd[100];
	int k=F2("45-042.txt",dd);
	for (int i=0; i<k; i++) printf("%d ",dd[i]);
	}