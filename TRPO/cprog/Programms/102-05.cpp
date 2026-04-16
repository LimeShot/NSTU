//-----------------------------------------------------102-05.cpp
// Статические элементы класса
//---------------------------------------------------1
class A{
		int val;
static	int cnt,m;
public:
    A(int n=0) { val = n; cnt++; if (cnt>m) m=cnt; }
    A(A &r) { val = r.val; cnt++; if (cnt>m) m=cnt; }
	~A() { cnt--; }
    A operator++(){
		A t=*this;
		val++;
		return t; }
static	int count(){ return m; }
	};
int F(){ A c(14); c++; return A::count(); }

int A::m=0,A::cnt=0;
A gl(10);

void main(){
   int e,f,g;
   g=A::count();
   A a(10),b(12);
   a++; b++;
   f=A::count(); e=F(); }
//---------------------------------------------------2
class A{
		int val;
static	int cnt;
public:
	A(int n=0) { val = n; cnt++; }
    A(A &r) { val = r.val; cnt++; }
    ~A() { /* Это исключено cnt--; */ }
    A operator++(){
		A t=*this;
		val++;
		return t; }
static	int count(){ return cnt; }
     };

int F(){ A c(14);
   c++;
   return A::count(); }

int A::cnt=0;
A gl(10);

void main(){
   int e,f,g;
   g=A::count();
   A a(10),b(12);
   a++; b++; f=A::count(); e=F(); }
//---------------------------------------------------3
class A{
		int val;
static	int cnt;
public:
	A(int n=0) { val = n; cnt+=val; }
    A(A &r) { val = r.val; cnt+=val; }
    ~A()	{ cnt-=val; }
    A operator++(){
		A t=*this;
		val++;
		return t; }
static	int count(){ return cnt; }
     };

int F(){ A c(4); c++; return A::count(); }

int A::cnt=0;
A gl(1);

void main(){
   int e,f,g;
   g=A::count();
   A a(3),b(5);
   a++; b++; f=A::count(); e=F(); }
//---------------------------------------------------4
class A{
		int val;
static	int cnt,m;
public:
	A(int n=0) { val = n; cnt++; m+=val; }
    A(A &r) { val = r.val; cnt++; m+=val; }
    ~A()	{ cnt--; m-=val; }
    A operator++(){
		A t=*this;
        val++;
        return t; }
static	int count(){ return m/cnt; }
     };

int F(){ A c(6); c++; return A::count(); }

int A::m=0,A::cnt=0;
A gl(1);

void main(){
   int e,f,g;
   e=A::count();
   A a(3),b(2); a++; b++; f=A::count(); g=F(); }
//---------------------------------------------------5
class A{
		int val;
static	A *all[10];
public:
	A(int n=0) { val = n;
		for (int i=0; i<10; i++)
        if (all[i]==NULL) { all[i]=this; break; }
		}
	A(A &r) { val = r.val;
		for (int i=0; i<10; i++)
			if (all[i]==NULL) { all[i]=this; break; }
		}
    ~A() {
		for (int i=0; i<10; i++)
			if (all[i]==this) { all[i]=NULL; break; }
     }
static int count(){
     int v=0;
     for (int i=0; i<10; i++)
		if (all[i]!=NULL) v++;
			return v; }
static int sum(){
		int v=0;
		for (int i=0; i<10; i++)
			if (all[i]!=NULL) v+=all[i]->val;
		return v; }
	};

A *A::all[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

int F(){
   A c(14),d(16);
   return A::count();
   }
A gl(10);

void main(){
   int e,f,g,h;
   e=A::count();
   A a(10),b(12);
    f=F();
   g=A::count();
   h=A::sum();
   }
//---------------------------------------------------6
class A{
		int val;
static	A *all[10];
public:
	A(int n=0) { val = n;
		for (int i=0; i<10; i++)
			if (all[i]==NULL) { all[i]=this; break; }
    }
    A(A &r) { val = r.val;
		for (int i=0; i<10; i++)
			if (all[i]==NULL) { all[i]=this; break; }
    }
    ~A() {
		for (int i=0; i<10; i++)
			if (all[i]==this) { all[i]=NULL; break; }
	}
static	int max(){
		int v=0;
		for (int i=0; i<10; i++)
			if (all[i]!=NULL && all[i]->val > v) 
				v=all[i]->val;
        return v; }
     };

A *A::all[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

int F(){
   A c(14),d(16);
   return A::max();
   }

A gl(10);

void main(){
   int e,f,g,h;
   e=A::max();
   A a(10),b(12);
    f=F();
   g=A::max();
   }
//---------------------------------------------------7
class A{
		char *str;
static	int cnt,m;
public:
	A(char *p="??????") { str=p; cnt++; m+=strlen(str); }
    A(A &r) { str = r.str; cnt++; m+=strlen(str); }
    ~A() { cnt--; m-=strlen(str); }
    A &operator=(A &R){
		m-=strlen(str);
		str=R.str;
        m+=strlen(str);
		return *this; }
static	int mid(){ return m/cnt; }
     };

int F(){
   A c;
   return A::mid();
   }

int A::m=0,A::cnt=0;
A gl("abcd");

void main(){
   int e,f,g;
   e=A::mid();
   A a("a"),b("b");
   f=A::mid();
    g=F();
   }
