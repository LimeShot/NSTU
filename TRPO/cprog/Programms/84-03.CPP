#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//------------------------------------------------------84-03.cpp
//------- Дерево, упорядоченное в глубину.
struct vtree{
	int val;			// значение
	vtree *l,*r;		// потомки
	int cnt;			// счетчик вершин
};

// Поиск значений, не превышающих заданное
// Рекурсивный обход с ограничением глубины
void search(vtree *p,  int high, int &n){
 if (p==NULL) return;
 n++;									// Счетчик пройденных вершин
 if (p->val <= high){
	printf("v=%d\n",p->val);
	search(p->r,high,n);
	search(p->l,high,n);
	}					
}

// Построение дерева - вытеснение в в поддерево 
// с минимальным количеством вершин
void insert(vtree *&p, int v){
 if (p==NULL){							// Найдено свободное место
	p=new vtree;						// Создать новую вершину
	p->l = p->r = NULL;
	p->cnt = 1;
	p->val = v;
	return;
	}
 p->cnt++;								// Увеличить счетчик вершин
 if (v < p->val){						// Вытеснение мешьшим большего
	 int c=p->val; p->val=v; v=c;		// из текущей вершины
	}
 if (p->l == NULL || p->r !=NULL && p->l->cnt < p->r->cnt) 
	 insert(p->l,v);					// Выбор свободной ветви или
 else									// поддерева с минимумом вершин
	 insert(p->r,v);
}

void scan(vtree *p, int level){
 if (p == NULL) return;
 for (int i=1; i<level;i++) printf(" ");	// отступ-пропорционально глубине
 printf("v=%d\n",p->val);
 scan(p->l,level+1);
 scan(p->r,level+1);
}
 
void main(){
vtree *ph=NULL;
int n=127,m=0,k=0;
srand(time(NULL));
for (int i=0; i<n; i++) {
	int vv=rand()%n;
	if (vv < n/10  && vv>k) k=vv;
	insert(ph,vv);
	}
scan(ph,1);
search(ph,k,m);
printf("count=%d\n",m);
}
