//------------------------------------------------------43-02.cpp
//--- sin, cos кратных углов
//
// sin(nx) = sin((n-1)x)cos(x) + cos((n-1)x)sin(x)
// cos(nx) = cos((n-1)x)cos(x) - sin((n-1)x)sin(x)
//
// 
// 
 #include <stdio.h>
 #include <math.h>
 void main(){
 int FI=30;
 double pi=3.1415926;
 double Cn,Cn1,C0,Sn,Sn1,S0;	// S0=sin(x), Sn1=sin((n-1)x), Sn=sin(nx)
 Cn1=C0=cos(FI*pi/180);			// при n=2  sin((n-1)x)=sin(x)
 Sn1=S0=sin(FI*pi/180);
 printf("sin(%d*%d)=%lf cos(%d*%d)=%lf\n",1,FI,S0,1,FI,C0); 
 for (int n=2;n<=10;n++){
	Sn=Sn1*C0 + Cn1*S0;			// Рекуррентная формула
	Cn=Cn1*C0 - Sn1*S0;
	printf("sin(%d*%d)=%lf cos(%d*%d)=%lf\n",n,FI,Sn,n,FI,Cn); 
	Cn1=Cn;						// Переход к следующему шагу
	Sn1=Sn;						// текущий становится предыдущим
	}
 }