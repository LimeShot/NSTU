#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <windows.h>

//--------------------------------------------------------------------------
// Класс СОБЫТИЯ и интерфейс СЛУШАТЕЛЯ для "мыши"
class MouseEvent{
public:	int x,y;
		MouseEvent(int x0,int y0){ x=x0; y=y0; }
	};
class MouseListener {		// КЛАСС (ИНТЕРФЕЙС) CЛУШАТЕЛЯ (Базовый и абстрактный)
public:
	virtual void mouseClicked(MouseEvent ee)=0;
	};
//--------------------------------------------------------------------------
// Класс СОБЫТИЯ и интерфейс СЛУШАТЕЛЯ для "действия"
class ActionEvent{			// МЕНЮ и КНОПКИ - Action
public:	
	char *name;
	ActionEvent(char *ss){ name=ss; }
	};
class ActionListener {		// КЛАСС (ИНТЕРФЕЙС) CЛУШАТЕЛЯ (Базовый и абстрактный)
public:
	virtual void actionPerformed(ActionEvent ee)=0;
	};
//---------------- НАПИСАН РАНЬШЕ и НЕ USER'ом------------------------------
class Component{
public:
	int x,y,w,h;
	Component(){ 
		x=y=h=w=0; 
		ml=NULL; 
		al=NULL;				// Обработчиков нет
		}
	void setSize(int x0,int y0,int w0,int h0){
		x=x0; y=y0; h=h0; w=w0;
		}
	virtual int inside(int xx,int yy){
		return xx>=x && xx<=x+w && yy>=y && yy<=y+h;
		}
	virtual void paint()=0;
	MouseListener *ml;			// Объект-обработчик события типа "мышь"(в нем метод)
	ActionListener *al;			// Объект-обработчик события типа "действие"(в нем метод)
	virtual void MouseClick(int xx,int yy)=0;
	};
//===========================================================================
class Button : public Component{
	char *label;
public:
	Button(char *s){ label=s; }
	void paint(){
		printf("Рисуем кнопку [%s] %d %d (%d,%d)\n",label,x,y,w,h);
		}
	void addActionListener(ActionListener *ff){ al=ff; }
	void addMouseListener(MouseListener *ff){ ml=ff; }
	void MouseClick(int xx,int yy){
		if (al!=NULL) al->actionPerformed(ActionEvent(label));
		else if (ml!=NULL) ml->mouseClicked(MouseEvent(xx,yy));
		}
	};
class TextField : public Component{
	int sym;
public:
	TextField(int ns){ sym=ns; }
	void paint(){
		printf("Рисуем текстовое поле [%d] %d %d (%d,%d)\n",sym,x,y,w,h);
		}
	void addMouseListener(MouseListener *ff){ ml=ff; }
	void MouseClick(int xx,int yy){
		if (ml!=NULL) ml->mouseClicked(MouseEvent(xx,yy));
		}
	};
//=========================================================================
class Frame{
	Component **ctrl;		// Объекты управления в окне - ДМУ
	int nc,sz;
public:
	Frame(){
		setlocale(LC_ALL,"Russian");
		ctrl=new Component*[20];
		nc=0;
		sz=20;
	}
	void add(Component *p){
		if (nc==sz){ sz*=2; ctrl=(Component**)realloc(ctrl,sz*sizeof(Component*)); }
		ctrl[nc++]=p;
	}
	virtual void paint(){
	// Заливка экрана + прорисовка элементов управления
	// ГРАФИКА - отвечает USER
		puts("Перерисовка окна");
		for (int i=0;i<nc;i++) ctrl[i]->paint();
	}
	// СОБЫТИЯ от ядра ОС - получение событий от ядра
	void loop(){
		while(1){
		char c=getch();
		if (c==' ') return;
		if (c=='c') paint();	// Перерисовка экрана == ВЫЗОВ в ПК
		if (c=='m') {			// МЫШЬ
			printf("Координаты мыши:");
			int xx,yy;
			scanf("%d%d",&xx,&yy);	// Передать объектам !!!!!!!!!!!!
			for (int i=0;i<nc;i++){
				if (ctrl[i]->inside(xx,yy)) {
					ctrl[i]->MouseClick(xx,yy);
					}
				}
			//---------------------
			}
		}}};
//========================================================================
// Обработка событий - ВНЕШНИЙ ПОЛИМОРФИЗМ с использованием ИНТЕРФЕЙСОВ
// (класс без данных + пустые методы)
//=========================================================================
class MyFrame : public Frame,public ActionListener{
public:
	//--------------------------------------------- Вложенный класс-адаптер
	class adapter_F1 : public ActionListener{
	MyFrame *pp;							// Указатель на ОКНО, в котором работает
public:
	adapter_F1(MyFrame *p0){ pp=p0; }			// При создании - запоминает указатель на окно
	void actionPerformed(ActionEvent ee){ pp->F1(ee); }
											// При вызове в качестве обработчика событий
	};
	class adapter_F2 : public ActionListener{
	MyFrame *pp;							// Указатель на ОКНО, в котором работает
public:
	adapter_F2(MyFrame *p0){ pp=p0; }			// При создании - запоминает указатель на окно
	void actionPerformed(ActionEvent ee){ pp->F2(ee); }
											// При вызове в качестве обработчика событий
	};
	//---------------------------------------------------------------------------------
	// Отложенное программирование - перерисовка графики
	void paint(){
		Frame::paint();			// Явно вызвать старый код
		puts("Перерисовка графики");
	}
	MyFrame(){
		Button *b1=new Button("Дави");		// Создать КНОПКУ
		b1->setSize(100,200,50,20);
		add(b1);							// ПЕРЕДАТЬ ОКНУ
		b1->addActionListener(this);		// Обработчик - само окно
		b1->addActionListener(new adapter_F1(this));
		b1=new Button("Стоп");				// Создать КНОПКУ
		b1->setSize(100,230,50,20);
		add(b1);							// ПЕРЕДАТЬ ОКНУ
		b1->addActionListener(this);
		b1->addActionListener(new adapter_F2(this));
		TextField *t1=new TextField(10);	// Создать ТЕКСТ
		t1->setSize(100,250,100,20);
		add(t1);							// ПЕРЕДАТЬ ОКНУ
		}
	//================================================================
	//  Объект-обработчик = само окно - ОБРАТЫВАЕТ СОБЫТИЯ ОТ ВСЕХ ИСТОЧНИКОВ
	void actionPerformed(ActionEvent ee){
		printf("Обработка в окне нажатия %s\n",ee.name);
	}
	// Должны быть 2 класса-адаптера
	void F1(ActionEvent ee){
		printf("Обработка в F1 нажатия %s\n",ee.name);
	}
	void F2(ActionEvent ee){
		printf("Обработка в F2 нажатия %s\n",ee.name);
	}
};

//===================================================================

void main(){
	MyFrame  X;	
	X.loop();			// Обработчик событий
}