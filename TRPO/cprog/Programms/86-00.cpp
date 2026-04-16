#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **randomatrix(int n, int l,int v){
	int i,j,k;
	srand(time(NULL));
	int **M=new int*[n];
	for (i=0; i<n;i++){
		M[i]=new int[n];
		for (j=0;j<n;j++) M[i][j]=0;
		}
	for(k=0;k<n*l/2;k++){
		int ii=rand()%n;
		int jj=rand()%n;
		if (ii==jj) { k--; continue; }
		if (M[ii][jj]!=0) { k--; continue; }
		M[ii][jj]=M[jj][ii]=rand()%v+1;
		}
	for (i=0;i<n;i++){
		for (int j=0;j<n;j++) printf("%2d ",M[i][j]);
		puts("");
		}
	return M;
	}
//-----------------------------------------------------------
int **load_1(char nm[],int &N){
	int i,j;
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return NULL;
	fscanf(fd,"%d",&N);
	int **M=new int*[N];
	for (i=0; i<N;i++){
		M[i]=new int[N];
		M[i][i]=0;
		}
	for (i=0; i<N;i++){
		for (j=0;j<i;j++)
			{
			fscanf(fd,"%d",&M[i][j]);
			M[j][i]=M[i][j];
			}
		}
	fclose(fd);	return M; }
struct link2{ int v1,v2,lnt; };
struct link3{ 
	int v2,lnt; 
	link3 *next;
	link3(int vv,int ll){ v2=vv; lnt=ll; next=NULL; }
	};
//-----------------------------------------------------------
link2 *load_2(char nm[],int &N){
	int i,j;
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return NULL;
	fscanf(fd,"%d",&N);
	link2 *M=new link2[N];
	for (i=0; i<N;i++)
		fscanf(fd,"%d%d%d",&M[i].v1,&M[i].v2,&M[i].lnt);
	return M;
	}
//-----------------------------------------------------------
link3 **load_3(char nm[],int &N){
	int i,j;
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return NULL;
	fscanf(fd,"%d",&N);
	link3 **M=new link3*[N];
	for (i=0;i<N;i++) M[i]=NULL;
	for (i=1;i<N;i++){
		int k;
		fscanf(fd,"%d",&k);
		while(k-- > 0){
			int vv2,l2;
			fscanf(fd,"%d%d",&vv2,&l2);
			link3 *q=new link3(vv2,l2);
			q->next=M[i]; M[i]=q;
			q=new link3(i,l2);
			q->next=M[vv2]; M[vv2]=q;
			}
		}
	return M;
	}
