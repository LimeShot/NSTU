#include <stdio.h>
//-------------------------------------------------114-05.cpp
//---------------------------------------------------1
class A{   int val;
public:
      A(int n=0) { val = n; }
      virtual int get() { return val; }
      virtual int operator++(){ int t=val++; return t; }
      };

class INC : public A {
public: INC(int n) : A(n+1) {}
      int get() { return A::get()+1; }
      };

void main(){
   A a(5),c(6); INC b(7);
   A *p[]={&a, &b, &c, NULL};
   int x=0, y=0, i=0;
   for (i=0; p[i]!=NULL; i++) x += p[i]->get();
   for (i=0; p[i]!=NULL; i++) y += (*p[i])++;
   }
//---------------------------------------------------2
class A{   int val;
public:
      A(int n=0) { val = n; }
      int get() { return val; }
      virtual A operator++(){ A t=*this; val++; return t; }
      };

class INC : public A {
public:INC(int n) : A(n+1) {}
      A operator++(){ A::operator++(); return *this; }
      };

void main(){
   A a(5),c(6); INC b(7);
   A *p[]={&a, &b, &c, NULL};
   int s=0, i=0;
   for (i=0; p[i]!=NULL; i++) s += (*p[i])++.get();
   A x=a++;
   A y=b++;
   A z=(*(A*)&b)++; }
//---------------------------------------------------3
class A{   int val;
public:
      A(int n=0) { val = n; }
      virtual int get() { return val; }
      A operator++(){ A t=*this; val++; return t; }
      };

class INC : public A {
public:INC(int n) : A(n+1) {}
      int get() { return A::get()+1; }
      };

class DEC : public A {
public:DEC(int n) : A(n-1) {}
      int get() { return A::get()-1; }
      };


void main(){
   A a(5); INC b(7); DEC c(6);
   A *p[]={&a, &b, &c, NULL};
   int s=0, i=0;
   for (i=0; p[i]!=NULL; i++) (*p[i])++;
   for (i=0; p[i]!=NULL; i++)  s += p[i]->get();
   }
//---------------------------------------------------4
class A{
protected:
      int val,cnt;
public:
      A() { val=cnt=0; }
      virtual A &operator+(int n) { cnt++; return *this; }
      virtual operator int(){ return cnt; }
      };

class B : public A {
public: A &operator+(int n) { cnt++; val+=n; return *this; }
      };

class C : public A {
public: A &operator+(int n) {
         if (cnt++ ==0) val=n;
         else if (n>val) val=n;
         return *this; }
      };


void main(){
   A a; B b; C c;
   A *p[]={&a,&b,&c,NULL};
   for (int i=0; p[i]!=NULL; i++) *p[i]+5+3+7;
   b+2;
   c+2+1; }
//---------------------------------------------------5
class A{
protected:
      int val,cnt;
public:
      A() { val=cnt=0; }
      virtual A &operator+(int n) { cnt++; return *this; }
      virtual operator int(){ return 0; }
      };

class B : public A {
public: virtual A &operator+(int n) { cnt++; val+=n; return *this; }
      operator int(){ return val/cnt; }
      };

class C : public A {
public: A &operator+(int n) {
		 if (cnt++ ==0) val=n;
         else if (n>val) val=n;
         return *this; }
      operator int(){ return val; }
      };


void main(){
   A a; B b; C c;
   A *p[]={&a,&b,&c,NULL};
   int v[3];
   for (int i=0; p[i]!=NULL; i++) *p[i]+5+3+8;
   b+1+3;
   c+2;
   for (int i=0; p[i]!=NULL; i++) v[i]=*p[i];
   }
//---------------------------------------------------6
class A{
public:
      virtual int operator[](int n) { return n; }
      virtual operator int(){ return 0; }
      };

class B : public A {
      int *p;
      int sz;
public: B(int A[], int n) { p=A; sz=n;}
      int operator[](int n) { return n>=sz ? 0 : p[n]; }
      operator int(){ return sz; }
      };

class C : public A {
      char *str;
public:
      C(char *s) { str=s; }
      int operator[](int n) { return str[n]-'0'; }
      operator int(){ return strlen(str); }
      };


void main(){
   int G[10]={4,2,5,1,7,4,19,3,2,1};
   A a; B b1(G,10),b2(G,3); C c1("45"), c2("12");
   A *p[]={&a,&b1,&b2,&c1,&c2,NULL};
   int x=0, y, j, i;
   for (i=0; p[i]!=NULL; i++){
         int m=*p[i];
         for (j=0;j<m;j++){
            y = (*p[i])[j];
            if (y>x) x=y;
            }}
   }
//---------------------------------------------------7
class A{
public:
      virtual int operator[](int n) { return n; }
      virtual operator int(){ return 0; }
      };

class B : public A {
      int *p;
      int sz;
public:
      B(int A[], int n) { p=A; sz=n;}
      int operator[](int n) { return n>=sz ? 0 : p[n]; }
      operator int(){ return sz; }
      };

class C : public A {
      char *str;
public:
      C(char *s) { str=s; }
      int operator[](int n) { return str[n]-'0'; }
      operator int(){ return strlen(str); }
      };


void main(){
   int G[10]={3,2,1};
   A a; B b1(G,3),b2(G,2); C c1("45"), c2("12");
   A *p[]={&a,&c1,&c2,&b1,&b2,NULL};
   int x=0, j, i;
   for (i=0; p[i]!=NULL; i++){
         int m=*p[i];
         for (j=0;j<m;j++)
            x += (*p[i])[j];
         }}
//---------------------------------------------------8
class A{
public:
      virtual int operator[](int n) { return n; }
      virtual operator int(){ return 0; }
      };

class B : public A {
      int *p;
      int sz;
public:
      B(int A[], int n) { p=A; sz=n;}
      int operator[](int n) { return n>=sz ? 0 : p[n]; }
      operator int(){ return sz; }
      };

class C : public A {
      char *str;
public:
      C(char *s) { str=s; }
      int operator[](int n) { return str[n]-'0'; }
      operator int(){ return strlen(str); }
      };

void main(){
   int G[10]={10,9,8,7,6,5,4,3,2,1};
   A a; B b1(G,10),b2(G,3); C c1("4567"), c2("1234");
   A *p[]={&a,&c1,&c2,&b1,&b2,NULL};
   int x=0, y=0, z=0, i=0;
   for (i=0; p[i]!=NULL; i++){
         z += (*p[i])[0];
         x += (*p[i])[i];
         y += *p[i];
         }}
//---------------------------------------------------9
class A{
public:
      virtual int operator[](int n) { return n; }
      virtual operator int(){ return 0; }
      };

class B : public A {
      int val;
public: B(int n) { val=n; }
      int operator[](int n) {
         int m=val;
         while (n--!=0) m=m/10;
         return m%10;   }
      operator int(){
         int n=0,m=val;
         while (m!=0) m=m/10,n++;
         return n; }
      };

class C : public A {
      char *str;
public: C(char *s) { str=s; }
      int operator[](int n) { return str[n]-'0'; }
      operator int(){ return strlen(str); }
      };


void main(){
   A a; B b1(25),b2(36); C c1("4567"), c2("1234");
   A *p[]={&a,&b1,&b2,&c1,&c2,NULL};
   int x=0, y=0, z=0, i=0;
   for (i=0; p[i]!=NULL; i++){
         x += (*p[i])[0];
         y += *p[i];
         }}
//---------------------------------------------------10
class A{
public:
      virtual int get() { return 1; }
      virtual operator int(){ return 0; }
      };

class B : public A {
      int val;
public: B(int n) { val=n; }
        int get() { return val; }
      operator int(){ return 1; }
      };

class C : public A {
      char *str;
public: C(char *s) { str=s; }
        int get() { return strlen(str); }
      operator int(){ return 2; }
      };


void main(){
   A a; B b1(5),b2(6); C c1("abc"), c2("1234");
   A *p[]={&a,&b1,&b2,&c1,&c2,NULL};
   int x=0, y=0, i=0;
   for (i=0; p[i]!=NULL; i++){
         x += p[i]->get();
         y += *p[i];
         }}
//---------------------------------------------------11
class A{   int val;
public:
      A(int n=0) { val = n; }
      virtual int get() { return val; }
      virtual int operator++(){ int t=val++; return t; }
      };

class INC : public A {
public: INC(int n) : A(n+1) {}
        int get() { return A::get()+1; }
      };

A a(5),c(6); INC b(7);
struct list {
   A *pd;
   list *next;
   }   c1={&c,NULL}, b1={&b,&c1}, a1={&a,&b1}, *h=&a1;

void main(){
   list *q;
   int x=0, y=0, i=0;
   for (q=h; q!=NULL; q=q->next)
         x += q->pd->get();
   for (q=h; q!=NULL; q=q->next)
         y += (*q->pd)++;
   }
