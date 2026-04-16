#include <stdio.h>

int FF(int A[], int n){
if (n==1) return 0;
for (int m=0,j=1,k=0;j<n;j++,m++)
	if (A[j]>A[k]) k=j;
int v=A[k];A[k]=A[n-1];A[n-1]=v;
return FF(A,n-1)+ m;
}

void main() { int v=0,B[10]={4,8,3,4,8,2,3,8,3,6};
printf("T=%d\n",FF(B,10));
for (int i=0;i<10;i++) printf("%d ",B[i]);
} 
