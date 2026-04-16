//-----------------------------------------------18-01.cpp
#include <stdio.h>
int FF(int A[], int n){
	int b=-1,i,s=0,k=0;
	for (i=1;i<n;i++){
		if (A[i]==A[i-1]) k++;
		else{
			if (k>s) s=k,b=i-k-1;
			k=0;
			}
		}
	if (k>s) s=k,b=i-k-1;
	s++;
	return b;
	}
void main(){
	int C[10]={3,4,4,4,5,5,5,5,4,6},
		B[100],n,i,j,bb;
	printf("n=");			
	scanf("%d",&n);			
	for (i=0;i<n;i++){
		printf("B[%d]=",i);	
		scanf("%d",&B[i]);	
		}
	printf("B[%d]={",n);
	for (i=0;i<n-1;i++){
		printf("%d,",B[i]);
		}
	printf("%d}\n",B[n-1]);
	bb=FF(B,n);
	printf("b(B)=%d\n",bb);
	printf("b(C)=%d\n",FF(C,10));
	}