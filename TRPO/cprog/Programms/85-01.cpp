#include <stdio.h>
#include <string.h>
//------------------------------------------------------85-01.cpp
// Линейная СД на основе дерева с двумя потомками
// Обход дерева слева - направо (левое - текущая - правое)
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

// Поиск вершины по логическому номеру
tree2 *get_n(tree2 *p, int n){
	if (p==NULL) return NULL;
	if (n >= p->cnt) return NULL;
	if (p->l!=NULL){
		int ll=p->l->cnt;
		if (n<ll) return get_n(p->l,n);
		n-=ll;
		}
	if (n-- ==0) return p;
	return get_n(p->r,n);
	}

// Добавление последним
void add(tree2 *&p, char *ss){
	if (p==NULL) p=create(ss);
	else p->cnt++, add(p->r,ss);
	}

// Включение по логическому номеру
void insert(tree2 *&p, int n, char *ss){
	if (p == NULL) { p=create(ss); return; }
	if (n >= p->cnt) return;
	p->cnt++;
	if (p->l!=NULL){
		int ll=p->l->cnt;
		if (n<ll) { insert(p->l,n,ss); return; }
		n-=ll;
		}
	if (n-- ==0) {		
		if (p->l==NULL) 		// Левое пустое - в него
			p->l=create(ss);
		else  { insert(p->r,0,p->s); 
				p->s=ss; }		// Иначе - вытеснить текущее в правое поддерево с ЛН=0
		}
	else insert(p->r,n,ss);
	}

// Удаление по логическому номеру
char *remove(tree2 *&p, int n){
	if (p == NULL) return NULL; 
	if (n >= p->cnt) return NULL;
	p->cnt--;
	if (p->l!=NULL){
		int ll=p->l->cnt;
		if (n<ll) return remove(p->l,n);
		n-=ll;
		}
	if (n-- ==0) {
		char *ss = p->s;
		tree2 *q;
		if (p->l==NULL && p->r==NULL) { delete p; p=NULL; return ss;}
		if (p->l==NULL) { q=p->r; delete p; p=q; return ss;  }
		if (p->r==NULL) { q=p->l; delete p; p=q; return ss;  }
		p->s = remove(p->l,0); return ss;
		}
	else return remove(p->r,n);
	}
// Балансировка дерева
tree2 *balance(tree2 *pp[], int a, int b){
	if (a>b) return NULL;
	tree2 *q;
	if (a==b) { q=pp[a]; q->l=q->r=NULL; q->cnt=1; return q; }
	int m=(a+b)/2;
	q=pp[m];
	q->l=balance(pp,a,m-1);
	q->r=balance(pp,m+1,b);
	q->cnt=b-a+1;
	return q;	
	}

// Обход дерева с заполнением массива указателей на вершины
void set(tree2 *pp[], tree2 *p, int &ln){
	if (p==NULL) return;		// ln - порядковый (логический) номер
	set(pp,p->l,ln);			// рекурсивно выполнить поддерева
	pp[ln++]=p;					// запомнить указатель на текущую вершину 
	set(pp,p->r,ln); }

void balance(tree2 *&ph){
	int sz=ph->cnt;
	tree2 **pp=new tree2*[sz];
	int ln=0; set(pp,ph,ln);
	ph=balance(pp,0,sz-1);
	}

// Обход дерева
void scan(tree2 *p, int level, int &ln){
	if (p==NULL) return;
	scan(p->l, level+1,ln);
	printf("l=%d n=%d cnt=%d :%s\n", level, ln, p->cnt, p->s);
	ln++;
	scan(p->r, level+1,ln);
	}

void main(){
tree2 *ph=NULL;
int k=0;
FILE *fd=fopen("85-01.cpp","r");
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