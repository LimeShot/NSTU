#include <stdio.h>
#include <typeinfo.h>
//-------------------------------------------------113-01.cpp
// Идентификация типов и их преобразование
class A{ public: virtual	void F(){ }};
class B: public A{};
class C: public A{};
class D {};

void main(){
	A aa; B bb;
	if (typeid(A)!=typeid(B)) puts("A!=B");
	puts(typeid(A).name());		// Выведет "class A"
	puts(typeid(B).name());		// Выведет "class B"
	puts(typeid(aa).name());	// Выведет "class A"
	puts(typeid(bb).name());	// Выведет "class B"
	A *p=&bb;					// Преобразование указателя к БК
	puts(typeid(p).name());		// Выведет "class A*"
	puts(typeid(*p).name());	// Выведет "class B"
	A *p1=dynamic_cast<A*>(&bb);// Преобразование ПК к БК (B->A)
	B *p2=dynamic_cast<B*>(p1); // Преобразование БК к ПК (A->B)
	C *p3=dynamic_cast<C*>(p1); // Преобразование БК к ПК (A->C)
	D *p4=dynamic_cast<D*>(p1); // Преобразование ???  (A->D) 
	if (p3==NULL) puts("p3==NULL"); // Выведет "p3==NULL"
	if (p4==NULL) puts("p4==NULL");	// Выведет "p4==NULL"
}