#include <stdio.h>
#include <string.h>
#include <conio.h>
//------------------------------------------------------83-01.cpp
// Линейная СД на основе дерева с двумя потомками
// и данными в концевых вершинах
struct tree2{
	int cnt;		// Количество терминальных вершин в дереве
	char *s;		// Данные - строка текста
	tree2 *l,*r;	// Левый и правый потомки
	};		

// Создание терминальной вершины	
tree2 *create(char *ss){
	tree2 *q=new tree2;
	q->l = q->r = NULL;
	q->cnt = 1;
	q->s = ss;
	return q; }

// Поиск вершины по логическому номеру
char *get_n(tree2 *p, int n){
	if (p==NULL) return NULL;
	if (n >= p->cnt) return NULL;		// Проверка на диапазон ЛН
	if (p->cnt==1) return p->s;			// Вершина концевая - найден
	int ll=p->l->cnt;					// ll - счетчик значений у левого потомка
	if (n<ll) return get_n(p->l,n);		// ЛН меньше, чем у левого - идти в него
	return get_n(p->r,n-ll);			// Иначе -  в правого потомка с вычетом ll
	}

// Добавление последним
void add(tree2 *&p, char *ss){
	if (p==NULL) p=create(ss);			// Для пустого дерева
	else {
		p->cnt++;						// Накручивать счетчики вершин
		if (p->r==NULL){				// Вершина концевая - 
			p->l=create(p->s);			// Значение текущей - левому потомку
			p->r=create(ss);			// Правому потомку  -новое
			}
		else add(p->r,ss);				// Не концевая - направо
		}
	}

// Включение по логическому номеру
void insert(tree2 *&p, int n, char *ss){
	if (p == NULL) { p=create(ss); return; }
	if (n >= p->cnt) return;			// Проверка на диапазон ЛН
	p->cnt++;
	if (p->r==NULL){					// концевая вершина -
		p->l=create(ss);				// сделать ее промежуточной
		p->r=create(p->s);				// текущие данные - правому
		return;							// потомку, новые - левому
		}
	int ll=p->l->cnt;					// ll - вершин у левого потомка
	if (n<ll) insert(p->l,n,ss);		// ЛН в диапазоне левого
	else insert(p->r,n-ll,ss);			// Иначе - перейти в правый с остатком
	}

// Удаление по логическому номеру
// результат - сообщение предку от концевой вершины
int remove(tree2 *p, int n){
	tree2 *q;
	if (p == NULL) return 0; 
	if (n >= p->cnt) return 0;
	p->cnt--;
	if (p->cnt==0) return 1;		// концевая вершина - "убей меня"
	int ll=p->l->cnt;				// вершин у левого потомка
	if (n<ll) {
		if (remove(p->l,n))			// Левый потомок просит удалить себя
			{
			delete p->l;			// Удалить левого потомка
			q=p->r;					// Совместить правого
			p->s=q->s;				// потомка с текущей
			p->l=q->l;				// вершиной
			p->r=q->r;
			delete q;
			}
		}
	else{
		if (remove(p->r,n-ll))		// Аналогично - просит правый
			{
			delete p->r;
			q=p->l;
			p->s=q->s;
			p->l=q->l;
			p->r=q->r;
			delete q;
			}
		}	
	return 0;						// Промежуточная вершина 
	}								// "не просит удалить себя"

// Балансировка дерева
tree2 *balance(tree2 *pp[], int a, int b){
	tree2 *q;
	if (a==b) {
		q=pp[a];			// В интервале одна вершина
		q->cnt=1;			// Возвратить ее как концевую
		q->r=q->l=NULL;
		return q;
		}
	q=new tree2;			// промежуточная вершина
	int m=(a+b)/2;			// середина интервала
	q->l=balance(pp,a,m);	// создать поддеревья 
	q->r=balance(pp,m+1,b);	// на половинах интервала
	q->cnt=b-a+1;			// Сформировать новый счетчик
	return q;				// Возвратить поддерево
	}

// Обход с заполнением ДМУ на концевые вершины
void create(tree2 *p, tree2 *pp[], int &ln){
	if (p==NULL) return;
	if (p->cnt==1){			// Концевая вершина - запомнить
		pp[ln++]=p;
		}
	else{
		create(p->l,pp,ln);	// Промежуточные - обход потомков
		create(p->r,pp,ln);
		delete p;			// Промежуточные - удаляются
		}}

void balance(tree2 *&ph){
	if (ph==NULL) return;
	int sz=ph->cnt;
	tree2 **pp=new tree2*[sz];
	int i=0;
	create(ph,pp,i);		// собрать концевые вершины в ДМУ
	ph=balance(pp,0,sz-1);
	delete pp;
	}

// Обход дерева - возвращает сумму длин путей
int scan(tree2 *p, int level, int &ln){
	if (p==NULL) return 0;
	if (p->l==NULL){
		printf("l=%d n=%d cnt=%d :%s\n", level, ln, p->cnt, p->s);
		ln++;
		return level;
		}
	else{
		printf("l=%d cnt=%d\n", level, p->cnt);
		return scan(p->l, level+1,ln)+scan(p->r, level+1,ln);
		}
}


void main(){
tree2 *ph=NULL;
int k=0;
FILE *fd=fopen("83-01.cpp","r");
char c[80];
while(fgets(c,80,fd)!=NULL) { c[strlen(c)-1]=0; add(ph,strdup(c)); }
fclose(fd);
puts("-----------");k=0;
printf("%d %d\n",scan(ph,1,k)/ph->cnt,ph->cnt); 
getch();
balance(ph);
puts("-----------");k=0;
printf("%d %d\n",scan(ph,1,k)/ph->cnt,ph->cnt); 
getch();
insert(ph,150,"aaaaa");
insert(ph,150,"bbbbb");
insert(ph,151,"ccccc");
insert(ph,151,"ddddd");
insert(ph,151,"eeeee");
insert(ph,150,"fffff");
if (remove(ph,150)) { delete ph; ph=NULL; }
if (remove(ph,150)) { delete ph; ph=NULL; }
if (remove(ph,150)) { delete ph; ph=NULL; }
puts("-----------");k=0;
printf("%d %d\n",scan(ph,1,k)/ph->cnt,ph->cnt); 
getch();
}