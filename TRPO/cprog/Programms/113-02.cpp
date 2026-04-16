//-----------------------------------------------------113-02.cpp
//---------------------------------------------------1
class A{
      int val;
public:
      A(int n=0) { val = n; }
      A operator/(A &two){
         if (two.val==0) throw *this;
         A t=*this;
         t.val/=two.val;
         return t; }
      A operator-(A &two){
         if (val < two.val) throw val - two.val;
         A t=*this;
         t.val-=two.val;
         return t; }
      };

void main(){
   A a(10),b(0),c(12),e,f,g;
   int m=0;
   try {
      e=a/b;
      f=a-c;
       }
   catch (int n) { m=n; }
   catch (A n) { g=n; }
   }
//---------------------------------------------------2
class A{
      int val;
public:
      A(int n=0) { val = n; }
      A operator/(A &two){
         if (two.val==0) throw *this;
         A t=*this;
         t.val/=two.val;
         return t; }
      A operator-(A &two){
         if (val < two.val) throw val - two.val;
         A t=*this;
         t.val-=two.val;
         return t; }
      };

void main(){
   A a(10),b(0),c(12),e,f,g;
   int m=0;
   try {
      f=a-c;
      e=a/b;
       }
   catch (int n) { m=n; }
   catch (A n) { g=n; }
   }
//---------------------------------------------------3
class A{
      int val;
      int top;
public:
      A(int n=10) { top = n; val=0; }
      A operator=(int v){
         if (v >= top) throw v;
         val=v;
         return *this; }
      A operator+(A &two){
         if (val + two.val >=top) throw *this;
         A t=*this;
         t.val+=two.val;
         return t; }
      };

void main(){
   A a(10),b(15),c(20);
   int m=0;
   try {
      a=8;
      b=18;
      c=25;
      a=a+c;
      b=a+c;
       }
   catch (int n) { c=10; }
   catch (A n) { c=1; }
   }
//---------------------------------------------------4
class A{
      int val;
      int top;
public:
      A(int n=10) { top = n; val=0; }
      A operator=(int v){
         if (v >= top) throw v;
         val=v;
         return *this; }
      A operator+(A &two){
         if (val + two.val >=top) throw *this;
         A t=*this;
         t.val+=two.val;
         return t; }
      };

void main(){
   A a(10),b(15),c(20);
   int m=0;
   try {
      a=8;
      b=12;
      c=15;
      a=a+c;
      b=a+c;
       }
   catch (int n) { c=10; }
   catch (A n) { c=n; }
   }

//---------------------------------------------------5
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)       { str=(char*)realloc(str,strlen(str)+strlen(s)+1); strcat(str,s); }
   int find(char *s)      { char *p=strstr(str,s);
                        if (p==NULL) throw str;
                        return p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   char   operator [](int n) {
                           if (n>=strlen(str)) throw *this;
                           return str[n]; }
   int   operator [](char *s) { return find(s); }
   };

   void main(){
   string s1("abcdefg"),s2("01234");
   char *p="***", c1='#',c2='#';
   int n1=0,n2=0;
   try   {
         c1=s1[3];
         c2=s2[10];
         n1=s1["cde"];
         n2=s2["abc"];
         }
   catch (char *s) { p=s; }
   catch (string s){ c1=s[1]; }
   }
//---------------------------------------------------6
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)       { str=(char*)realloc(str,strlen(str)+strlen(s)+1); strcat(str,s); }
   int find(char *s)      { char *p=strstr(str,s);
                        if (p==NULL) throw str;
                        return p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   char   operator [](int n) {
                           if (n>=strlen(str)) throw *this;
                           return str[n]; }
   int   operator [](char *s) { return find(s); }
   };

   void main(){
   string s1("abcdefg"),s2("01234");
   char *p="***", c1='#',c2='#';
   int n1=0,n2=0;
   try   {
         n1=s1["cde"];
         n2=s2["abc"];
         c1=s1[3];
         c2=s2[10];
         }
   catch (char *s) { p=s; }
   catch (string s){ c1=s[1]; }
}
