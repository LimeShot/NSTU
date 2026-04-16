#include <stdio.h>
struct list{
	int val;
	list *next;
};
void show(list *p) {
for (; p!=NULL; p=p->next) printf("%d ",p->val);
}

//---------------------------------------------------------63-03.cpp
// Представление очереди и стека односвязным списком
// Включение в конец списка - помещение в очередь
void In(list *&ph,int v){
	list *q=new list,*p;
	q->next=NULL; 
	q->val=v;
	if (ph==NULL) ph=q;		// список пуст - единственный
	else {					// цикл поиска конца списка
		for (p=ph; p->next!=NULL; p=p->next);
		p->next=q;			// следующий за последним - новый
	}}
// Включение в начало списка - посмещение в стек
void PUSH(list *&ph,int v){
	list *q=new list;
	q->next=NULL; 
	q->val=v;
	q->next=ph;				// следующий за новым - бывший первый
	ph=q; }					// новый теперь первый

int Out(list *&ph){
	if (ph==NULL) return -1;
	list *q=ph;				// запомнить текущий
	ph=ph->next;			// сдвинуться к следующему	
	int v=q->val;
	delete q;				// удалить текущий
	return v;}
// Указатели на первый и последний элементы
// list	*PH[2];  -   заголовок очереди, [0]-первый, [1]-последний
void	In(list *ph[], int v){
	list *p= new list;		// создать элемент списка;
	p->val=v;				// и заполнить его
	p->next=NULL; 			// новый элемент - последний		
	if (ph[0]==NULL)		// включение в пустую очередь
		ph[0]=ph[1]=p; 
	else{					// включение за последним элементом	
		ph[1]->next = p;	// следующий за последним = новый
		ph[1] = p;			// последний = новый 
	}}

int	Out(list *ph[]){ 		// извлечение из очереди 
	if (ph[0]==NULL) 
		return -1; 			// очередь пуста
	list *q=ph[0];			// исключение первого элемента
	ph[0]=q->next;		
	if (ph[0]==NULL) 
		ph[1]=NULL;			// элемент единственный
	int v = q->val;
	delete q; return v; }

void main(){ int v; list *phh=NULL, *ph[2]={NULL, NULL};
In(phh,7); In(phh,5); In(phh,3);
printf("%d ",Out(phh));  
In(phh,12); In(phh,7); In(phh,6);
while ((v=Out(phh))!=-1) printf("%d ",v); 
puts("\n-------------------------");
In(ph,7); In(ph,5); In(ph,3);
printf("%d ",Out(ph));  
In(ph,12); In(ph,7); In(ph,6);
while ((v=Out(ph))!=-1) printf("%d ",v); 
PUSH(phh,7); PUSH(phh,5); PUSH(phh,3);
PUSH(phh,12); PUSH(phh,7); PUSH(phh,6);
puts("\n-------------------------");
while ((v=Out(phh))!=-1) printf("%d ",v); 
}
