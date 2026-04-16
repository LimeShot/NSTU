#include <stdio.h>
#include <string.h>
//------------------------------------------------------83-02.cpp
// Линейная СД на основе дерева с двумя потомками
// Обход дерева сверху-вниз 
struct tree2{
	int cnt;		// Количество терминальных вершин в дереве
	char *s;
	tree2 *l,*r;	// Левый и правый потомки
	};		

// Создание терминальной вершины	
tree2 *create(char *ss){
	tree2 *q=new tree2;
	q->l = q->r = NULL;
	q->cnt = 1;
	q->s = ss;
	return q; }

// Добавление последним
void add(tree2 *&p, char *ss){
	if (p==NULL) p=create(ss);
	else p->cnt++, add(p->r,ss);
	}

void scan(tree2 *p, int level, int &ln){	// level  – уровень вершины (длина ветви)
	if (p==NULL) return;					// ln	- общий счетчик логических номеров
	printf("%d %d %s\n", ln, level, p->s);	// Сначала – вывод текущей вершины
	ln++;					
	scan(p->l, level+1,ln);					// Затем рекурсивный обход потомков
	scan(p->r, level+1,ln); }

// Поиск значения по логическому номеру
char *get_n(tree2 *p, int n){
	if (p==NULL) return NULL;		
	if (n >= p->cnt) return NULL;		// ЛН вне диапазона дерева
	if (n-- ==0) return p->s;			// ЛН = 0 для корневой вершины 
	if (p->l!=NULL){					// Если есть левое поддерево
		int ll=p->l->cnt;				// и ЛН-1 попадает в его диапазон ll
		if (n<ll) 	return get_n(p->l,n);	// Искать в нем с тем же ЛН-1
		n-=ll;							// Иначе отбросить число вершин
		}								// в левом поддереве и корень
	return get_n(p->r,n); }				// и искать остаток в правом поддереве

// Включение по логическому номеру
void insert(tree2 *&p, int n, char *ss){
	if (p == NULL) { p=create(ss); return; }
	if (n >= p->cnt) return;		
	p->cnt++;							// увеличивать счетчики в проходимых вершинах
	if (n-- ==0)						// если текущий ЛН=0 - вершина найдена,
		insert(p->l,0,p->s),p->s=ss; 	// данные из нее сносятся в левое поддерево 
	else								// с ЛН=0, а  на их место помещаются новые
	if (p->l!=NULL){					// Иначе - рекурсивный вызов аналогично алгоритму
		int ll=p->l->cnt;				// поиска по ЛН
		if (n<ll) { insert(p->l,n,ss); return; }
		n-=ll; }
	else insert(p->r,n,ss);} 

// Удаление по логическому номеру
char *remove(tree2 *&p, int n){		// ссылка на место размещения указателя
	if (p == NULL) return NULL;		// удаляемой вершины
	if (n >= p->cnt) return NULL;	// Для удаляемой вершины производится замещение
	p->cnt--;						// Если нет потомков - удаляется
	if (n-- ==0) {					// Если есть один потомок - удаляется, на ее место
		char *ss = p->s;			// помещается потомок
		tree2 *q;					// Иначе замещается значением, удаляемым по ЛН=0
									// из левого поддерева
		if (p->l==NULL && p->r==NULL) { delete p; p=NULL; return ss;}
		if (p->l==NULL) { q=p->r; delete p; p=q; return ss;  }
		if (p->r==NULL) { q=p->l; delete p; p=q; return ss;  }
		p->s = remove(p->l,0); return ss;
		}
	if (p->l!=NULL){				// Иначе - рекурсивный вызов аналогично алгоритму
		int ll=p->l->cnt;			// поиска по ЛН
		if (n<ll) return remove(p->l,n);
		n-=ll; }
	else return remove(p->r,n); }

// Балансировка поддерева в диапазоне логических номеров [a...b]
// Функция формирует сбалансированное поддерево из вершин интервала
tree2 *balance(tree2 *pp[], int a, int b){
	if (a>b) return NULL;		// диапазон "стянулся" в точку
	tree2 *q;
	if (a==b)					// в диапазоне - единственная вершина
		{ q=pp[a]; q->l=q->r=NULL; q->cnt=1; return q; }
	q=pp[a];					// первая вершина интервала - корневая
	int m=(a+b+1)/2;			// середина оставшегося интервала
	q->l=balance(pp,a+1,m-1);	// левое и правое поддерево сформировать
	q->r=balance(pp,m,b);		// рекурсивно из половинок интервала
	q->cnt=b-a+1;				// счетчик вершин в поддереве - 
	return q;					// ширина интервала
	}

// Обход дерева с заполнением массива указателей на вершины
void set(tree2 *pp[], tree2 *p, int &ln){
	if (p==NULL) return;		// ln - порядковый (логический) номер
	pp[ln++]=p;					// запомнить указатель на текущую вершину 
	set(pp,p->l,ln);			// рекурсивно выполнить для поддеревьев
	set(pp,p->r,ln); }

// Балансировка поддерева с использованием динамического массива указателей
void balance(tree2 *&ph){
	int sz=ph->cnt;				// создать динамический массив указателей
	tree2 **pp=new tree2*[sz];
	int ln=0;	
	set(pp,ph,ln);				// заполнить 
	ph=balance(pp,0,sz-1);		// вызвать рекурсивную функцию балансировки
	}							// для всего интервала


void main(){
tree2 *ph=NULL;
int k=0;
FILE *fd=fopen("83-02.cpp","r");
char c[80];
while(fgets(c,80,fd)!=NULL) { c[strlen(c)-1]=0; add(ph,strdup(c)); }
fclose(fd);
puts("-----------");k=0;scan(ph,1,k);
balance(ph);
puts("-----------");k=0;scan(ph,1,k);
insert(ph,0,"aaaaa");
insert(ph,0,"bbbbb");
insert(ph,1,"ccccc");
insert(ph,1,"ddddd");
insert(ph,0,"eeeee");
insert(ph,3,"fffff");
puts(remove(ph,4));
puts(remove(ph,4));
puts(remove(ph,1));
puts(remove(ph,0));
puts("-----------");k=0;scan(ph,1,k);
}