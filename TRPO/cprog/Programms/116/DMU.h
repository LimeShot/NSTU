#include <malloc.h>
#ifndef DMU_def
#define DMU_def 0
//---- Шаблон динамического массива указателей
template <class T> class DMU{
	int n,sz;
	T **pd;
public:
	DMU(int sz0=10){
		sz=sz0; n=0;
		pd= new T*[sz];
		}
	~DMU(){
		clear();			// В ДМУ все объекты - собственность класса
		delete []pd;
		}
	void clear(){
		for (int i=0;i<n;i++) delete pd[i];
		n=0;
		}
	void extend(){
		if (n!=sz) return;
		sz*=2;
		pd=(T**)realloc(pd,sz*sizeof(T*));
		}
	T* operator[](int m){
		if (m<0 || m>=n) return NULL;
		return pd[m];
		}
	void add(T *q){
		pd[n++]=q;
		extend();
		}
	void swap(int i,int j){
		T *c=pd[i]; pd[i]=pd[j]; pd[j]=c;
		}
	int size(){ return n;}
	};
//----------------------------------------
#endif