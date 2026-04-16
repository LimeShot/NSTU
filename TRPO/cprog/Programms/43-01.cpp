//------------------------------------------------------43-01.cpp
//--- Числа Фибоначчи
int FIBO(int n){
	int Fn,Fn1=1,Fn2=1;
	for (int i=2; i<=n; i++){
		Fn=Fn1+Fn2;
		Fn2=Fn1;		// Перехов к следующему шагу:
		Fn1=Fn;			// текущий становится предыдущим
		}
	return Fn;
	}

 #include <stdio.h>
 void main(){
 for (int nn=2; nn<10;nn++)
	printf("FIBO(%d)=%d\n",nn,FIBO(nn)); }
