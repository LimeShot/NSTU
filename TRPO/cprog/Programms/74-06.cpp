//------------------------------------------------------ 1
int F11(int A[],int n){
	if (n==1) return A[0];
	int vv=F11(A,n-1);
	return vv>A[n-1] ? vv : A[n-1];
	}
//------------------------------------------------------ 2
int F12(int A[],int n){
	if (n<=0) return 0; 
	if (n==1) return A[0];
	int m=n/2;
	int v1=F12(A,m);
	int v2=F12(&A[m],n-m);
	return v1>v2 ? v1: v2; 
	}
//------------------------------------------------------ 3
int F13(int A[],int n){
	if (n==1) return A[0];
	int vv=F13(A,n-1);
	return A[n-1] + vv;
	}
//------------------------------------------------------ 4
int F14(int A[],int n){
	if (n<=0) return 0; 
	if (n==1) return A[0];
	int m=n/2;
	int v1=F14(A,m);
	int v2=F14(&A[m],n-m);
	return v1+v2; 
	}
//------------------------------------------------------ 5
int F15(int A[], int a, int b, int val){
	int i,j,mode;
	if (a>=b) return -1;
	int m=(a+b)/2;
	if (val==A[m]) return m;
	if (val<A[m])  return F15(A,a,m-1,val);
	return F15(A,m+1,b,val); }
//------------------------------------------------------ 6
void F16(int A[],int n){
	if (n==1) return;
	int i,k;
	for(i=k=0;i<n;i++)
		if (A[i]<A[k]) k=i;
	int c=A[k]; A[k]=A[n-1];A[n-1]=c;
	F16(A,n-1);
	}
//------------------------------------------------------ 7
void F17(int A[],int n){
	int c=A[0]; A[0]=A[n-1];A[n-1]=c;
	F17(&A[1],n-2);
	}
//------------------------------------------------------ 8
int F18(int A[],int n){
	if (n==0) return 0;
    return F18(A,n-1)+(A[n-1]<0);
	}
//------------------------------------------------------ 9
int F19(int A[],int n){
	if (n<=0) return 0; 
	if (n==1) return A[0]<0;
	int m=n/2;
	return F19(A,m)+ F19(&A[m],n-m);
	}
//------------------------------------------------------ 10
void F20(int A[], int m){
	if (m==1) { A[0]=0; return; }
	int i;
	for (i=2; m % i !=0; i++);
	A[0]=i; 
	F20(&A[1],m/i); }
//------------------------------------------------------ 11
void F21(int A[], int a, int b){
	int i,j,mode;
	if (a>=b) return;
	for (i=a, j=b, mode=1; i != j; mode >0 ? i++ : j--)
	if (A[i] > A[j]){ 
		int c;
		c=A[i]; A[i]=A[j]; A[j]=c; mode = -mode;
		}
	F21(A,a,i-1); F21(A,i+1,b); }
//------------------------------------------------------ 12
char *F22(char *p, char *s) {
	if ( *s =='\0') return p;
	*p++ = *s;
	p=F22(p, s+1);
	*p++ = *s;
	return p;}
void z22() { char *q, S[80]; *F22(S, "abcd")=0; }
//------------------------------------------------------ 13
void F23(char *&p, char *s){
	if ( *s =='\0') return;
	*p++ = *s;
	F23(p, s+1);
	*p++ = *s; }
void z23() {char *q, S[80]; q = S; F23(q,"abcd"); *q=0; }
//------------------------------------------------------ 14
double F24(double A[], double x, int n){
	if (n==0) return A[0];
	return A[0] + x *F24(&A[1],x,n-1); }
void z24() {double B[]={5.,0.7,4.,3.} ,X=3.,Y=F24(B,X,4); }
//------------------------------------------------------ 15
long F25(int n){
	if (n==0 || n==1) return 1;
	return F25(n-1)+F25(n-2);}
//------------------------------------------------------16
long F26(int n){
	if (n==0 || n==1) return 1;
	return n*F26(n-1); }
