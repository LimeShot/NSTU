#include <stdio.h>
//--------------------------------------------------------104-04.cpp
// Класс неориентированного графа, представленного массивом 
// заголовков списков смежных вершин
//--- Полный рекурсивный обход графа, таблица списков смежных вершин
class graph{
	struct link{		// Элемент списка смежных вершин
		int v2,lnt; 
		link *next;
		link(int vv,int ll){ v2=vv; lnt=ll; next=NULL; }
		};
public:
//--------------------------------------------------------------
// Итератор для списка смежных вершин
	struct iterator{
		link *cur;		// указатель на элемент списка
		iterator(link *p0){ cur=p0;}
						// Установка на последующий элемент
int next(int &v2, int &lnt2){
	if (cur==NULL) return 0;	
	v2=cur->v2; lnt2=cur->lnt;
	cur=cur->next;
	return 1; }
	};
// Метод, создающий итератор дл списка ребер k-ой вершины
iterator first(int k){
	return iterator(M[k]);
	}
private:
	int	n;				// размерность графа
	link **M;			// динамический массив указателей на списки
	int *D;
public:
	operator int(){ return n; }
graph(int n0){			// констуктор пустого графа
	n=n0;
	M=new link*[n];
	for (int i=0; i<n;i++) M[i]=NULL;
	}
void add(int k1,int k2, int v){
	link *q=new link(k1,v);	// добавление ребра
	q->next=M[k2]; M[k2]=q;	// добавление в список первой вершины
	q=new link(k2,v);		// добавление в список второй вершины
	q->next=M[k1]; M[k1]=q;
	}
void scan(){				// полный рекурсивный обход графа
	D=new int[n];			// массив отметок обхода вершин
	for (int i=0; i<n;i++) D[i]=0;
	scan_v(0);
	delete []D;
	}
private:					// рекурсивный метод обхода вершины
void scan_v(int i){
	D[i]=1;					// отметить верштну
	int v2,l2;
	graph::iterator II=first(i);	
	while(II.next(v2,l2))	// Цикл просмотра соседей для текущей вершины
		if (D[v2]==0) {		// просмотр списка ребер
			printf("%d-%d[%d]\n",i,v2,l2);
			scan_v(v2); }	// если не отмечена - рекурсивный вызов
	D[i]=0;}
public:
//-----------------------------------------------------------
// Конструктор из матрицы (массив указателей на строки)
	graph (int *pp[],int n0){
	n=n0;
	int i,j;
	M=new link *[n];
	for (i=0;i<n;i++) M[i]=NULL;
	for (i=0;i<n;i++)		// Создать ребра только
		for (j=0;j<i;j++)	// для ненулевых значений матрицы
		if (pp[i][j]!=0) add(i,j,pp[i][j]);
	}
private:
void destroy(){				// Разрушение структуры данных
	for (int i=0;i<n;i++){
		link *p=M[i],*q;
		while(p!=NULL){		// Освободить память для списка
			q=p; p=p->next; delete q;
			}}
	delete []M;				// Освободить пмять для ДМУ
	}
public:
~graph(){ destroy(); }		// Деструктор
void load(char nm[]){
	FILE *fd=fopen(nm,"r");
	if (fd==NULL) return;
	destroy();
	fscanf(fd,"%d",&n);
	int i,j;
	M=new link *[n];
	for (i=0;i<n;i++) M[i]=NULL;
	for (i=0;i<n;i++)
		for (j=0;j<i;j++){
			int vv;
			fscanf(fd,"%d",&vv);
			if (vv!=0) add(i,j,vv);
		}
	}
};

//-------------------------------------------------------------------
void main(){
int a00[]={ 0,  5, 8, 0, 0, 0, 0};
int a01[]={ 5,  0, 0,12, 0, 9, 0};
int a02[]={ 8,  0, 0, 0, 8, 4, 2};
int a03[]={ 0, 12, 0, 0, 3, 6, 0};
int a04[]={ 0,  0, 8, 3, 0, 0, 7};  
int a05[]={ 0,  9, 4, 6, 0, 0, 0};
int a06[]={ 0,  0, 2, 0, 7, 0, 0};
int *A1[]={a00,a01,a02,a03,a04,a05,a06};
	graph GG(A1,7);
	GG.scan();
	puts("--------------------------");
	GG.load("86-011.txt");				// Алгоритм Дейкстры
	int N=GG;							// для поиска кратчайших путей
	int i,k,j;
	int *P=new int[N];
	int *D=new int[N];
	for (i=0;i<N;i++) P[i]=0,D[i]=100000;
	D[0]=0;
	while(1){
		for (k=-1,i=0;i<N;i++){
			if (P[i]==1) continue;		// В облаке
			if (k==-1 || D[i] < D[k]) 
				k=i;					// Ближайшая вне облака 
			}
		if (k==-1) break;
		P[k]=1;
		printf("put=%d[%d]\n",k,D[k]);
		int v2,l2;
		graph::iterator II=GG.first(k);	// Цикл просмотра соседей для текущей вершины
		while(II.next(v2,l2)){
			if (D[k] + l2 < D[v2])		// - если расстояние уменьшается
				D[v2] = D[k] + l2;
			}
		}
	puts("-----------------------------------");
	for (i=0;i<N;i++) printf("%2d ",D[i]);
	printf("\n");
	}

