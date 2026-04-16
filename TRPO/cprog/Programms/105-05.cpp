#include <iostream>
using namespace std;
//------------------------------------------------105-05.cpp
// Шаблон циклического списка
template <class T>
class list
	{
	class elem{					// Внутрениий класс - 
	public:						// элемент списка
		T *pd;
		elem *next,*prev;		// Указатели
		int remove(){			// Метод - выкуси себя сам
			if (next==this)		// Единственный - ничего
				return 1;		// не делать
			next->prev=prev;	// Иначе - перекинуть
			prev->next=next;	// указатели соседей
			return 0;}			// друг на друга
		void before(elem *p){	// Включить себя перед p
			next=p;				// Следующий за собой - p
			prev=p->prev;		// Предыдущий - p->prev
			p->prev->next=this;	// Следующий за p->prev - сам
			p->prev=this;		// Предыдущий для p - сам
			}					// Конструктор
		elem(T *s) {pd=s; next=prev=this; }
		~elem() {}				// Деструктор пустой
		};
	elem *head;
public:
	void end(T *s){				// Включение в конец
		if (head==NULL) head=new elem(s);
		else (new elem(s))->before(head);
		}						// Не пустой - перед первым
	void front(T *s){			// В начало = в конец
		end(s); head=head->prev;// + перемещение заголовка
		}
	void sort();
	operator int();				// Приведение к int - длина списка
	friend ostream &operator<<(ostream&,list&);
	list() { head=NULL; }
	~list();
};
//---------------------------------------------
template <class T>	istream &operator>>(istream &I,list<T> &L){
		int n; I >> n;			// Ввод из потока - чтение счетчика
		T val;					// 
		while(n--!=0){I >> val; L.end(val); }
		}
//template <class T> int list<T>::elem::remove(){
//		if (next==this)		// Единственный - ничего
//			return 1;		// не делать
//		next->prev=prev;	// Иначе - перекинуть
//		prev->next=next;	// указатели соседей
//		return 0;}			// друг на друга
template <class T> list<T>::~list(){
	int k;
	do  {					// Цикл, пока не остался последний
		elem *q=head->prev;	// Последний
		k=q->remove();		// исключить
		delete q;			// и удалить
		} while(k==0);		// пока он не единственный
	}

template <class T> list<T>::operator int(){
	if (head==NULL) return 0;
	list<T>::elem *p; int n;// Обход списка, начиная со второго
	for (p=head->next,n=1; p!=head;n++,p=p->next);
	return n;
	}

template <class T> ostream &operator<<(ostream &O,list<T> &L){
	int n=L;				// Приведение к int - длина списка
	list<T>::elem *p=L.head;
	O << n << endl;
	while(n--!=0){			// Просмотр списка и вывод
		O << *p->pd << endl;// хранимых объектов
		p=p->next;
		}
	return O; }

template <class T> void list<T>::sort(){
if (head==NULL || head->next==head) return;
	elem *q,*out,*p;		// Сортировка вставками
	q=head->prev;			// Создать из последнего элемента
	q->remove();			// выходной список
	q->next=q->prev=q;
	out=q;
	int k;
	do {					// Удалить последний элемент
		q=head->prev;
		k=q->remove();
		p=out;				// Просмотр выходного, пока 
		do	{				// не встретит больше себя
   		if (*q->pd < *p->pd) break;
   		p=p->next;
   		} while(p!=out);	// Или пока список не кончится
		q->before(p);		// Вставка нового перед найденным
		if (*q->pd < *out->pd) 
			out=q;			// Если перед первым - коррекция заголовка
	} while(k==0);
	head=out;				// Вернуть новый список на старое место
	}



void main(){
int c[10]={4,7,3,4,5,2,8,6,7,5};
list<int> A;
for (int i=0; i<10; i++) A.end(&c[i]);
cout << A;
A.sort();
cout << A;
}