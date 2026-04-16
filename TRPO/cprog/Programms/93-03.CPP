#include <stdio.h>
#include <string.h>
#include <math.h>
//------------------------------------------------------93-03.cpp
//------Сортировка массива структур по разным критериям
struct user{
	char name[20];
	int account;
	double time;
}	S[]={
	{"John",2775,13.74},
	{"Alex",4765,10.1},
	{"Martin",1122,0.0},
	{"Billy",3344,7.5},
	{"Larry",1222,5.5},
	{"",0,0}};
//-------- Вставка погружением
// cmp - указатель на функцию сравнения двух struct user
void sort(user A[], int (*cmp)(user&,user&)){
	for (int i=1;A[i].name[0]!=0;i++)
		for(int j=i; j>0 && (*cmp)(A[j],A[j-1])<0; j--)
		{ user c=A[j];
		A[j]=A[j-1];
		A[j-1]=c; }
	}
//--------- функция сравнения по имени
int cmp_name(user &u1, user &u2){
	return strcmp(u1.name,u2.name);	
	}
//--------- функция сравнения по account
int cmp_account(user &u1, user &u2){
	return u1.account - u2.account;	
	}
//--------- функция сравнения по time
int cmp_time(user &u1, user &u2){
	return u1.time - u2.time;	
	}
void show(user A[]){
	puts("-------------------------");
	for (int i=0;A[i].name[0]!=0;i++)
		printf("%20s %4d %5.3lf\n",A[i].name,A[i].account,A[i].time);
	}

void main(){
	show(S);
	sort(S,cmp_name);
	show(S);
	sort(S,cmp_account);
	show(S);
	sort(S,cmp_time);
	show(S);
	}