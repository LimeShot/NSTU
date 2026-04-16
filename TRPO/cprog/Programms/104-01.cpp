#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;
//-----------------------------------------------------------104-01.cpp
class string1{
	char *str;
	void load(char *s)    { str=strdup(s); }
	void add(char *s)     { str=(char*)realloc(str,strlen(str)+strlen(s)+1);
							strcat(str,s); }
	int find(char *s)     { 
			int i,k;
			for (k=0; str[k]!=0; k++){
				for (i=0; s[i]!=0 && s[i]==str[k+i]; i++);
				if (s[i]==0) return i;
				}
		return -1;}
	int cmp(string1 &t)    { return strcmp(str,t.str); }
//-----------------------------------------------------------
public:
	string1(){ load(""); }
	string1(char *s){ load(s); }
	string1(string1 &t){ load(t.str); }
	~string1() { delete []str; }
//-----------------------------------------------------------
	string1   &operator=(string1 &r) { delete []str; load(r.str); return *this; }
	string1   operator+(char *c) { string1 t(str); t.add(c); return t; }
	string1   operator+(string1 &r) { string1 t(str); t.add(r.str); return t; }
	friend string1 operator+(char *s, string1 &t)
		{ string1 x(s); x.add(t.str); return x; }
//-----------------------------------------------------------
	int operator==(string1 &t) { return cmp(t)==0; }
	int operator!=(string1 &t) { return cmp(t)!=0; }
	int operator< (string1 &t) { return cmp(t)< 0; }
	int operator<=(string1 &t) { return cmp(t)<=0; }
	int operator> (string1 &t) { return cmp(t)> 0; }
	int operator>=(string1 &t) { return cmp(t)>=0; }
//-----------------------------------------------------------
	char operator[](int k){ if (k<0 || k>=strlen(str)) return '?';
		return str[k]; }
	int operator[](char *c){ return find(c); }
	int operator[](string1 &t){ return find(t.str); }
//-----------------------------------------------------------
	string1 operator()(int n1, int n2=-1){
		if (n2==-1) n2=strlen(str);
		if (n1<0 || n2<0 || n1>strlen(str) || n2>strlen(str) || n1>n2)
			{ return string1(""); }
	char c=str[n2]; str[n2]=0;
	string1 x(str+n1);
	str[n2]=c;
	return x; }
//-----------------------------------------------------------
	friend ostream &operator<<(ostream &IO, string1 &t){
		IO << t.str; return IO; }
	friend istream &operator>>(istream &IO, string1 &t){
		char c[1000];
		IO.getline(c,1000); delete []t.str; t.str=strdup(c);
		return IO; }
	};




