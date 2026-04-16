//-----------------------------------------------103-02.cpp
// Переопределение операций распределения памяти
#include <stdio.h>
#include <string.h>
#include <malloc.h>

class memory{
	char *pa;
	int sz0;
public:
memory(int sz){
	pa=new char[sz];
	*(int*)pa=sz-sizeof(int);		// Размерность свободного куска
	sz0=sz;
	}
~memory(){ delete []pa; }
//--------------------------------------------------------------
// поиск строго подходящего или отрезание от первого
void *malloc(int sz){						
	char *p=pa;
	int lnt;
	while(p<pa+sz0){
		lnt=*(int*)p;
		if (lnt<0)					// Занятый блок - пропустить
			p+=-lnt+sizeof(int);
		else{
			if (sz==lnt) {
				*(int*)p=-lnt;		// Занять блок
				return p+sizeof(int);
				}
			p+=lnt+sizeof(int);
			}
		}
	lnt=*(int*)pa;					// Отрезать от первого
	if (sz+sizeof(int)>lnt) 
		return NULL;
	lnt-=sz+sizeof(int);
	*(int*)pa=lnt;					// Остаток длины первого блока
	p=pa+lnt+sizeof(int);			// "Хвост"- выделенный блок
	*(int*)p=-sz;
	return p+sizeof(int);
	}
//--------------------------------------------------------------------
void show(){						
	puts("---------------------------------------");
	char *p=pa;
	int lnt;
	while(p<pa+sz0){
		lnt=*(int*)p;
		if (lnt<0){					// Занятый блок - пропустить
			lnt=-lnt;
			printf("busy:");
			}
		else printf("free:");
		printf(" addr=%8d sz=%d\n",p,lnt);
		p+=lnt+sizeof(int);
		}
	}
//---------------------------------------------------------------------
void free(void *q0){
	char *q=(char*)q0-sizeof(int);
	int lnt=*(int*)q;					// Извлечение длины
	lnt=-lnt;
	char *pr=NULL,*p=pa;
	while(p!=q){
		int ln=*(int*)p;
		if (ln<0) ln=-ln;
		pr=p;
		p+=ln+sizeof(int);
		}								// Просмотр до предыдущего
	*(int*)q=lnt;						// Освободить блок
	if (*(int*)pr>0) {
		*(int*)pr+=lnt+sizeof(int);		// Склеить с предыдущим
		p=pr;
		}
	lnt=*(int*)p;
	q=p+lnt+sizeof(int);
	if (q<pa+sz0 && *(int*)q>0)			// Есть следующий и он свободен
		*(int*)p+=*(int*)q+sizeof(int);	// Склеить со следующим
	}
};

//-----------------------------------------------
// Класс степенного полинома с собственным распределением памяти
class poly{
	int n;						// степень полинома
	double *pd;					// динамический массив коэффициентов
void load(int n0, double p[]){
	n=n0;					// закрытый метод загрузки массива
	pd=(double*)MEM.malloc(sizeof(double)*(n+1));
	for(int i=0;i<=n;i++)
		pd[i]=p[i]; }
void extend(int n1){		// увеличение размерности полинома
	int i;
	if (n1<=n) return;
	double *pd1=(double*)MEM.malloc(sizeof(double)*(n1+1));
	for (i=0;i<=n;i++) pd1[i]=pd[i];
	for (;i<=n1;i++) pd1[i]=0;
	n=n1;
	MEM.free(pd);			// удалить старый массив
	pd=pd1;					// считать новый за старый
	}
void normalize(){			// нормализация - удаление лишних 0
	while(n>0 && pd[n]==0) n--;
	}						// память не перераспределяется
public:
static memory MEM;			// статический объект класса MEM - ДРП
poly(){						// "пустой" полином - нулевой степени
	n=0;					// с нулевым коэффициентом
	pd=(double*)MEM.malloc(sizeof(double));
	pd[0]=0;}
poly(int m){				// полином заданной степени
	n=m;					// с нулевыми коэффициентами
	pd=(double*)MEM.malloc(sizeof(double)*(n+1));
	for(int i=0;i<=n;i++)
		pd[i]=0; }
poly(int n0,double p[]){	// конструктор из массива коэффициентов
	load(n0,p); }
poly(poly &T){				// конструктор "объект из объекта"
	load(T.n, T.pd); }		// (конструктор копирования)
~poly(){ MEM.free(pd); }
//-------------------------------------------------------
// переопределение операторов new и delete в классе
static void *operator new(size_t sz){
		return MEM.malloc(sz);
		}
static void operator delete(void *p){
		MEM.free(p);
		}
//----------------------------------------------------------
double &get(int k){			// ссылка на коэффициент полинома
	static double foo=0;	// вне пределов массива - ссылка
	if (k<0 || k>n) return foo;
	return pd[k];			// на "левую" статическую переменную
	}
void show(){				// вывод в "удобочитаемом" виде
	for (int i=n,k=0; i>=0; i--){
		if (pd[i]==0) continue;
		if (k++!=0 && pd[i]>0) printf("+");
		printf("%3.1lf",pd[i]);
		if (i>0) printf("*X");
		if (i>1) printf("^%d",i);
		}
	printf("\n");
	}
void add(poly &T){			// Сложение - добавление второго к текущему
	extend(T.n);			// Увеличить до размерности второго
	for (int i=0;i<=T.n;i++) pd[i]+=T.pd[i];
	normalize();
	}
void mul(poly &T){			// Умножение 
	poly R(n+T.n+1);		// Вспомогательный объект - сумма размерностей
	for (int i=0;i<=n;i++)	// Добавление частичных произведений всех пар
	for (int j=0;j<=T.n;j++)
		R.pd[i+j]+=pd[i]*T.pd[j];
	int c; double *d;		// Обмен содержимым текущего и вспомогательного
	c=n; n=R.n; R.n=c;
	d=pd; pd=R.pd; R.pd=d;
	}
void diff(){				// Производная от полинома (k*x^n)' = k*n*x^(n-1)
	for (int i=0;i<n;i++)
		pd[i]=pd[i+1]*(i+1);
	n--;
	}
int compare(poly &T){		// Сравнение полиномов
	int k=0;
	poly R(*this);			// Копия текущего
	for (int i=R.n;i>=0;i--) 
		R.pd[i]=-R.pd[i];	// Инвертирование коэффициентов
	R.add(T);				// Вычитание из второго - текущего
	R.normalize();
	if (R.n==0 && R.pd[0]==0)
		return 0;			// Результат - нулевой полином = равны
	if (R.pd[R.n]<0) return 1;
	return -1;				// Иначе - знак старшего коэффициента
	}
//-----------------------------------------------------------
// переопределение операций
};


memory poly::MEM(10000);

void main(){
	double A[]={1,-2,3,-4},B[]={5,3,6};
	poly a1(3,A),a2(2,B),*p;
	poly::MEM.show();
	p=new poly(3,A);
	poly::MEM.show();
	delete p;
	poly::MEM.show();
	}

