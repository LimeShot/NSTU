#include <stdio.h>
#include <string.h>
//------------------------------------------------------102-02.cpp
//----- Класс " разделяемых" строк
 class cstring{
	char *str;					// Указатель на строку
	int *pcnt;                  // Указатель на счетчик ссылок
    void beforChange(){
        if (*pcnt==1)
            return;
        str=strdup(str);		// Экземпляр разделяемых данных
        int *q=new int;         // Динамическая переменная - счетчик ссылок
        *q=1;   				// Новое количество ссылок +1
        *pcnt--;                // Старое -1
        pcnt=q;                 // Взять себе новое
        }
    void release(){
        if (--(*pcnt)==0 ){		// если последний уничтожает
			delete []str;       // экземпляр данных и счетчик
			delete pcnt;
            }
        }
 public:
	cstring(char *s){			// Конструктор
		str=strdup(s);			// Экземпляр разделяемых данных
		pcnt=new int;           // Динамическая переменная - счетчик ссылок
		*pcnt=1; }				// Количество ссылок 1
	cstring(cstring &R){		// Конструктор копирования
		str=R.str;              // копирует указатели и увеличивает счетчик
		pcnt=R.pcnt;
		(*pcnt)++;
		printf("+copies=%d %s %lx\n",*pcnt,str,this);
		}
	~cstring(){					// Деструктор
		printf("-copies=%d %s %lx\n",*pcnt,str,this);
		release();
        }
	cstring &operator=(cstring &R){ // переопреление присваивания
								//  уменьшение для левой части
		printf("-copies=%d %s %lx\n",*pcnt,str,this);
		release();
		str=R.str;              // копирует указатели и увеличивает счетчик
		pcnt=R.pcnt;            // правой части
		(*pcnt)++;
		printf("+copies=%d %s %lx\n",*pcnt,str,this);
		return *this;
		}
    cstring &changeChar(char c, int n){
        if (n<0 || n>=strlen(str))
            return *this;
        beforChange();
        str[n]=c;
        return *this;
        }
    void show(){ printf("cnt=%d %s\n",*pcnt,str); }
 };

 cstring copy(cstring S){ return S; }

int main(){
 cstring a("aaaaa"),b("33333"),c=a,*p;	// явный КК
 a.show();
 b.show();
 c.show();
 b = a;                             // Переопределенная операция =
 copy(a).changeChar('z',3).show();	// Два КК в функции
 b.changeChar('x',1);
 c.changeChar('y',1);
 b.changeChar('x',2);
 a.show();
 b.show();
 c.show();
 return 0;
 }

