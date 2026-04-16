#include <stdio.h>
#include <string.h>
//------------------------------------------------------92-09.cpp
//--------------------------------------------------------1
 void F1(int *p,...)
 { int **q, i, d;
 for (i=1, q = &p, d=*p; q[i]!=NULL; i++) *q[i-1] = *q[i];
 *q[i-1] = d;}
 //--------------------------------------------------------2 
 int *F2(int *p,...)
 { int **q, i, *s;
 for (i=1, q = &p, s=p; q[i]!=NULL; i++)
      if (*q[i] > *s) s = q[i];
 return s; }
 //--------------------------------------------------------3 
 int F3(int p[], int a1,...)
 { int *q, i;
 for (i=0, q = &a1; q[i] > 0; i++) p[i] = q[i];
 return i;}
 //--------------------------------------------------------4 
 union x { int *pi; long *pl; double *pd; };
 void F4(int p,...)
 { union x ptr;
 for (ptr.pi = &p; *ptr.pi != 0; ) {
      switch(*ptr.pi++) {
              case 1: printf("%d",*ptr.pi++); break;
              case 2: printf("%ld",*ptr.pl++); break;
              case 3: printf("%lf",*ptr.pd++); break;
           }}}
 //--------------------------------------------------------5 
 char **F5(char *p,...)
 { char **q,**s; int i,n;
 for (n=0, q = &p; q[n] !=NULL; n++);
 s = new char*[n+1];
 for (i=0, q = &p; q[i] !=NULL; i++) s[i]=q[i];
 s[n]=NULL; return s;}
 //--------------------------------------------------------6 
 char *F6(char *p,...)
 { char **q; int i,n;
 for (i=0, n=0, q = &p; q[i] !=NULL; i++)
      if (strlen(q[i]) > strlen(q[n])) n=i;
 return q[n]; }
 //--------------------------------------------------------7
 int F7(int a1,...)
 { int *q, s;
 for (s=0, q = &a1; *q > 0; q++) s+= *q;
 return s;}
 //--------------------------------------------------------8 
 union xx { int *pi; long *pl; double *pd; };
 double F8(int p,...)
 { union xx ptr;
 double dd=0;
 for (ptr.pi = &p; *ptr.pi != 0; )
            {
         switch(*ptr.pi++) {
  case 1: dd+= *ptr.pi++; break;
  case 2: dd+= *ptr.pl++; break;
  case 3: dd+= *ptr.pd++; break;
         }}
 return dd;}
 //-------------------------------------------------------9 
 double F9(int a1,...)
 { double s=0; int *p=&a1;
 while(*p!=0) {
            if (*p>0) s+=*p++;
            else
           { p++; s += *((double*)p)++; } 
            } return s; }
 //--------------------------------------------------------10 
 double F10(char *p,...)
 { double s;
 int *q=(int *)(&p+1);
 for (;*p!=0; p++)
           switch(*p) {
 case 'd': s+=*q++; break;
 case 'f': s+=*((double*)q)++; break;
 case 'l': s+=*((long*)q)++; break;
            } return s; }
 //--------------------------------------------------------11 
 int F11(char *p,...)
 { int s=0, *q=(int *)(&p+1);
 for(;*p!=0;p++)
      if (*p>='0' && *p<='9') s+=q[*p-'0'];
 return s; }
 //--------------------------------------------------------12 
 double F12(int p,...)
 { double dd=0; int *q=&p;
      for (; *q != 0; ) {
      switch(*q++)
           {
  case 1: dd+= *q++; break;
  case 2: dd+= *((long*)q)++; break;
  case 3: dd+= *((double*)q)++; break;
           }}
 return dd;}