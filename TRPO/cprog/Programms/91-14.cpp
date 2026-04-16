#include <stdio.h>
//------------------------------------------------------91-14.cpp
//------------------------------------------------
 unsigned long F(unsigned long v, int k){
 int i; unsigned long s;
 for (s=1, i=0; i<k; s<<=1, i++) v = v & ~s;
 return v;}
 void main(){ printf("F(0x1FFF,7)=%lx\n",F(0x1FFF,7)); }
