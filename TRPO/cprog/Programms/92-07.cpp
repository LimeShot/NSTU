#include <stdio.h>
#include <string.h>
//------------------------------------------------------92-07.cpp
//------------------------------------------------------ 1
 struct man {char name[20]; int dd,mm,yy; char *addr; };
 char *F1(char *p, char *nm, char *ad)
 { man *q =(man*)p;
 strcpy(q->name,nm);
 strcpy((char*) (q+1 ),ad);
 q->addr = (char*) (q+1 );
 for (p=(char*) (q+1 ); *p!=0; p++);
 p++; return p;}
 //------------------------------------------------------ 2
 struct man1 {char name[20]; int dd,mm,yy; char addr[]; };
 char *F2(char *p, char *nm, char *ad)
 { man1 *q =(man1*)p;
 strcpy(q->name,nm);
 strcpy(q->addr,ad);
 for (p=q->addr; *p!=0; p++);
 p++; return p;}
 //------------------------------------------------------ 3
 int *F3(int *q, char *p[])
 { char *s; int i;
 for (i=0; p[i]!=NULL; i++);
 *q = i;
      for (s = (char*)(q+1), i=0; p[i]!=NULL; i++) {
      for ( int j=0; p[i][j]!='\0'; j++) *s++ = p[i][j];
      *s++ = '\0';
      }
 return (int*)s;}
 //------------------------------------------------------- 4
 double F4(int *p)
 { double *q,s; int m;
 for (q=(double*)(p+1), m=*p, s=0.; m>=0; m--) s+= *q++;
 return s;}
 //------------------------------------------------------- 5
 char *F5(char *s, char *p[])
 { int i,j;
      for (i=0; p[i]!=NULL; i++) {
      for (j=0; p[i][j]!='\0'; j++) *s++ = p[i][j];
      *s++ = '\0';
      }
 *s = '\0'; return s;}
 //------------------------------------------------------- 6
 union x {int *pi; long *pl; double *pd;};
 double F6(int *p)
 { union x ptr;
 double dd=0;
 for (ptr.pi=p; *ptr.pi !=0; )
           switch (*ptr.pi++) {
 case 1: dd += *ptr.pi++; break;
 case 2: dd += *ptr.pl++; break;
 case 3: dd += *ptr.pd++; break;
      }
 return dd;}
 //------------------------------------------------------- 7
 unsigned char *F7(unsigned char *s, char *p)
 { int n;
 for (n=0; p[n] != '\0'; n++);
 *((int*)s) = n; s+=sizeof(int);
 for (; *p != '\0'; *s++ = *p++);
 s++; return s;}
 //------------------------------------------------------- 8
 int *F8(int *p, int n, double v[])
 { *p++ = n;
 for (int i=0; i<n; i++) 
	{ *((double*)p) = v[i]; p+=sizeof(double)/sizeof(int); }
 return p;}
 //------------------------------------------------------- 9
 double F9(int *p)
 { double s=0;
      while(*p!=0) {
      if (*p>0) s+=*p++;
      else
		{ p++; s+= *((double*)p); p+=sizeof(double)/sizeof(int); }
      }
 return s; }
 //------------------------------------------------------ 10
 double F10(char *p)
 { double s; char *q;
 for (q=p; *q!=0; q++);
 for (q++; *p!=0; p++)
           switch(*p) {
 case 'd': s+=*((int*)q); q+=sizeof(int); break;
 case 'f': s+=*((double*)q); q+=sizeof(double); break;
 case 'l': s+=*((long*)q); q+=sizeof(long); break;
      }
 return s; }
 //-------------------------------------------------------11
 int F11(char *p)
 { int s=0, *v; char *q;
 for (q=p; *q!=0; q++);
 q++; v=(int*)q;
 for(;*p!=0;p++)
      if (*p>='0' && *p<='9') s+=v[*p-'0'];
 return s; }
 
