#include <stdio.h>
//------------------------------------------------------105-02.cpp
//----- Шаблон СД - динамический массив указателей
// <class T> - параметр шаблона - класс T, внутренний тип данных
// vector - имя группы шаблонных классов
template <class T> class vector{
	int sz,n;			// Размерность ДМУ и кол-ко элементов
	T **obj;			// Массив указателей на параметризованные
public:                 // объекты типа T
	T *operator[](int); // оператор [int] возвращает указатель на
						// параметризованный объект класса T
	operator int();		// Возвращает текущее количество указателей
	int append(T*);     // Добавление указателя на объект типа T
	int index(T*);		// Поиск индекса хранимого объекта
	vector(int);		// Конструктор
	~vector(){ delete []obj; } 
	};					// Деструктор
//---- Встроенные функции (методы) шаблонного класса - тоже шаблоны
// параметр шаблона - класс T, внутренний тип данных
// имя функции-элемента или оператора - параметризировано
template <class T> vector<T>::operator int(){ return n; }

template <class T> T* vector<T>::operator[](int k){
	return k>=n ? NULL : obj[k]; }

template <class T> int vector<T>::index(T *pobj){
	for ( int i=0; i<n; i++)
		if (pobj == obj[i]) return i;
	return -1;}

template <class T> vector<T>::vector(int sz0){
	sz=sz0; n=0; obj=new T*[sz]; }


template <class T> int vector<T>::append(T *pobj){
 if (n>=sz) return 0;
 obj[n++]=pobj;
 return 1;}

 void main(){
 vector<int> A(5);
 int B[10]={6,4,8,4,8,0,4,76,98,10},i;
 for (i=0; i<10; i++) { A.append(&B[i]); }
 for (i=0; i<5; i++) printf("%d\n",*A[i]);
 printf("[%d]\n",A.index(&B[3]));
 }
