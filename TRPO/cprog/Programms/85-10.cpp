#include <stdio.h>
//------------------------------------------------------85-10.cpp
// Тестовые задания
struct ltree{
	int val;
	ltree *child,*next;
	};			

struct tree{
	int val;
	tree *ch[4];
	};		

struct tree1{
	int val;
	int n;
	tree1 *ch[10];
	};		

struct btree{
	int val;
	btree *l,*r;
	};		
	
ltree	A={4,NULL,NULL},
		B={5,NULL,&A},
		C={3,NULL,&B},		
		D={12,NULL,NULL},
		E={7,&C,NULL},
		F={1,&D,&E},	
		G={5,&F,NULL},
		*ph = &G;

tree	a={4,NULL,NULL,NULL,NULL},
		b={5,&a,NULL,NULL,NULL},
		c={3,&b,NULL,NULL,NULL},		
		d={12,NULL,NULL,NULL,NULL},
		e={7,&c,NULL,NULL,NULL},
		f={1,&d,&e,NULL,NULL},	
		g={5,&f,NULL,NULL,NULL},
		*ph1 = &g;

btree	a1={4,NULL,NULL},
		b1={5,&a1,NULL},
		c1={3,&b1,NULL},		
		d1={12,NULL,NULL},
		e1={7,NULL,NULL},
		f1={1,&d1,&c1},	
		g1={5,&f1,&e1},
		*ph2 = &g1;

tree1	a2={4,0},
		b2={5,0},
		c2={3,2,&b2,&a2},		
		d2={12,0},
		e2={7,1,&c2},
		f2={1,2,&d2,&e2},	
		g2={5,1,&f2},
		*ph3 = &g2;


int tree2[]={0,3,2,6,8,3,-1,8,-1,4,-1,-1,-1,-1,9,5};

//----------------------------------------------------------1
int F1(ltree *p){
	int n=1;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		n+=F1(q);	
	return n;
	}
//----------------------------------------------------------2
int F2(ltree *p){
	int n=p->val;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		n+=F2(q);	
	return n;
	}
//----------------------------------------------------------3
int F3(ltree *p){
	int n=p->val;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		{ int vv=F3(q);	if (vv > n)  n=vv; }
	return n;
	}
//----------------------------------------------------------4
int F4(ltree *p){
	int n=0;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		{ int vv=F4(q);	if (vv > n)  n=vv; }
	return n+1;
	}
//----------------------------------------------------------5
void F5(ltree *p, int l, int &m){
	if (l > m) m=l;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		F5(q,l+1,m);
	}
//----------------------------------------------------------6
int F6(ltree *p, int l){
	int n=l;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		n+=F6(q,l+1);	
	return n;
	}
double main6(ltree *p){
	return ((double)F6(p,1))/F1(p);
	}
//----------------------------------------------------------7
int F7(ltree *p){
	if (p->val > 6) return p->val;
	for (ltree *q=p->child; q!=NULL; q=q->next)
		{ int vv=F7(q); if (vv!=-1) return vv; }
	return -1;
	}
//----------------------------------------------------------8
int F8(btree *p) {
	if (p==NULL) return 0;
	return (1 + F8(p->r) + F8(p->l)); 
	}
//----------------------------------------------------------9
int F9(btree *p) {
if (p==NULL) return 0;
int nr=F9(p->r);
int nl=F9(p->l);
return 1 + (nr>nl ? nr : nl); }
//----------------------------------------------------------10
int F10(btree *p) {
if (p==NULL) return 0;
int m,n=p->val;
if ((m=F10(p->r))>n) n=m;
if ((m=F10(p->l))>n) n=m;
return n; }
//----------------------------------------------------------11
int F11(tree1 *p){
	int s=1;
	for (int i=0;i < p->n; i++)
		s+=F11(p->ch[i]);	
	return s;
	}
//----------------------------------------------------------12
int F12(tree1 *p){
	int s=p->val;
	for (int i=0;i < p->n; i++)
		s+=F12(p->ch[i]);	
	return s;
	}
//----------------------------------------------------------13
int F13(tree1 *p){
	int s=p->val;
	for (int i=0;i < p->n; i++)
		{ int vv=F13(p->ch[i]);	if (vv > s)  s=vv; }
	return s;
	}
//----------------------------------------------------------14
int F14(tree1 *p){
	int s=0;
	for (int i=0;i < p->n; i++)
		{ int vv=F14(p->ch[i]);	if (vv > s)  s=vv; }
	return s+1;
	}
//----------------------------------------------------------15
void F15(tree1 *p, int l, int &m){
	if (l > m) m=l;
	for (int i=0;i < p->n; i++)
		F15(p->ch[i],l+1,m);
	}
//----------------------------------------------------------16
int F16(tree1 *p, int l){
	int s=l;
	for (int i=0;i < p->n; i++)
		s+=F16(p->ch[i],l+1);	
	return s;
	}
double main16(tree1 *p){
	return ((double)F16(p,1))/F11(p);
	}
//----------------------------------------------------------17
int F17(tree1 *p){
	if (p->val > 6) return p->val;
	for (int i=0;i < p->n; i++)
		{ int vv=F17(p->ch[i]); if (vv!=-1) return vv; }
	return -1;
	}
//----------------------------------------------------------21
int F21(tree *p){
	if (p==NULL) return 0;
	int s=1;
	for (int i=0; i<4; i++)
		s+=F21(p->ch[i]);	
	return s;
	}
//----------------------------------------------------------22
int F22(tree *p){
	if (p==NULL) return 0;
	int s=p->val;
	for (int i=0; i<4; i++)
		s+=F22(p->ch[i]);	
	return s;
	}
//----------------------------------------------------------23
int F23(tree *p){
	if (p==NULL) return 0;
	int s=p->val;
	for (int i=0; i<4; i++)
		{ int vv=F23(p->ch[i]);	if (vv > s)  s=vv; }
	return s;
	}
//----------------------------------------------------------24
int F24(tree *p){
	if (p==NULL) return 0;
	int s=0;
	for (int i=0; i<4; i++)
		{ int vv=F24(p->ch[i]);	if (vv > s)  s=vv; }
	return s+1;
	}
//----------------------------------------------------------25
void F25(tree *p, int l, int &m){
	if (p==NULL) return;
	if (l > m) m=l;
	for (int i=0; i<4; i++)
		F25(p->ch[i],l+1,m);
	}
//----------------------------------------------------------26
int F26(tree *p, int l){
	if (p==NULL) return 0;
	int s=l;
	for (int i=0; i<4; i++)
		s+=F26(p->ch[i],l+1);	
	return s;
	}
double main26(tree *p){
	return ((double)F26(p,1))/F21(p);
	}
//----------------------------------------------------------27
int F27(tree *p){
	if (p->val > 6) return p->val;
	for (int i=0; i<4; i++)
		{ int vv=F27(p->ch[i]); if (vv!=-1) return vv; }
	return -1;
	}
//----------------------------------------------------------30
int F30(int A[],int sz, int n){
	if (n>=sz || A[n]==-1) return 0;
	return 1+F30(A,sz,2*n)+F30(A,sz,2*n+1);
	}
//----------------------------------------------------------31
int F31(int A[],int sz, int n){
	if (n>=sz || A[n]==-1) return 0;
	return A[n]+F31(A,sz,2*n)+F31(A,sz,2*n+1);
	}
//----------------------------------------------------------32
int F32(int A[],int sz, int n){
	if (n>=sz || A[n]==-1) return 0;
	int xx,vv=A[n];
	if ((xx=F32(A,sz,2*n))>vv) vv=xx;
	if ((xx=F32(A,sz,2*n+1))>vv) vv=xx;
	return vv;
	}
//----------------------------------------------------------33
int F33(int A[],int sz, int n){
	if (n>=sz || A[n]==-1) return 0;
	int x1=F33(A,sz,2*n);
	int x2=F33(A,sz,2*n+1);
	return x1>x2 ? x1+1 : x2+1;
	}


void main(){
	printf("F1=%d\n",F1(ph));
	printf("F2=%d\n",F2(ph));
	printf("F3=%d\n",F3(ph));
	printf("F4=%d\n",F4(ph));
	int m=0; F5(ph,1,m);
	printf("F5=%d\n",m);
	printf("F6=%3.1lf\n",main6(ph));
	printf("F7=%d\n",F7(ph));
	printf("F8=%d\n",F8(ph2));
	printf("F9=%d\n",F9(ph2));
	printf("F10=%d\n",F10(ph2));
	printf("F11=%d\n",F11(ph3));
	printf("F12=%d\n",F12(ph3));
	printf("F13=%d\n",F13(ph3));
	printf("F14=%d\n",F14(ph3));
	m=0; F15(ph3,1,m);
	printf("F15=%d\n",m);
	printf("F16=%3.1lf\n",main16(ph3));
	printf("F17=%d\n",F17(ph3));
	printf("F21=%d\n",F21(ph1));
	printf("F22=%d\n",F22(ph1));
	printf("F23=%d\n",F23(ph1));
	printf("F24=%d\n",F24(ph1));
	m=0; F25(ph1,1,m);
	printf("F25=%d\n",m);
	printf("F26=%3.1lf\n",main26(ph1));
	printf("F27=%d\n",F27(ph1));
	printf("F30=%d\n",F30(tree2,sizeof(tree2)/sizeof(int),1));
	printf("F31=%d\n",F31(tree2,sizeof(tree2)/sizeof(int),1));
	printf("F32=%d\n",F32(tree2,sizeof(tree2)/sizeof(int),1));
	printf("F33=%d\n",F33(tree2,sizeof(tree2)/sizeof(int),1));
	}

