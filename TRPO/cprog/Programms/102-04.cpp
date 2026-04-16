#include <string.h>
#include <malloc.h>
/*-----------------------------------------------------
КОСТРУКТОР КОПИРОВАНИЯ
Определить значения переменных и содержимое объектов
после выполнения операций. Подсчитать общее количество
объектов определяемого класса с учетом локальных объектов,
объектов - формальных параметров и результатов, передаваемых
по значению.
-----------------------------------------------------*/
//---------------------------------------------------1
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1);
                         strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); add(t.str+1); }
   ~string() { delete str; }
   string   &operator=(string &r) { delete str; load(r.str); return *this; }
   string   operator+(string &r) { string t(str); t.add(r.str); return t; }
   };
   string EMPTY(string s) { return s; }

void main(){
   string s1,s2("ab"),s3=s2;
   s1=EMPTY(s2);
   }
//---------------------------------------------------2
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1);
                         strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); add(t.str+1); }
   ~string() { delete str; }
   string   &operator=(string &r) { delete str; load(r.str); return *this; }
   string   operator+(string &r) { string t(str); t.add(r.str); return t; }
   };
   string &EMPTY(string &s) { return s; }

void main(){
   string s1,s2("ab"),s3=s2;
   s1=EMPTY(s2);
   }
//---------------------------------------------------3
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1);
                         strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); add("???"); }
   ~string() { delete str; }
   string   &operator=(string &r) { delete str; load(r.str); return *this; }
   string   operator+(string &r) { string t(str); t.add(r.str); return t; }
   };
   string &EMPTY(string &s) { return s; }

void main(){
   string s1,s2("ab"),s3=s2;
   s1=s2+s2;
//---------------------------------------------------4
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
                         strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); add("???"); }
   ~string() { delete str; }
   string   &operator=(string &r) { delete str; load(r.str); return *this; }
   string   operator+(string &r) { string t=*this; t.add(r.str); return t; }
   };
   string &EMPTY(string &s) { return s; }

void main(){
   string s1,s2("ab"),s3=s2;
   s1=s2+s2;
   }
//---------------------------------------------------5
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
                         strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); add("+"); }
   ~string() { delete str; }
   string   &operator=(string &r) { delete str; load(r.str); return *this; }
   friend   string   operator+(string one, string &two) { one.add(two.str); return one; }
   };

void main(){
   string s1,s2("ab"),s3=s2;
   s1=s2+s3;
   while(1);
   }
//---------------------------------------------------6
class S { int val;
public:
   S (int v0) { val = v0; }
   S(S &r) { val = r.val*2; }
   S operator+(S x) { x.val += val; return x; }
    };
void main(){
   S a(5),b=a,c(0);
   c=a+b;
   }
//---------------------------------------------------7
class S { int val;
public:
   S (int v0) { val = v0; }
   S(S &r) { val = r.val*2; }
   S operator-(S &x) { S tmp=*this; tmp.val -= x.val; return tmp; }
   };

void main(){
   S a(5),b=a,c(0);
   c=b-a;
   }
