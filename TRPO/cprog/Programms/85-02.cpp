#include <stdio.h>
#include <string.h>
//------------------------------------------------------85-02.cpp
// Двоичное дерево
// Обход дерева слева - направо (левое - текущая - правое)
struct btree{
	int cnt;		// Количество вершин в дереве
	char *s;
	btree *l,*r;	// Левый и правый потомки
	};

// Создание терминальной вершины
btree *create(char *ss){
	btree *q=new btree;
	q->l = q->r = NULL;
	q->cnt = 1;
	q->s = ss;
	return q; }

// Поиск вершины по логическому номеру
btree *get_n(btree *p, int n){
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

// Поиск вершины с заданным значением -  рекурсия
btree *search(btree *p, char *key){
	if (p==NULL) return NULL;
	int k=strcmp(key,p->s);
	if (k==0) return p;
	if (k<0) return search(p->l,key);
	return search(p->r,key);
	}
// Поиск вершины с заданным значением -  цикл
btree *search1(btree *p, char *key){
	while(p!=NULL){
		int k=strcmp(key,p->s);
		if (k==0) return p;
		if (k<0) p=p->l;
		else p=p->r;
		}
	return NULL; }

// Включение с сохранием порядка
void insert(btree *&p, char *ss){
	if (p == NULL) { p=create(ss); return; }
	p->cnt++;
	if (strcmp(ss,p->s)<0)
		insert(p->l,ss);
	else
		insert(p->r,ss);
	}

// Удаление по логическому номеру
char *remove(btree *&p, int n){	// Возвращает удаляемую строку
	if (p == NULL) return NULL;
	if (n >= p->cnt) return NULL;
	p->cnt--;
	if (p->l!=NULL){
		int ll=p->l->cnt;
		if (n<ll) 	// В интервале левого - рекурсия
			return remove(p->l,n);
		n-=ll;
		}
	if (n-- ==0) {	// Удалить корневую
		char *ss = p->s;
		btree *q;	// p - ссылка на указатель
					// (адрс указателя на текущую вершину)
		if (p->l==NULL && p->r==NULL) 	// Нет потомков
			{ delete p; p=NULL; return ss;}
		if (p->l==NULL) 				// Только правый -
			{ q=p->r; delete p; p=q; 	// указатель на него
				return ss;  }			// на место указателя на текущий
		if (p->r==NULL) 				// Только левый -
			{ q=p->l; delete p; p=q; return ss;  }
		p->s = remove(p->r,0); 			// на место текущей строки
			return ss;					// [0] из правого поддерева
		}
	else		// В интервале правого - рекурсия
		return remove(p->r,n);
	}


// Балансировка дерева
btree *balance(btree *pp[], int a, int b){
	if (a>b) return NULL;
	btree *q;				// Интервал =1 - концевая вершина
	if (a==b) { q=pp[a]; q->l=q->r=NULL; q->cnt=1; return q; }
	int m=(a+b)/2;
	q=pp[m];				// Вершина в середине интервала
	q->l=balance(pp,a,m-1);	// Поддерево на левом интервале
	q->r=balance(pp,m+1,b);	// Поддерево на правом интервале
	q->cnt=b-a+1;
	return q;
	}
//  Обход с сохранением вершин в порядке возрастания
void scan(btree *qq[], btree *p, int &ln){
	if (p==NULL) return;
	scan(qq, p->l,ln);
	qq[ln++]=p;
	scan(qq,p->r,ln);
	}

void balance(btree *&ph){
	int sz=ph->cnt;
	btree **pp=new btree*[sz];
	int idx=0;
	scan(pp,ph,idx);
	ph=balance(pp,0,sz-1);
	}

// Обход дерева
void scan(btree *p, int level, int &ln){
	if (p==NULL) return;
	scan(p->l, level+1,ln);
	printf("l=%d n=%d cnt=%d :%s\n", level, ln, p->cnt, p->s);
	ln++;
	scan(p->r, level+1,ln);
	}

double sum (btree *p, int level){
	if (p==NULL) return 0;
	return level+sum(p->l,level+1)+sum(p->r,level+1);
	}

int main(){
btree *ph=NULL;
int k=0;
char c[80];
c[1]=0;
for(int i=0;i<=26;i++){
    c[0]='A'+i;
	insert(ph,strdup(c));
    }
puts("-----------");
k=0;scan(ph,1,k);
printf("mid=%lf\n",sum(ph,1)/ph->cnt);
getchar();
balance(ph);
puts("-----------");
k=0;scan(ph,1,k);
printf("mid=%lf\n",sum(ph,1)/ph->cnt);
getchar();
//-----------------------------------------------------------------
FILE *fd=fopen("revolution.txt","r");
ph=NULL;
while(fgets(c,80,fd)!=NULL) {
	c[strlen(c)-1]=0; 		// Затереть \n в конце "aaaaaa\n"
	insert(ph,strdup(c));
	}
fclose(fd);
puts("-----------");
k=0;scan(ph,1,k);
printf("mid=%lf\n",sum(ph,1)/ph->cnt);
getchar();
balance(ph);
puts("-----------");
k=0;scan(ph,1,k);
printf("mid=%lf\n",sum(ph,1)/ph->cnt);
getchar();
insert(ph,"Aaaaa");
insert(ph,"Bbbbb");
insert(ph,"Ccccc");
insert(ph,"Ddddd");
insert(ph,"Eeeee");
insert(ph,"Fffff");
puts(remove(ph,14));
puts(remove(ph,14));
puts(remove(ph,10));
puts(remove(ph,10));
puts("-----------");k=0;scan(ph,1,k);
getchar();
}
