#include <stdio.h>
#include <conio.h>
#include <time.h>

//--------------Шаблон класса очереди, содержащей адреса объектов
template <class T> class queue{			
public:
	struct elem{
	T *data;
	elem *next;
	elem(T *s){ data=s; next=NULL;}
	};
elem *fst,*lst;
queue(){  fst=lst=NULL;}
~queue(){
	 elem *q;
	 while(fst!=NULL){
		 q=fst; fst=fst->next;
		 delete q;
		}}
T *out(){
	if (fst==NULL) return NULL;
	elem *q=fst;
	fst=fst->next;
	T *foo=q->data;
	delete q;
	return foo;}
void in(T *s){
	elem *q=new elem(s);
	if (fst==NULL) fst=lst=q;
	else { lst->next=q; lst=q; }
	}
void remove(T *s){			// Удаление объекта из очереди
	elem *q;
	if (fst==NULL) return;	// по заданому адресу
	if (fst->data==s) out();
	else {
		for (q=fst; q->next->data!=s; q=q->next);
		if (q->next==lst) lst=q;
		q->next=q->next->next;
		}
	}
};

struct mes{
	int		type;			// Тип сообщения
	long	value;			// Значение сообщения
	void	*addr;			// Адрес обекта
	mes(int t0, long v0=0, void *a=NULL)
		{ type=t0; value=v0;  addr=a; }
	};

#define wasBorn 0			// Сообщение - создать процесс
#define killMe  1			// Сообщение - уничтожить процесс
#define keyBrd  2			// Сообщение от клавиатуры

class programm0{			// Начало класса "программа" - очередь сообщений
public:
	queue<mes> M;
	};

class process{				// Класс "процесс" - указатель объекта "программа"
	programm0 *prg;
public:						// Конструктор: процесс порождается программой
	process(programm0 *p0=NULL){
		prg=p0;				
		send(wasBorn,0,this);
	}						// Конструктор: процесс порождается процессом
	process(process *parent){
		prg=parent->prg;
		send(wasBorn,0,this);
	}
	void send(int t0,long v0=0,void *a0=NULL){ prg->M.in(new mes(t0,v0,a0)); }
							// Виртуальная функция обработки сообщения
	virtual int procMes(mes &m){ return 0; }
	virtual ~process(){}
	};

class programm : public programm0{	
	queue<process> P;		// Класс "программа" - очередь процессов
public:
	void run(){				// Диспетчер сообщений
		while(1){			// Сообщения от источника - клавиатуры
		M.in(new mes(keyBrd,getch()));
		mes *mm;			// Пока очередь сообщений не пуста
		while((mm=M.out())!=NULL){	
			printf("type=%d val=%ld addr=%lx\n",mm->type,mm->value,mm->addr);
							// Сообщение о порождении процесса
							// поставить в очередь
			if (mm->type==wasBorn)P.in((process*)mm->addr);
			else
			if (mm->type==killMe) {
							// Сообщение об уничтожении процесса
							// удалить из очереди и уничтожить объект
				process *q=(process*)mm->addr;
				P.remove(q);
				delete q;
				}
			else			// Иначе - пропустить через все процессы
			for (queue<process>::elem *q=P.fst; q!=NULL; q=q->next)
				if (q->data->procMes(*mm)) break;
			delete mm;
			}}}
	};

// Вторичный процесс. При получении '-' просит уничтожить себя,
// При получении '?' - сообщает о себе
class PRC2 : process{
public:
	PRC2(process *pp):process(pp){}
	int procMes(mes &m){		
		if (m.type==keyBrd){
			if  (m.value=='-') { send(killMe,0,this); return 1; }
			if  (m.value=='?') { printf("A am %lx\n",this); }
			}
		return 0;
		}};
// Первичный процесс. При получении '+' порождает вторичный процесс
class PRC1 : process{
public:
	PRC1(programm *pp):process(pp){}
	int procMes(mes &m){
		if (m.type==keyBrd){
			if  (m.value=='+') new PRC2(this);
			}
		return 0;
		}};

void main(){		// Основная программа
	programm P;		// Определяет объект "программа"
	new PRC1(&P);	// Создает "процесс" и привязывет его к "программе" 
	P.run();		// Вызывает метод "run" в программе
	}
