#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
//-------------------------------------------------112-02.cpp
// Конструирование, присваивание, копирование при наследовании
class string1{
	char *str;
public:
	string1(){ str=strdup("");}
	string1(char *s){ str=strdup(s); }
	string1(string1 &T){ str=strdup(T.str); }	// КК
	~string1(){ delete []str; }
	string1 &operator=(string1 &T){			// Присваивание
		delete []str;
		str=strdup(T.str);
		return *this;
		}
	friend ostream&operator<<(ostream &O, string1 &D){
		O << D.str << endl; return O; }
};
class string2 : string1{
	char *str;	
public:
	string2(){ str=strdup("");}
	string2(char c[], char c2[]): string1(c2)
		{ str=strdup(c); }
	string2(string2 &T){
		*(string1*)this=*(string1*)&T;// Присваивание объекта БК	
		str=strdup(T.str); }
	string2 &operator=(string2 &T){
		*(string1*)this=*(string1*)&T;// Присваивание объекта БК
		delete []str;
		str=strdup(T.str);
		return *this;
		}							// Переопределение вывода в поток
	friend ostream&operator<<(ostream &O, string2 &D){
		O << *(string1*)&D << D.str << endl; return O; }
	};								// Вызов операции в БК

void main(){
	string1 A("aaaaaaa");
	string2 B("bbbb","cccc"),C,D(B);
	C=B;
	cout << A << B << C << D;
	}