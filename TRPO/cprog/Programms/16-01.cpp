//-----------------------------------------------16-01.cpp
#include <stdio.h>
//-------------------------------------------------
void Hello(){
	printf("Hello, Im here");
	}
void main(){ Hello(); }
//-------------------------------------------------
int nod(int a,int b){
	int n; for (n=a; !(n%a==0 && n%b==0);n++);
	return n;
	}
void main(){ int y=nod(36,54); }
//-------------------------------------------------
void inc(int &n){ n++; }
void main(){ int m=6; inc(m); }
//-------------------------------------------------
void swap(int &a, int &b){
	int c=a; a=b;b=c; 
	}
void main(){ int m1=5,m2=7; swap(m1,m2); }
//-------------------------------------------------
void swap(int A[],int n){
	for (int i=0,j=n-1;i<j;i++,j--)
		{ int c=A[i];A[i]=A[j];A[j]=c; }
	}
void main(){
	int B[]={3,6,4,5,7};
	swap(B,5);
	}
//-------------------------------------------------
int max(int A[],int n){
	int i,s; for (int i=1,s=A[0];i<n;i++)
		if (A[i]>s) s=A[i];
	return s;
	}
void main(){
	int m,B[]={3,6,4,5,7};
	m=max(B,5);
	}
//-------------------------------------------------
void max(int &s,int A[], int n){
	int i;
	for (i=1,s=A[0];i<n;i++)
		if (A[i]>s) s=A[i];
	}
void main(){
	int m,B[]={3,6,4,5,7};
	max(m,B,5);
	}
//-------------------------------------------------
int pull(int v,int A[],int n){
	int i=0,m=2;
	while(v!=1 && i!=n){
		if (v%m==0) { A[i++]=m; v/=m; }
		else m++;
		}
	return i;
	}
void main(){
	int k,B[10];
	k=pull(1275,B,10);
	}
//-------------------------------------------------
int len(int &k,int A[],int n){
	for (int i=0;i<n;i++){
		for (k=1;i+k<n && A[i]==A[i+k];k++);
		if (k>1) return i;
		}
	return -1;
	}
void main(){
	int k1,m1,B[10]={5,7,6,6,6,6,6,6,5,7};
	k1=len(m1,B,10);
	}