#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 100
int A[N][N];				// матрица расстояний до соседей
int W[N];					// матрица расстояний от начального

template <class T, int sz>
class queue{
	T area[sz];
	int fst,lst;
public:
	int size(){ return lst>=fst ? lst-fst : fst+N-lst; }
	queue(){ fst=lst=0; }
	T out(){
		static T null;
		if (fst==lst) return null;
		null=area[fst++];
		fst%=sz;
		return null;
		}
	void in(T v){ area[lst++]=v; lst%=sz; }
	};

int random(int m){
	return ((double)m)*rand()/RAND_MAX;
	}

void create(double prc){
   srand( (unsigned)time( NULL ) );
   int i,j,k;
   for (i=0;i<N;i++)
		for (j=0;j<N;j++) A[i][j]=0;
   for(k=0; k<prc*N*N;k++){
		i=random(N);
		j=random(N);
//		j=(i+random(N/2))%N;
		if (i==j || A[i][j]!=0) { k--; continue; }
		A[i][j]=A[j][i]=random(30);
		}
	}


void main(){
int nc=0,ncmp=0,i;
for (i=0;i<N;i++) W[i]=-1;
create(0.05);
int n0=0;					// Начальная вершина и расстояние до самой себя =0
W[n0]=0;
queue<int,100> Q;			// Очередь номеров вершин
Q.in(n0);					// Поместить исходную в очередь
while(Q.size()!=0){			// Пока очередь не пуста
	int ni=Q.out();			// Извлечь номер очередной вершины
	if (W[ni]==-1) continue; // ошибка - она еще не пройдена
	nc++;					// подсчет трудоемкости алгоритма
	for (i=0;i<N;i++)		// проверка всех соседей
	if (A[ni][i]!=0){		// Это неотмеченный сосед 
		if (W[i]==-1 || W[i]>W[ni]+A[ni][i])
			{				//или сосед с более длинным путем
			printf("city %2d => %2d way %2d => %2d \n",ni,i,W[i],W[ni]+A[ni][i]);
			W[i]=W[ni]+A[ni][i]; // Уменьшить длину пути до него
			Q.in(i);		// Поместить в очередь (вторая волня)
			}
		ncmp++;				// подсчет трудоемкости алгоритма
		}
	}
for (i=0;i<N;i++) printf("%d ",W[i]);
printf("\nnc=%d ncmp=%d\n",nc,ncmp);
}

