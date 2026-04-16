//-----------------------------------------------------62-03.cpp
//--- Матрица произвольной  размерности - массив указателей на массивы
#include <stdio.h>
double **load(char nm[], int &n, int &m){
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return NULL;
	fscanf(fd,"%d%d",&n,&m);		// Чтение размерностей
	double **pp=new double*[n];		// Создание ДМУ по первой размерности
	for(int i=0;i<n;i++){
		pp[i]=new double[m];			// Создание линейных ДМ (строк)
		for(int j=0;j<m;j++) fscanf(fd,"%lf",&pp[i][j]);
		}
	fclose(fd);
	return pp;}
double sum(double **p , int n, int m ){ 
double s=0 ;
for (int i=0; i<n; i++)
	for (int j=0; j<m; j++) s+=p[i][j];
return s; }
void destroy(double **pp,int n){
	for (int i=0;i<n;i++) delete []pp[i];
	delete []pp;
	}
void main(){
int n1,m1;
double **pp=load("62-03.txt",n1,m1);
if (pp!=NULL) printf("sum(%d,%d)=%2.0lf\n",n1,m1,sum(pp,n1,m1)); 
destroy(pp,n1);
}
