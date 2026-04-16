#include <iostream>
using namespace std;
//------------------------------------------------------105-04.cpp
// Шаблон односвязного списка
// Первый элемент - заголовок
//----------------------------------------------------------------------------------------
template <class T> class list{
	list<T> *next;				// Указатель на следующий в списке
	T data;						// Элемент списка хранит сам объект
	list(T& v)					// Скрытый конструктор для элементов с данными
		{ data=v; next=NULL; }
public:
	list() { next=NULL; }		// Конструктор для элемента - заголовка
	~list(){					// Деструктор рекурсивный
		if (next!=NULL) delete next;
		}						// рекурсивное удаление следующего
	void front(T& v){			// Включение в начало
		list *q=new list(v);
		q->next=next;
		next=q;
		}
	void end(T &v){				// Включение в конец
		list *p,*q=new list(v);	// Дойти до последнего
		for(p=this;p->nezt!=NULL;p=p->next);
		p->next=q;				// Следующий за последним - новый
		}
	void insert(T&,int);		// Включение по логическому номеру
	void insert(T&);            // Включение с сохранением порядка
	T remove(int);				// Извлечение по ЛН
	operator int(){				// Приведение к int = размер списка
		list *q; int n;
		for(q=next,n=0; q!=NULL; n++,q=q->next);
		return n;			
		}
	friend ostream &operator<<(ostream &O, list &R){
	list<T> *q;
	O << (int)R << endl;
	for (q=R.next; q!=NULL; q=q->next) O << q->data << endl;
	return O; 
	}
	friend istream &operator>>(istream&, list&);
 };                             // Переопределенный вывод в поток
//----------------------------------------------------------------------------------------
template <class T> void list<T>::insert(T &newdata,int n){
	list<T> *p,*q;
	p=new list<T>(newdata);
	for (q=this; q->next!=NULL && n!=0; n--,q=q->next);
	p->next=q-> next;			// Вставка после текущего
	q->next=p; }				// Отсчет от заголовка
//----------------------------------------------------------------------------------------
template <class T> void list<T>::insert(T &newdata){
 list<T> *p,*q;
 p=new list<T>(newdata);		// Сравнивать СО СЛЕДУЮЩИМ
 for (q=this; q->next!=NULL && newdata>q->next->data; q=q->next);
 p->next =q->next;				// Вставка ПОСЛЕ текущего
 q->next=p;}
//----------------------------------------------------------------------------------------
template <class T> T list<T>::remove(int n){
	list<T> *q,*p;				// Указатель на ПРЕДЫДУЩИЙ
	for (q=this; q->next!=NULL && n!=0; n--,q=q->next);
	T val;
	if (q->next==NULL) return val;	// Такого нет
	val=q->next->data;
	p=q->next; q->next=p->next;		// Исключить СЛЕДУЮЩИЙ из цепочки
	p->next=NULL;					// Для исключения рекурсивного деструктора
	delete p;
	return val;}
//----------------------------------------------------------------------------------------
template <class T> ostream &operator<<(ostream &O, list<T> &R){
	list<T> *q;
	O << (int)R << endl;
	for (q=R.next; q!=NULL; q=q->next) O << q->data << endl;
	return O; }
template <class T> istream &operator>>(istream &I, list<T> &R){
	T val; int n;
	I >> n;
	while(n--!=0){
		I >> val;
		R.front(val);
		}
	return I; }

 void main(){
 list<int> A; 
 int i,B[10]={5,34,8,4,6,8,4,78,4,8};
 for (i=0; i<10; i++) A.insert(B[i]);
 cout << "new value:"; cin >> i;
 A.insert(i);
 cout << A;
 cout << A.remove(2) << " "<< A.remove(5) << endl;;
 }
