#include "table.h"
//------------------------------------------------
// Набор объектов - прототипов 
// аналог виртуального конструктора
static Int I0(0);
static String S0("");
static double d[1];
static Float F0(0);
static Matrix M0(1,1,d);
static ADT_mem *proto[]={&I0,&F0,&S0,&M0,NULL};

ADT_mem *Mtable::create_ADT(int k){
	for (int i=0;proto[i]!=NULL;i++)
		if (proto[i]->type()==k)
			return proto[i]->clone();
	return NULL;
	}
//-------------------------------------------
int Mtable::load(char nm[]){
	fstream F;
	F.open(nm,ios::in | ios::binary);
	F.read((char*)&nc,sizeof(int));
	F.read((char*)&nr,sizeof(int));
	int i;
	for (i=0;i<nc;i++){
		int t;
		F.read((char*)&t,sizeof(int));
		HEAD.add(create_ADT(t));
		String *s=new String("");
		s->load(F);
		NAMES.add(s);
		}
	for (i=0;i<nr;i++){
		record *q=HEAD.clone();
		q->load(F);
		TBL.add(q);
		}
	F.close();
	return 1;
	}
int Mtable::save(char nm[]){
	fstream F;
	F.open(nm,ios::out | ios::binary | ios::trunc);
	F.write((char*)&nc,sizeof(int));
	F.write((char*)&nr,sizeof(int));
	int i;
	for (i=0;i<nc;i++){
		int t=HEAD[i]->type();
		F.write((char*)&t,sizeof(int));
		NAMES[i]->save(F);
		}
	for (i=0;i<nr;i++) TBL[i]->save(F);
	F.close();
	return 1;
	}
//-------------------------------------------------
void Mtable::add_col(){
	int i;
	if (nr!=0) return;
	for (i=0;proto[i]!=0;i++) printf("%d:%s\n",i,proto[i]->name());
	char c[80];
	int k;
	scanf("%d",&k);
	if (k<0 || k>=i) return;
	HEAD.add(proto[k]->clone());
	gets(c);
	gets(c);
	NAMES.add(new String(c));
	nc++;
	}
//-- Быстрая сортировка
void Mtable::sort(int k,int a,int b){
	if (a>=b) return;
	int i,j,mode;
	for(i=a,j=b,mode=1;i<j;mode ? j--: i++)
		if ((*TBL[i])[k]->cmp((*TBL[j])[k])>0){
			TBL.swap(i,j);
			mode=!mode;
			}
	sort(k,a,i-1);
	sort(k,i+1,b);
	}
void Mtable::sort(int k){ sort(k,0,nr-1); }
void Mtable::show(){
	int i,j;
	char *q;
	for (j=0;j<nc;j++) {
		q=NAMES[j]->put();
		printf("%15s",q);
		delete []q;
		}
	puts("");
	for (j=0;j<nc;j++) printf("%15s",HEAD[j]->name());
	puts("");
	for (i=0;i<nr;i++){
		for (j=0;j<nc;j++){
			q=(*TBL[i])[j]->put();
			printf("%15s",q);
			delete []q;
			}
		puts("");
		}
	}
void Mtable::add(){
	record *q=HEAD.clone();
	for (int i=0;i<nc;i++){
		char c[80],*s;
		s=NAMES[i]->put();
		printf("%s(%s):",s,HEAD[i]->name());
		delete []s;
		gets(c);
		(*q)[i]->get(c);
		}
	TBL.add(q);
	nr++;
	}
