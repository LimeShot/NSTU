//-----------------------------------------------------103-03.cpp
#include <stdio.h>
#include <string.h>
#include <malloc.h>
//---------------------------------------------------1
class string{
   char *str;
   void load(char *s)  { str=strdup(s); }
void add(char *s){ str=(char*)realloc(str,strlen(str)+strlen(s)+1); strcat(str,s); }
   int find(char *s)   { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)  { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   char   operator [](int n) { return n>=strlen(str) ? '?' : str[n]; }
   string &operator()(char c, int n0, int n1){
      for (int i=n0; i<=n1 && i<strlen(str); i++) str[i]=c;
      return *this;
      }
   };
   void main(){
   string s1("abcdefg"),s2("01234");
   s2(s1(s2[3],2,4)[0],1,3);
   }
//---------------------------------------------------2
class string{
   char *str;
   void load(char *s)    { str=strdup(s); }
   void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1); strcat(str,s); }
   int find(char *s)     { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)    { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string operator+(string &r) { string t(str); t.add(r.str); return t; }
   string operator()(int n0, int n1){
      if (n1 >= strlen(str)) n1=strlen(str)-1;
      char c=str[n1+1]; str[n1+1]='\0';
      string t(str+n0);
      str[n1+1]=c;
      return t;
      }
   };
   void main(){
   string s1("abcdefg"),s2("01234"),s3;
   s3=s1(0,2)+s2(2,4);}
//---------------------------------------------------3
class string{
   char *str;
   void load(char *s)   { str=strdup(s); }
void add(char *s) { str=(char*)realloc(str,strlen(str)+strlen(s)+1);
strcat(str,s); }
   int find(char *s)    { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)   { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s)   { load(s); }
   string(string &t) { load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string   operator+(string r) { r.add(str); return r; }
   };
   void main(){
   string s1("abc"),s2("012"),s3;
   s3=s1+s2+s2;}
//---------------------------------------------------4
class string{
   char *str;
   void load(char *s)  { str=strdup(s); }
void add(char *s){ str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)   { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t)  { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   friend string operator+(string one, string &two) 
{ one.add(two.str); return one; }
   };
   void main(){
   string s1("abc"),s2("012"),s3;
   s3=s1+s2+s1; }
//---------------------------------------------------5
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string &operator+(char *s) { add(s); return *this; }
   string &operator+(string &two) { add(two.str); return *this; }
   };
   void main(){
   string s1("ab"),s2("12"),s3;
   (s3=s1+s2+"zz")+s1;}
//---------------------------------------------------6
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string operator+(char *s) { string two(s); two.add(str); return two; }
   string operator+(string two) { two.add(str); return two; }
   };
   void main(){
   string s1("abc"),s2("012"),s3;
   s3=s1+s2+"zz"+s2;}
//---------------------------------------------------7
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(char c, int n){ str=new char[n+1]; 
for (str[n--]='\0'; n>=0; n--) str[n]=c; }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string &operator()(char c, int n0, int n1){
      for (int i=n0; i<=n1 && i<strlen(str); i++) str[i]=c;
      return *this;
      }
   };
   void main(){
   string s1('a',5),s2('b',5),s3("abcd");
   (s3=s1('b',0,2)('c',0,0))('d',4,10); }
//---------------------------------------------------8
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string &operator+(string &t) { 
for (int i=0; i<strlen(str) && i<strlen(t.str); i++)
            str[i]=t.str[i];
            return *this; }
   string   &operator+(char *s)     { string t(s); return *this + t; }
   };
   void main(){
   string s1("abcdefg"),s2("123"),s3;
   (s3=s1+"qwerty")+s2; }
//---------------------------------------------------9
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string &operator()(int n0, int n1) {
            int k=strlen(str); n1++;
            while(n1<=k) str[n0++]=str[n1++];
            return *this; }
   string &operator-(char *s)     {
            int k=strlen(s), n0=find(s);
            if (n0!=-1) (*this)(n0,n0+k-1);
            return *this; }
   };
   void main(){
   string s1("abcdefg"),s2("1234"),s3;
   (s3=s1(2,4)-"bf")-"abc";
   s2-"12345"-"23";}
//---------------------------------------------------10
class string{
   char *str;
   void load(char *s) { str=strdup(s); }
   void add(char *s)  { str=(char*)realloc(str,strlen(str)+strlen(s)+1); 
strcat(str,s); }
   int find(char *s)  { char *p=strstr(str,s); return p==NULL ? -1 : p-str; }
   int cmp(string &t) { return strcmp(str,t.str); }
public:
   string(){ load(""); }
   string(char *s){ load(s); }
   string(string &t){ load(t.str); }
   ~string() { delete str; }
   string &operator=(string &r) { delete str; load(r.str); return *this; }
   string &operator()(int n0, int l) {
            int k=strlen(str);
            int n1=n0+l;
            while(n1<=k) str[n0++]=str[n1++];
            return *this; }
   int   operator[](char *s) { return find(s); }
   };
   void main(){
   string s1("abcdefg"),s2("12345678");
   s1(s1["def"],2);
   int n=s1["cf"];
   s2(s2["45"],2),s2(s2["36"],2); }

