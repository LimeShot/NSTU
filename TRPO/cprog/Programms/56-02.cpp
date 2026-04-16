#include <malloc.h>
#include <stdio.h>
//------------------------------------------------------56-02.cpp
//----------------------------------------------------- 1
 char *F1(char *s)
 { char *p,*q; int n;
 for (n=0; s[n] !='\0'; n++);
 p = new char[n+1];
 for (q=p; n >=0; n--) *q++ = *s++;
 return p; }
 //------------------------------------------------------- 2
 int *F2()
 { int n,i,*p;
 scanf("%d",&n);
 p=new int[n+1];
 for (p[0]=n, i=0; i<n; i++) scanf("&d",&p[i+1]);
 return p; }
 //------------------------------------------------------- 3
 int *F3()
 { int n,i,*p;
 scanf("%d",&n);
 p=new int[n+1];
 for (i=0; i<n; i++)
      { scanf("&d",&p[i]); if (p[i]<0) break; }
 p[i]=-1;
 return p; }
 //------------------------------------------------------- 4
 char *F4(char *p, char *q)
 { int n1, n2;
 for (n1=0; p[n1]!=0; n1++);
 for (n2=0; p[n2]!=0; n2++);
 char *s,*v;
 s=v=new char[n1+n2+1];
 while(*p!=0) *s++ = *p++;
 while(*q!=0) *s++ = *q++;
 *s=0;
 return v; }
 //------------------------------------------------------- 5
 double *F5(int n, double v[]){
 double *p=new double[n+1];
 p[0]=n;
 for (int i=0; i<n; i++) p[i+1]=v[i];
 return p; }
 //------------------------------------------------------- 6
 int *F6()
 { int *p, n=10,i;
 p=(int*)malloc(n*sizeof(int));
      for (i=0;;i++){
           if (i==n) { n=n*2; p=(int*)realloc(p,sizeof(int)*n); }
      scanf("&d",&p[i]);
      if (p[i]==0) break;}
 return p;} 
 //------------------------------------------------------- 7 
 void *F7(void *p, int n)
 { char *pp, *qq, *ss;
 qq = ss = new char [n];
 for (pp= (char*)p; n!=0; n--) *pp++ = *qq++;
 return ss;}
 //------------------------------------------------------- 8
 int *F8(int n)
 { int s,i,m,k,*p;
 s = 10; p = (int*)malloc(s*sizeof(int));;
      for (i=2, m=0; i<n; i++) {
      for (k=0; k<m; k++)
	   if (i % p[k]==0) break;
      if (k==m)
	   { p[m++] = i;
		if (m==s){
		s=s*2;
		p= (int*) realloc( (void*) p,sizeof(int)*s);
		}}}
 return p; }
