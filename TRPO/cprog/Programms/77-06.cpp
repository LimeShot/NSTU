#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//----------------------------------------------77-06
// Лексикографическая сортировка массива
// Разряд - десятичная цифра 
// Определение кол-ва цифр в чиcле
int dig_len(int dig,int k){
	int i;
	for( i=0;(dig/=k)!=0;i++);
	return i+1;}
// Выделение цифры на позиции num
int get_dig(int v,int num,int k){
	while(num--!=0) v/=k;
	return v%k;}

int cnt=0;
void sort(int A[], int n, int k){	
int i,max_len;
for (i=0,max_len=0;i<n;i++){		// определение максимальной разрядности
	int l=dig_len(A[i],k);
	if (l>max_len) max_len=l;
	}
int **B=new int*[k],*I=new int[k];	// создание "карманов" - ДМУ
for (i=0;i<k; i++) B[i]=new int[n];	
for(int raz=0;raz < max_len; raz++)
	{
	int i,j,m;
	for (m=0,i=0;i<k;i++) I[i]=0;	// Обнудение счетчиков
	for(i=0;i<n;i++)
		{
		cnt++;
		int v=get_dig(A[i],raz,k);	// Распределение по карманам
		B[v][I[v]++]=A[i];			// по очередному разряду
		}
	for (i=0;i<k;i++)
		{
		printf("\n[%d] ",i);
		for (j=0;j<I[i];j++,cnt++,m++) {
			A[m]=B[i][j];			// Слияние карманов
			printf("%d ",A[m]);
			}
		}
	}
}


void main()
{
int i,n=20,*A=new int[n];
srand(time(NULL));
for(i=0;i<n;i++) A[i]=rand()%10000+1;
sort(A,n,10);	
puts("");
for(i=0;i<n;i++) printf("%d ",A[i]);
printf("\ncnt=%d\n",cnt);
}