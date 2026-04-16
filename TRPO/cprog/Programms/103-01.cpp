//-----------------------------------------------103-01.cpp
// Клас степенного полинома - переопределение операций
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class poly{
int n;						// степень полинома
double *pd;					// динамический массив коэффициентов
void load(int n0, double p[]){
	n=n0;					// закрытый метод загрузки массива
	pd=new double[n+1];		// - не всегда корректно вызывается
	for(int i=0;i<=n;i++)
		pd[i]=p[i]; }
void extend(int n1){		// увеличение размерности полинома
	int i;
	if (n1<=n) return;
	double *pd1=new double[n1+1];
	for (i=0;i<=n;i++) pd1[i]=pd[i];
	for (;i<=n1;i++) pd1[i]=0;
	n=n1;
	delete []pd;			// удалить старый массив
	pd=pd1;					// считать новый за старый
	}
void normalize(){			// нормализация - удаление лишних 0
	while(n>0 && pd[n]==0) n--;
	}						// память не перераспределяется
public:
poly(){						// "пустой" полином - нулевой степени
	n=0;					// с нулевым коэффициентом
	pd=new double[1];
	pd[0]=0;}
poly(int m){				// полином заданной степени
	n=m;					// с нулевыми коэффициентами
	pd=new double[n+1];
	for(int i=0;i<=n;i++)
		pd[i]=0; }
poly(int n0,double p[]){	// конструктор из массива коэффициентов
	load(n0,p); }
poly(poly &T){				// конструктор "объект из объекта"
	load(T.n, T.pd); }		// (конструктор копирования)
~poly(){ delete []pd; }		// деструктор
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
	poly R(n+T.n);			// Вспомогательный объект - сумма размерностей
	for (int i=0;i<=n;i++)	// Добавление частичных произведений всех пар
	for (int j=0;j<=T.n;j++)
		R.pd[i+j]+=pd[i]*T.pd[j];
	int c; double *d;		// Обмен содержимым текущего и вспомогательного
	c=n; n=R.n; R.n=c;
	d=pd; pd=R.pd; R.pd=d;
	normalize();
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
poly &operator=(poly &R){	// Присваивание
	if (&R==this)			// Присваивание "сам в себя"
		return *this;
	delete []pd;			// Разрушить левую часть (текущий)
	load(R.n,R.pd);			// Копия правой части (аналог КК)
	return *this;			// Возвращает ссылку на левый
	}
poly &operator=(double *d){	// Экзотическое присваивание массива со счетчиком
	delete []pd;			// Разрушить левую часть (текущий)
	int nn=d[0];			// В начале массива - размерность
	load(nn,d+1);			// дальше - данные
	return *this;			// Возвращает ссылку на левый
	}
poly operator+(poly T){		// Переопределение сложения - конвейер значений
	T.add(*this);			// Копия второго + первый
	return T;
	}
poly operator+(double *p){	// Переопределение сложения с массивом
//	poly R((int)*p,p+1);	// Создать объект из массива
//	return *this+R;			// p[0]-размерность, p[1]...p[n+1] - коэффициенты
	return *this+poly((int)*p,p+1);
	}
poly &operator-(poly T){	// Переопределение вычитания - конвейер значений
	for (int i=0;i<=T.n;i++)
		T.pd[i]=-T.pd[i];	// Инвертировать коэффициенты копии второго операнда
	T.add(*this);			// Копия второго + первый
	return T;
	}
poly operator*(poly &T){	// Умножение - конвейер значений
	poly R(n+T.n);			// Вспомогательный объект - сумма размерностей
	for (int i=0;i<=n;i++)	// Добавление частичных произведений всех пар
	for (int j=0;j<=T.n;j++)
		R.pd[i+j]+=pd[i]*T.pd[j];
	return R;				// Возврат локального объекта по значению
	}
poly operator*(int v){		// Умножение на целое - конвейер значений
	poly R(*this);
	for (int i=0;i<=R.n;i++)
		R.pd[i]*=v;
	return R; }
// переопределение операции int*poly - конвейер значений
friend poly operator*(int v, poly R){
	for (int i=0;i<=R.n;i++)	
		R.pd[i]*=v;
	return R;
	}
// Переопределение приведения к double* - 
// возвращение динамического массива
operator double*(){
	double *q=new double[n+2];
	q[0]=n;
	for (int i=0;i<=n;i++)
		q[i+1]=pd[i];
	return q;
	}
// Переопределение сравнений
int operator<(poly &T) {	return compare(T)<0; }	
int operator<=(poly &T){	return compare(T)<=0;}	
int operator>(poly &T) {	return compare(T)>0; }	
int operator>=(poly &T){	return compare(T)>=0;}	
int operator==(poly &T){	return compare(T)==0;}	
int operator!=(poly &T){	return compare(T)!=0;}	
// переопределение [] - ссылка на коэффициент
double &operator[](int k){	return get(k); }
// переопределение () с двумя параметрами - запись коэффициента
poly &operator()(int k, double v){
	get(k)=v; 
	return *this;}
// переопределение приведения к int - возвращает размерность
// operator int(){ return n; }
// переопределение вывода в поток - дружественный оператор
// конвейер ссылок
friend ostream &operator<<(ostream &O, poly T){		// Не всегда понимает  в выражениях !!!!!!!!!!!!!!!!!
	O << T.n << endl;								// без промежуточного присваивания
	for (int i=0;i<=T.n; i++) 
		O << T.pd[i] << " ";
	O << endl;
	return O;
	}
// переопределение ввода из потока - дружественный оператор
// конвейер ссылок
friend istream &operator>>(istream &O, poly &T){
	delete []T.pd;
	O >> T.n;
	T.pd=new double[T.n+1];
	for (int i=0;i<=T.n; i++) 
		O >> T.pd[i];
	return O;
	}
poly operator++(int){			// Переопределение poly++
	poly T(*this);
	pd[0]++;
	return T;
	}
poly operator++(){				// Переопределение ++poly
	pd[0]++;
	poly T(*this);
	return T;
	}
};


void main(){
	double A[]={1,-2,3,-4},B[]={5,3,6},C[]={3,1,2,3,4};
	poly a1(3,A),a2(2,B),a3,a4,a5;
	a3=a1;
	a4=C;
	a1.show();
	a2.show();
	a3.show();
	a4.show();
	a5=3*(a1+a2*a3);
	cout << 3*(a1+a2*a3) << a5;				
	ofstream F1("103-01.txt");
	F1 << a1 << a2 << a4 << 3*(a1+a2*a3);
	F1.close();
	ifstream F2("103-01.txt");
	F2 >> a4 >> a3 >> a2 >> a1;
	F2.close();
	a1[1]=15;
	a1(2,16);
	a1.show();
	// cout << "n=" << (int)a1 << endl;
	if (a1==a1) cout << "a1==a1\n";
	if (a1!=a2) cout << "a1!=a2\n";
	if (a1<a2)  cout << "a1<a2\n"; else cout << "a1>=a2\n";
	cout << "a1++ " << a1++;
	cout << "++a1 " << ++a1;
	cout << "a1+C[] " << a1+C;
	double *q=a1;
	for (int i=0; i<=q[0]; i++) cout << q[i+1] << " ";
	delete []q;
}