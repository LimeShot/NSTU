//------------------------------------------------------61-01.cpp
#define SZ 1000
int A[SZ];
// Последовательность со счетчиком
int n=0;
void add(int vv){ if (n!=SZ-1) A[n++]=vv; }
int get1(int k){ return k>=n ? 0 : A[k]; }
int remove(int k){
	if (k>=n) return 0;
	int vv=A[k];
	for (int j=k;j<n-1;j++) A[j]=A[j+1];
	n--;
	return vv;
	}
int insert(int vv, int k){
	if (n==SZ-1 || k>=n) return 0;
	for (int j=n-1;j<=k;j--) A[j+1]=A[j];
	A[k]=vv;
	n++;
	}
//---------------------------------------------------------
// Стек в массиве
int sp=-1;
void push(int vv){ if (sp!=SZ-1) A[++sp]=vv; }
int pop(){ return sp==-1 ? 0 : A[sp--]; }
int get2(int k){ return sp-k<0 ? 0 : A[sp-k]; }
//---------------------------------------------------------
// Очередь в массиве
void in(int vv){ if (n!=SZ-1) A[n++]=vv;}
int out(){
	if (n==0) return 0;
	int vv=A[0];
	for (int i=0;i<n-1;i++) A[i]=A[i+1];
	n--;
	return vv;
	}
int get3(int k){ return k>=n ? 0 : A[k]; }
//---------------------------------------------------------
// Циклическая очередь в массиве
int fst=0,lst=0;
void in2(int vv){ 
	if ((lst+1)%SZ==fst) return;
	A[lst++]=vv;
	if (lst==SZ) lst=0;
	}
int out2(){
	if (fst==lst) return 0;
	int vv=A[fst++];
	if (fst==SZ) fst=0;
	return vv;
	}
int get4(int m){ return A[(fst+m)%SZ]; }



void main(){}
