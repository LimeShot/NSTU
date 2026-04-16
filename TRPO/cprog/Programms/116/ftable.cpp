#include <malloc.h>
#include "ftable.h"
#include "table.h"

static Int I0(0);
static String S0("");
static Float F0(0);
static ADT_mem *proto[]={&I0,&F0,&S0,NULL};

void Ftable::create(char nm[],int sz0){
	fstream F(nm,ios::out | ios::binary | ios::trunc);
	int nr0=0,nc0,i;
	long p0;
	Mtable TB;
	printf("cols=");
	scanf("%d",&nc0);
	for (i=0;i<nc0;i++) TB.add_col();
	F.write((char*)&nc0,sizeof(int));
	F.write((char*)&nr0,sizeof(int));
	F.write((char*)&sz0,sizeof(int));
	F.write((char*)&p0,sizeof(long));
	for (i=0;i<nc0;i++){
		int t=TB.HEAD[i]->type();
		F.write((char*)&t,sizeof(int));
		TB.NAMES[i]->save(F);
		}
	p0=F.tellg();
	long vv=0;
	for (i=0;i<sz0;i++)
		F.write((char*)&vv,sizeof(long));
	F.seekg(3*sizeof(int));
	F.write((char*)&p0,sizeof(long));
	F.close();
}


void Ftable::create_head(char nm[]){
	fstream F(nm,ios::out | ios::binary | ios::trunc);
	long p0_new=p0;
	int nr0=0,i;
	F.write((char*)&nc,sizeof(int));
	F.write((char*)&nr0,sizeof(int));
	F.write((char*)&sz,sizeof(int));
	F.write((char*)&p0_new,sizeof(long));
	for (int i=0;i<nc;i++){
		int t=HEAD[i]->type();
		F.write((char*)&t,sizeof(int));
		NAMES[i]->save(F);
		}
	p0_new=F.tellg();
	long vv=0;
	for (i=0;i<sz;i++)
		F.write((char*)&vv,sizeof(long));
	F.seekg(3*sizeof(int));
	F.write((char*)&p0_new,sizeof(long));
	F.close();
}

int Ftable::load(char nm[]){
	open(nm,ios::in | ios::out | ios::binary);
	if (!good()) { nc=0; return 0; }
	read((char*)&nc,sizeof(int));
	read((char*)&nr,sizeof(int));
	read((char*)&sz,sizeof(int));
	read((char*)&p0,sizeof(long));
	for (int i=0;i<nc;i++){
		int t;
		read((char*)&t,sizeof(int));
		HEAD.add(Mtable::create_ADT(t));
		String *s=new String("");
		s->load(*this);
		NAMES.add(s);
		}
	pp=new long[sz];
	seekg(p0);
	read((char*)pp,sz*sizeof(long));
	return good();
	}

void Ftable::update_sys(){
	seekg(0);
	write((char*)&nc,sizeof(int));
	write((char*)&nr,sizeof(int));
	write((char*)&sz,sizeof(int));
	write((char*)&p0,sizeof(long));
	seekg(p0);
	write((char*)pp,sz*sizeof(long));
	}

void Ftable::extend(){
	if (nr!=sz) return;
	sz*=2;
	pp=(long*)realloc(pp,sz*sizeof(long));
	for (int i=sz/2;i<sz;i++) pp[i]=0;
	seekg(0,ios::end);
	p0=tellg();
	update_sys();
	}

void Ftable::close(){ update_sys(); fstream::close(); }

void Ftable::add(record *p){
	seekg(0,ios::end);
	pp[nr++]=tellg();
	p->save(*this);
	extend();
	}

void Ftable::add(){
	record *q=HEAD.clone();
	for (int i=0;i<nc;i++){
		char c[80],*s;
		s=NAMES[i]->put();
		printf("%s(%s):",s,HEAD[i]->name());
		delete []s;
		gets(c);
		(*q)[i]->get(c);
		}
	add(q);
	}

void Ftable::show(){
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
		record *p=HEAD.clone();
		seekg(pp[i]);
		p->load(*this);
		for (j=0;j<nc;j++){
			q=(*p)[j]->put();
			printf("%15s",q);
			delete []q;
			}
		delete p;
		puts("");
		}
	}

record *Ftable::get(int m){
	if (m<0 || m>=nr) return NULL;
	record *p=HEAD.clone();
	seekg(pp[m]);
	p->load(*this);
	return p;
	}

void Ftable::compress(char nm[]){
	Ftable::create_head(nm);
	Ftable T;
	T.load(nm);
	for (int i=0;i<nr;i++){
		record *p=get(i);
		T.add(p);
		delete p;
		}
	T.close();
	}

//-- Быстрая сортировка
void Ftable::sort(DMU<ADT_mem> *COL,int a,int b){
	if (a>=b) return;
	int i,j,mode;
	for(i=a,j=b,mode=1;i<j;mode ? j--: i++)
		if ((*COL)[i]->cmp((*COL)[j])>0){
			COL->swap(i,j);
			long c=pp[i]; pp[i]=pp[j]; pp[j]=c;
			mode=!mode;
			}
	sort(COL,a,i-1);
	sort(COL,i+1,b);
	}

void Ftable::sort(int k){
	if (k<0 || k>=nc) return;
	DMU<ADT_mem> *pcol=new DMU<ADT_mem>;
	for (int i=0;i<nr;i++){
		record *q=get(i);
		pcol->add((*q)[k]->clone());
		delete q;
		}
	sort(pcol,0,nr-1);
	delete pcol;
	update_sys();
	}

void Ftable::update(record *q, int k){
	if (k<0 || k>=nr) return;
	record *old=get(k);
	if (q->fsize()<=old->fsize())
		seekg(pp[k]);
	else{
		seekg(0,ios::end);
		pp[k]=tellg();
		}
	q->save(*this);
	}