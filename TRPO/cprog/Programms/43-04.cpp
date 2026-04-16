//------------------------------------------------------43-04.cpp
//-----Степенной полином
 double poly(double A[], double x, int n){ 
 int i; double s;
 for (s=A[n], i=n; i>=0; i--) s = s * x + A[i];
 return s; }

#include <stdio.h>
void main(){
double B[]={4,0,3,1,8};
printf("%lf\n",poly(B,2.,4));}
