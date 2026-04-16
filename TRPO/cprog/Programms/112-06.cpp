//---------------------------------------------------112-06.cpp
//---------------------------------------------------1
class A{   int val;
public:
      A(int n=0) { val = n; }
        int get() { return val; }
      A operator++(){ A t=*this; val++; return t; }
      };

class INC : public A {
public:
      INC(int n) : A(n+1) {}
      int get() { return A::get()+1; }
      };

void main(){
   A a(10); INC b(12);
   A x=a++;
   A y=b++;
   int z=(b++).get();
   }
//---------------------------------------------------2
class A{   int val;
public:
      A(int n=0) { val = n; }
      A operator++(){ A t=*this; val++; return t; }
      };

class INC : public A {
public:
      INC(int n) : A(n+1) {}
      INC operator++(){ A::operator++(); return *this; }
      };

void main(){
   A a(10); INC b(12);
   A x=a++;

   INC y=b++;
   A z=(*(A*)&b)++;
   }
//---------------------------------------------------3
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A operator+(A &two){ A t=*this; t.val+=two.val; return t; }
      A operator-(A &two){ A t=*this; t.val-=two.val; return t; }
      };

class ABS : public A {
public:
      ABS(int n=0) : A(n<0 ? -n : n) {}
      ABS operator-(ABS &two){
         ABS t=*this; t.val-=two.val;
         if (t.val<0) t.val=-t.val;
         return t; }
      };

void main(){
   A a1(10),a2(-5),a3,a4; ABS b1(-6),b2(12),b3,b4;
   a3=a1+a2;
   a4=a1-a2;
   b3=*(ABS*)&(b1+b2);
   b4=b1-b2;

   }
//---------------------------------------------------4
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator+(A &two){ val+=two.val; return *this; }
      A &operator-(A &two){ val-=two.val; return *this; }
      };

class ABS : public A {
public:
      ABS(int n=0) : A(n<0 ? -n : n) {}
      ABS &operator-(ABS &two){
         val-=two.val;
         if (val<0) val=-val;
         return *this; }
      };

void main(){
   A a1(10),a2(-5),a3,a4,a5; ABS b1(-6),b2(12),b3,b4;
   a1+a2;
   a2-a1;
   b1+b2;
   b2-b1;
   }
//---------------------------------------------------5
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator+(A &two){ val+=two.val; return *this; }
      A &operator-(A &two){ val-=two.val; return *this; }
      };

class ABS : public A {
public:
      ABS(int n=0) : A(n<0 ? -n : n) {}
      ABS &operator+(ABS &two){
         A::operator+(two);
         return *this; }

      ABS &operator-(ABS &two){
         A::operator-(two);
         if (val<0) val=-val;
         return *this; }
      };

void main(){
   A a1(10),a2(-5),a3,a4; ABS b1(-6),b2(12),b3,b4;
   a1+a2;
   a2-a1;
   b1+b2;
   b2-b1;
   }
//---------------------------------------------------6
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator+(A &two){ val+=two.val; return *this; }
      A &operator-(A &two){ val-=two.val; return *this; }
      };

class SIGN : public A {
      int s;
public:
      SIGN(int n=0) : A(n<0 ? -n : n) { s=(n<0); }
      SIGN &operator+(SIGN &two){
		 if (s==two.s) A::operator+(two);
		 else {
			A::operator-(two);
			if (val<0) { val=-val; s=!s; }
			}
         return *this; }

      SIGN &operator-(SIGN &two){
         two.s=!two.s;
		 operator-(two);
         two.s=!two.s;
         return *this; }
      };

void main(){
   A a1(10),a2(5),a3,a4; SIGN b1(-6),b2(12),b3,b4;
   a1+a2;
   a2-a1;
   b1+b2;
   b2-b1;
   }
//---------------------------------------------------7
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator*(A &two){ val*=two.val; return *this; }
      A &operator/(A &two){ val/=two.val; return *this; }
      };

class SIGN : public A {
      int s;
public:
      SIGN(int n=0) : A(n<0 ? -n : n) { s=(n<0); }
      SIGN &operator*(SIGN &two){
         s=(s!=two.s);
         A::operator*(two);
         return *this; }

      SIGN &operator/(SIGN &two){
         s=(s!=two.s);
         A::operator/(two);
         return *this; }
      };

void main(){
   A a1(10),a2(5),a3,a4; SIGN b1(-6),b2(12),b3,b4;
   a1*a2;
   a2/a1;
   b1*b2;
   b2/b1;
   }
//---------------------------------------------------8
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator*(A &two){ val*=two.val; return *this; }
      A &operator/(A &two){ val/=two.val; return *this; }
      };

class SIGN : public A {
      int s;
public:
      SIGN(int n=0) : A(n<0 ? -n : n) { s=(n<0); }
      SIGN &operator*(SIGN &two){
         s=(s!=two.s);
         A::operator*(two);
         return *this; }

      SIGN &operator/(SIGN &two){
         s=(s!=two.s);
         A::operator/(two);
         return *this; }
      };

void main(){
   A a1(10),a2(15),a3,a4; SIGN b1(-6),b2(12),b3,b4;
   a1*A(2);
   a2/A(-3);
   b1*SIGN(7);
   b2/SIGN(-2);
   }
//---------------------------------------------------9
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator+(A &two){ val+=two.val; return *this; }
      A &operator-(A &two){ val-=two.val; return *this; }
      };

class MOD : public A {
      int s;
public:
      MOD(int n=0, int m=10) : A(n)
         { s=m; if (val>=s) val%=s; else while(val<0) val+=s; }
      MOD &operator+(MOD &two){
         A::operator+(two);
         if (val>=s) val%=s; else while(val<0) val+=s;
         return *this; }

      MOD &operator-(MOD &two){
         A::operator-(two);
         if (val>=s) val%=s; else while(val<0) val+=s;
         return *this; }
      };

void main(){
   A a1(10),a2(15),a3,a4; MOD b1(6,10),b2(12,20),b3(-6,10),b4;
   a1+A(2);
   a2-A(-3);
   b1+MOD(7,10);
   b2-MOD(15,20);
   b3-MOD(6,10);
   }
//---------------------------------------------------10
class A{
protected:
      int val;
public:
      A(int n=0) { val = n; }
      A &operator*(A &two){ val*=two.val; return *this; }
      A &operator/(A &two){ val/=two.val; return *this; }
      };

class MOD : public A {
      int s;
public:
      MOD(int n=0, int m=10) : A(n)
         { s=m; if (val>=s) val%=s; else while(val<0) val+=s; }
      MOD &operator*(MOD &two){
         A::operator*(two);
         while(val>=s) val-=s;
         return *this; }
      };

void main(){
   A a1(10),a2(15),a3,a4; MOD b1(6,10),b2(15,20),b3(-6,10),b4;
   a1*A(2);
   a2/A(-3);
   b1*MOD(7,10);

   b2/MOD(25,20);
   b3/MOD(2,10);
   }
