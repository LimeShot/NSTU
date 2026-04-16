#ifndef Rec_def
#define Rec_def 0
#include "ADT_mem.h"
#include "DMU.h"
// Класс строки таблицы
class record{
public:
	DMU<ADT_mem> R;
	ADT_mem *operator[](int m){ return R[m]; }
	record *clone(){
		record *q=new record;
		for (int i=0;i<R.size();i++) q->R.add(R[i]->clone());
		return q;
		}
	int save(fstream &F){
		for (int i=0;i<R.size();i++) 
			if (!R[i]->save(F)) return 0;
		return 1;		
		}
	int load(fstream &F){
		for (int i=0;i<R.size();i++) 
			if (!R[i]->load(F)) return 0;
		return 1;		
		}
	void add(ADT_mem *q){ R.add(q); }
	int fsize(){ 
		int i,s;
		for (s=0,i=0;i<R.size();i++) 
			s+=R[i]->fsize();
		return s;		
		}
	void edit(){
		for (int i=0;i<R.size();i++){
			char *q=R[i]->put();
			char c[80];
			printf("%d:%s:%s\n",i,R[i]->name(),q);
			gets(c);
			R[i]->get(c);
			delete []q;
			}
		}
	};
#endif