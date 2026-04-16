#include <stdio.h>
#include <string.h>
#include <malloc.h>
//------------------------------------------------------85-03.cpp
// Двоичное дерево в массиве
struct btree{
	char **p;
	int sz;
//------------------------------------------------------
void init(){ sz=10; p=new char*[sz];
	for (int i=0;i<sz;i++) p[i]=NULL;
	}
//-- число вершин в поддереве
int	size(int n){
	if (n>=sz || p[n]==NULL) return 0;
	return 1+size(2*n)+size(2*n+1); }
//-- Обход дерева
void scan(int n, int level, int &ln){
	if (n>=sz || p[n]==NULL) return;
	scan(2*n,level+1,ln);
	printf("l=%d n=%d :%s\n", level, ln, p[n]);
	ln++;
	scan(2*n+1,level+1,ln);}
//-- Поиск вершины по логическому номеру
char *get_n(int m, int n){
	if (m>=sz || m>=size(n)) return NULL;
	int ll=size(2*n);
	if (m<ll) return get_n(m,2*n);
	m-=ll;
	if (m-- ==0) return p[n];
	return get_n(m,2*n+1);
	}
// Включение с сохранением порядка
void insert(int n, char *ss){
	if (n>=sz){
		sz*=2;
		p=(char**)realloc(p,sz*sizeof(char*));
		for (int i=sz/2;i<sz;i++) p[i]=NULL;
		}
	if (p[n] == NULL) { p[n]=ss; return; }
	if (strcmp(ss,p[n])<0)
		insert(2*n, ss);
	else
		insert(2*n+1, ss);}

//--- Балансировка дерева
void balance(char *pp[], int a, int b){
	if (a>b) return;
	int m=(a+b)/2;
	insert(1,pp[m]);
	balance(pp,a,m-1);
	balance(pp,m+1,b);
	}
//-- Обход дерева с сохранением в линейном массиве указателей
void set(char *pp[], int n, int &ln){
	if (n>=sz || p[n]==NULL) return;
	set(pp,2*n,ln);
	pp[ln++]=p[n];
	set(pp,2*n+1,ln);}

void balance(){
	int sz1=size(1),ln=0;
	char **pp=new char*[sz1];
	set(pp,1,ln);
	delete p;
	init();
	balance(pp,0,sz1-1);
	}
double sum(int n, int level){
	if (n>=sz || p[n]==NULL) return 0;
	return sum(2*n,level+1)+level+sum(2*n+1,level+1);
	}
int cnt(int n){
	if (n>=sz || p[n]==NULL) return 0;
	return cnt(2*n)+1+cnt(2*n+1);
	}
};


int main(){
btree X;
X.init();
int k=0;
FILE *fd=fopen("revolution.txt","r");
char c[80];
while(fgets(c,80,fd)!=NULL) { c[strlen(c)-1]=0; X.insert(1,strdup(c)); }
fclose(fd);
puts("-----------");
k=0;X.scan(1,1,k);
printf("mid=%lf\n",X.sum(1,1)/X.cnt(1));
X.balance();
puts("-----------");
k=0;X.scan(1,1,k);
printf("mid=%lf\n",X.sum(1,1)/X.cnt(1));
X.insert(1,"aaaaa");
X.insert(1,"bbbbb");
X.insert(1,"ccccc");
X.insert(1,"ddddd");
X.insert(1,"eeeee");
X.insert(1,"fffff");
puts("-----------");
k=0;X.scan(1,0,k);
for (k=X.size(1)-1;k>=0;k--) puts(X.get_n(k,1));
getchar();
}
