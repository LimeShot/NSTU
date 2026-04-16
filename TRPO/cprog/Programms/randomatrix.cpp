#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//----------------Генерация матрицы
// n - размерность
// l - кол-во ветвей на 1 вершину
// v - диапазон значений
int **randomatrix(int N, int l,int v){
	srand(time(NULL));
	int **M=new int*[N+1];
	M[N]=NULL;
	for (int i=0; i<N;i++){
		M[i]=new int[N];
		for (int j=0;j<N;j++) M[i][j]=0;
		}
	int st=N*N;
	for(int k=0;k<N*l/2;k++){
		if (st--==0) break;
		int ii=rand()%N;
		int jj=rand()%N;
		if (ii==jj) { k--; continue; }
		if (M[ii][jj]!=0) { k--; continue; }
		M[ii][jj]=M[jj][ii]=rand()%v+1;
		}
	return M;
	}

void print(int **M){
	int i,j;
	int N;
	for(N=0;M[N]!=NULL;N++);
	for (i=0; i<N;i++){
		for (j=0;j<N;j++)
			printf("%2d ",M[i][j]);
		printf("\n");
		}
	}

int **load(char nm[], int &N){
	int i,j;
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return NULL;
	fscanf(fd,"%d",&N);
	int **M=new int*[N+1];
	M[N]=NULL;
	for (i=0; i<N;i++){
		M[i]=new int[N];
		M[i][i]=0;
		}
	for (i=0; i<N;i++){
		for (j=0;j<N;j++)
			{
			fscanf(fd,"%d",&M[i][j]);
			M[j][i]=M[i][j];
			}
		}
	fclose(fd);
	return M;
	}

void save(int **M, char nm[]){
	int i,j;
	FILE *fd=fopen(nm,"w");
	if (fd==NULL) return;
	int N;
	for(N=0;M[N]!=NULL;N++);
	fprintf(fd,"%d\n",N);
	for (i=0; i<N;i++){
		for (j=0;j<N;j++)
			fprintf(fd,"%d ",M[i][j]);
		fprintf(fd,"\n");
		}
	fclose(fd);
	}

void main(){
	int nn=0;
	int **M=randomatrix(10,3,1);
	print(M);
	save(M,"a.txt");
	M=load("a.txt",nn);
	print(M);
	getchar();
	}