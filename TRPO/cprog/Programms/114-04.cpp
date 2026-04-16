//-----------------------------------------------114-04.cpp
#include <stdio.h>
// Внутрениий полиморфизм - отложенное программирование
class A{
		A *next;	// Внутрениий статический односвязный
static	A *head;	// список объектов
public:
	A()	{
		next=head;	// Включение в начало статического списка
		head=this;
		}
	~A(){			// Деструктор - исключение из списка
		if (head==this) head=head->next;
		else{
			A *p;
			for (p=head; p->next!=this; p=p->next);
			p->next=this->next;
			}
		}
static void show(){
		for (A *p=head; p!=NULL; p=p->next)
			p->F();	//
		}
virtual void G(){ printf("%x:Im A-class\n",this); }
		void F(){  
		G();		// Внутрениий полиморфизм - отложенное
		}			// программирование в производном классе
};

A	*A::head=NULL;	// Статический заголовок списка

class B : A{
	void G(){ printf("%x:Im B-class\n",this);  }
};

class C : A{
	void G(){ printf("%x:Im C-class\n",this);  }
};


B bb;
void main(){
	A::show();
	C cc; A aa;
	A::show();
}