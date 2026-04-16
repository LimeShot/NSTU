/*-------------------------------------------------------
ПЕРЕОПРЕДЕЛЕНИЕ ОПЕРАТОРОВ
Определить значения переменных, количество и содержимое объектов
после выполнения операций
-----------------------------------------------------*/
//---------------------------------------------------1-1
class S { int val;
public:
   S (int v0) { val = v0; }
   S INC() { S t = *this; t.val++; return t; }
    };
void main(){
   S x(5) ,y (0), z (0);
y = x.INC(); z = x.INC().INC(); }
//---------------------------------------------------1-2
class S { int val;
public:
   S (int v0) { val = v0; }
   S &INC() { val++; return *this; }
    };
void main (){
   S x(5), y(0), z(0);
   y = x.INC(); z = x.INC().INC(); }
//---------------------------------------------------1-3
class S { int val;
public:
   S (int v0) { val = v0; }
   S *INC() { val++; return this; }
    };
void main (){
   S x(5),y ( 0),z(0);
   y = *x.INC(); z = *(x.INC()->INC());}
//---------------------------------------------------1-4
class S { int val;
public:
   S (int v0) { val = v0; }
   S &operator+(int m) { val+=m; return *this; }
    };
void main(){
   S x(5),y(0);
   y=x+5+6;
   }
//---------------------------------------------------1-5
class S { int val;
public:
   S(int v0) { val = v0; }
    S operator+(int m) { S z(0); z=*this; z.val+=m; return z; }
    };
void main(){
   S a(5),b(0);
   b=a+5+6; }
//---------------------------------------------------1-6
class S { int val;
public:
   S (int v0) { val = v0; }
   S operator+(S x) { x.val += val; return x; }
    };
void main(){
   S a(5),b(6),c(0);
   c=a+b; }
//---------------------------------------------------1-7
class S { int val;
public:
   S (int v0) { val = v0; }
   S &operator+(S &m) { val += m.val; return *this; }
    };
void main(){
   S a(5),b(6),c(0);
   c=a+b+b; }
//---------------------------------------------------1-8
class S { int val;
public:
   S(int v0) { val = v0; }
    S &operator+(S &m) { m.val += val; return *this; }
    };
void main(){
   S a(5),b(6),c(0);
   c=a+b+b; }
//---------------------------------------------------1-9
class S { int val;
public:
   S(int v0) { val = v0; }
   S &operator+(S &s) { s.val += val; return s; }
    };
void main(){
   S a(5),b(6),c(0);
   c=a+b+b; }
//---------------------------------------------------1-10
class S { int val;
public:
   S(int v0) { val = v0; }
   S operator+(S m) { m.val += val; return m; }
    };
void main(){
   S a(5),b(6),c(0);
   c=a+b+b; }
//---------------------------------------------------1-11
class S { int val;
public:
   S (int v0) { val = v0; }
   S operator+(int two)   { S res = *this; res.val += two; return res; }
    S operator+(S two) { return *this + two.val; }
    };
void main(){
   S x(5),y(0), z(0);
   y = x + 5; z = x + y;
   }
//---------------------------------------------------1-12
class S { int val;
public:
   S(int v0) { val = v0; }
   S operator++(int) { S res = *this; val++ ; return res; }
    };
void main(){
   S x(5),y(0), z(0);
   y = x++; z = x++; }
//---------------------------------------------------1-13
class S { int val;
public:
   S(int v0) { val = v0; }
    S operator++() { val ++ ; return *this; }
    };
void main(){
   S x(5),y(0), z(0);
   y = ++x; z = ++x;
   }
//---------------------------------------------------1-14
class S { int val;
public:
   S(int v0) { val = v0; }
   S operator-(int two) { S res = *this; res.val -= two; return res; }
   S operator-(S two) { return *this - two.val; }
    };
void main(){
   S x(5),y(0), z(0);
   y = x - 5; z = x - y;
   }
//---------------------------------------------------1-15
class S { int val;
public:
   S(int v0) { val = v0; }
   S operator-(int two) { S res(two); res.val -= val; return res; }
    S operator-(S two) { two.val -= val; return two; }
   };
void main(){
   S x(5),y(0), z(0);
   y = x - 2; z = x - y; }
//---------------------------------------------------1-16
class S { int val;
public:
   S(int v0) { val = v0; }
    S &operator-(int two) { val -= two; return *this; }
    S &operator-(S two) { val -= two .val; return *this; }
    };
void main(){
   S x(5),y(0), z(0);
   y = x - 2; z = x - y; }
//---------------------------------------------------1-17
class S { int val;
public:
   S(int v0) { val = v0; }
    S &operator-(int two) { val -= two; return *this; }
   S &operator-(S &two) { val -= two .val; return two; }
    };
void main(){
   S x(5),y(0), z(0);
   y = x - 2; z = x - y;
   }
