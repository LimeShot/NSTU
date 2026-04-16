#include <stdio.h>
//------------------------------------------------------93-05.cpp
//------------------------------------------------------- 1
 void ( *P1(void(*ff)(void)))(void) { return ff; }
 void foo1(void){ printf("I'm foo\n"); }
 void main1(){(*P1(foo1))();}
 //------------------------------------------------------- 2
 int ( *P2(int(*ff)(int)))(int) { return ff; }
 int inc2(int n){ return n+1; }
 void main2(){ printf("%d\n",(*P2(inc2))( 5 ));}
 //------------------------------------------------------- 3
 typedef void (*PF3)(void);
 PF3 P3(PF3 ff) { return ff; }
 void foo3(void){ printf("I'm foo\n");; }
 void main3(){(*P3(foo3))();}
 //------------------------------------------------------- 4
 typedef int (*PF4)(int);
 PF4 P4(PF4 ff) { return ff; }
 int inc4(int n){ return n+1; }
 void main4(){ printf("%d\n",(*P4(inc4))( 7 ));}

