#include <stdio.h>
#include <malloc.h>
#include <string.h>
//------------------------------------------------------95-17.cpp
 struct man { int dd,mm,yy; char *addr; };
//------------------------------------------------------ 1
 man *F1(int n, FILE *fd)
 { man *p = new man;
 fseek (fd, (long)sizeof( man)*n, SEEK_SET);
 fread (p, sizeof( man),1,fd);
 return(p); }
 //------------------------------------------------------ 2
 void *F2(FILE *fd)
 { int n; void *p;
 fread(&n,sizeof(int),1,fd);
 if (n==0) return(NULL);
 p = ( void*) new char[n];
 fread(p,n,1,fd);
 return p; }
 //------------------------------------------------------ 3
 double *F3(FILE *fd)
 { int n; double *p;
 fread(&n,sizeof(int),1,fd);
 if (n==0) return(NULL);
 p = new double[ n+1];
 fread(p,sizeof(double),n,fd);
 p[n]=0.0;
 return p; }
 //------------------------------------------------------ 4
 #define FNULL -1L
 struct xxx { long fnext; /*. . .*/ };
 xxx *F4(int n,FILE *fd)
 { xxx *p; long p0;
 p = new xxx;
 fseek(fd,0L,SEEK_SET);
 fread(&p0,sizeof(long),1,fd);
      for (; p0!=FNULL && n!=0; n--, p0 = p->fnext) {
      fseek(fd,p0,SEEK_SET);
      fread(p,sizeof( xxx),1,fd); }
 return p; }
 //------------------------------------------------------ 5
 man *F5(int n, FILE *fd)
 { long fp; man *p = new man;
 fseek(fd, sizeof(long)*n,SEEK_SET);
 fread(&fp,sizeof(long),1,fd);
 fseek(fd,fp,SEEK_SET);
 fread(p,sizeof(man),1,fd);
 return p; }
 //------------------------------------------------------ 6
 void *F6(int n, FILE *fd)
 { int sz; void *p;
 fseek(fd,0L,SEEK_SET);
 fread(&sz,sizeof(int),1,fd);
 p = ( void*) new char[sz];
 fseek (fd, (long)sz * n +sizeof(int), SEEK_SET);
 fread (p, sz,1,fd);
 return p; }
 //------------------------------------------------------ 7
 void *F7(int n, FILE *fd)
 { int sz; void *p; long p0;
 fseek(fd,0L,SEEK_SET);
 fread(&sz,sizeof(int),1,fd);
 fread(&p0,sizeof(long),1,fd);
 p = (void*)new char[sz];
 fseek (fd, p0 + sizeof(long)*n, SEEK_SET);
 fread (&p0, sizeof(long),1,fd);
 fseek(fd, p0, SEEK_SET);
 fread(p, sz, 1, fd);
 return p; }
 //------------------------------------------------------ 8
 char *F8(int n, FILE *fd)
 { char *p; long fp; int i;
 fseek(fd, sizeof(long)*n,SEEK_SET);
 fread(&fp,sizeof(long),1,fd);
 fseek(fd,fp,SEEK_SET);
 n = 80; p = new char [n];
      for (i=0;; i++) {
      if (i==n) p = (char*)realloc(p, n=n*2);
      fread(p+i,1,1,fd);
      if (p[i]=='\0') return p;
      }
 return p; }
 //------------------------------------------------------ 9
 #define FNULL -1L
 char *F9(int n, FILE *fd)
 { long p0; int sz; char *p;
 fseek(fd,0L,SEEK_SET);
 fread(&p0,sizeof(long),1,fd);
      for (; p0!=FNULL && n!=0; n--) {
      fseek(fd,p0,SEEK_SET);
      fread(&p0,sizeof(long),1,fd);
      }
 if (p0==FNULL) return(NULL);
 fread(&sz,sizeof(int),1,fd);
 p = new char[sz+1];
 fread(p,sz,1,fd);
 p[sz]='\0'; return p;}
 //-------------------------------------------------------- 10
 char *F10(FILE *fd)
 { int n; char *p;
 fread(&n,sizeof(int),1,fd);
 if (n==0) return(NULL);
 p = new char[n];
 fread(p,n,1,fd);
 return p; }
 //-------------------------------------------------------- 11
 void F11(FILE *fd, char *s)
 { int n;
 fseek(fd,0L,SEEK_END);
 n = strlen(s)+1;
 fwrite(&n,sizeof(int),1,fd);
 fwrite(s,n,1,fd); }
 //-------------------------------------------------------- 12
 double *F12(FILE *fd)
 { int n, dn; double *p;
 fread(&n,sizeof(int),1,fd);
 if (n==0) return(NULL);
 dn = n / sizeof(double);
 p = new double[ dn+1];
 p[0]=dn;
 fread(p+1,sizeof(double), dn, fd);
 return p; }
 //-------------------------------------------------------- 13
 void F13(FILE *fd, double *s, int dn)
 { int n;
 n = dn * sizeof(double);
 fseek(fd,0L,SEEK_END);
 fwrite(&n,sizeof(int),1,fd);
 fwrite(s,sizeof(double),dn,fd); }
 //------------------------------------------------------ 14
 void F14(FILE *fd)
 { int n; void *p;
 fread(&n,sizeof(int),1,fd);
 if (n==0) return;
 p = ( void*) new char[n];
 fread(p,n,1,fd);
      switch (n) {
 case sizeof(int): printf("%d ",*(int*)p); break;
 case sizeof(double): printf("%lf ",*(double*)p); break;
 default: printf("%s ",(char*)p); break;
      } delete p; }
 //------------------------------------------------------ 15
 char *F15(int n, FILE *fd)
 { int m; char *p; long fp;
 fseek(fd, sizeof(long)*n,SEEK_SET);
 fread(&fp,sizeof(long),1,fd);
 fseek(fd,fp,SEEK_SET);
 fread(&m,sizeof(int),1,fd);
 p=new char [m];
 fread(p,m,1,fd);
 return p ; }
 //------------------------------------------------------ 16
 char *F16(int n, FILE *fd1, FILE *fd2)
 { long pp; char *q;
 fseek(fd1,n*sizeof(long),SEEK_SET);
 fread(&pp,sizeof(long),1,fd1);
 q = new char[80];
 fseek(fd2,pp,SEEK_SET);
 fgets(q,80,fd2);
 return q; }
 //------------------------------------------------------ 17
 char **F17(FILE *fd)
 { int n,m,i; char **p; long *fp;
 fseek(fd, 0L,SEEK_SET);
 fread(&n,sizeof(int),1,fd);
 p = new char *[n+1];
 fp = new long[n];
 fread(fp,sizeof(long),n,fd);
      for (i=0; i<n; i++) {
      fseek(fd, fp[i],SEEK_SET);
      fread(&m,sizeof(int),1,fd);
      p[i]= new char[m];
      fread(p[i],m,1,fd);
      }
 p[n]=NULL; return p ; }
 //------------------------------------------------------ 18
 #define FNULL -1L
 struct ooo { ooo *p[20]; char *s; long fs; long fp[20]; };
 ooo *F18(FILE *fd, long pos)
 { int i,m; ooo *q;
 if (pos==FNULL) return NULL;
 q = new ooo;
 fseek(fd,pos,SEEK_SET);
 fread(q, sizeof(ooo),1,fd);
 fseek(fd,q->fs,SEEK_SET);
 fread(&m,sizeof(int),1,fd);
 q->s= new char[m];
 fread(q->s,m,1,fd);
 for (i=0; i<20; i++) q->p[i]=F18(fd,q->fp[i]);
 return q; }
 void main() { FILE *fd; ooo *head = F18(fd,0L); }
 //------------------------------------------------------ 19
 man *F19(FILE *fd)
 { man *p; int n;
 fread(&n,sizeof(int),1,fd);
 p = new man;
 fread (p, sizeof(man),1,fd);
 n = n - sizeof(man);
 p->addr = new char[n];
 fread(p->addr,n,1,fd);
 return p; }
 //------------------------------------------------------ 20
 void F20(FILE *fd, man *p)
 { int n = sizeof(man)+strlen(p->addr)+1;
 fseek(fd,0L,SEEK_END);
 fwrite(&n,sizeof(int),1,fd);
 fwrite (p, sizeof(man),1,fd);
 n = n - sizeof(man);
 fwrite (p->addr, n,1,fd ); }

