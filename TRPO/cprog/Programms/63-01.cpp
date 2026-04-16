#include <stdio.h>
struct list{
	char *val;
	list *next;
};

//------------------------------------------------------63-01.cpp
//------ формальный параметр - заголовок списка
 void F1(list *p) {
 for (; p!=NULL; p=p->next) puts(p->val);
 }

list A={"a list",NULL}, B={"is",&A}, C={"this",&B}, *ph=&C;
void main(){
F1(ph);
}
