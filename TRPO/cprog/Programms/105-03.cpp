#include <stdio.h>
//------------------------------------------------------105-03.cpp
//------- Шаблон с параметром-константой
template <class T,int size> class FIFO{
	int fst,lst;			// Индексы начала и конца очереди
	T queue[size];			// Массив объектов класса T размерности size
public:	
	T from();			    // Функции включения-исключения
	int into(T);			//
	FIFO(){ fst=lst=0; }	// Конструктор
	};
 
template <class T,int size> T FIFO<T,size>::from(){
	T work=0;
    if (fst !=lst){
      work = queue[lst++];
      if (lst==size) lst=0;
      }
	return work;}
 
template <class T,int size> int FIFO<T,size>::into(T obj) {
	if ((fst+1)%size==lst)
		return 0;			// Проверка на переполнение
	queue[fst++] = obj;
	if (fst==size) fst=0;
	return 1; }

 void main(){
 FIFO<int,20>	b; 
 int i;
 for (i=0; i<15; i++) b.into(i);
 for (i=0; i<10; i++) printf("%d ",b.from());
 for (i=0; i<10; i++) b.into(i);
 for (i=0; i<20; i++) printf("%d ",b.from());
 }
