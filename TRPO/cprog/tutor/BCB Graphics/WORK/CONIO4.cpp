#include <stdio.h>
#include <conio.h>
#include <string.h>

#define DELAY
#ifdef DELAY
#include <time.h>
// Функция задержки, параметр - время задержки в миллисекундах
void delay(int ms){
  unsigned long t1 = clock()/CLK_TCK*1000+ms, t2 = 0;
  while((t2 = clock()/CLK_TCK*1000) < t1);
}
#endif

// Предлагаемая к сортировке строка
unsigned char C[] = "lpokmnjiuhbvgytfcxdreszawq";

int y=8;	// номер строки на экране, где будет сортировка

// Опустить букву вниз на знакоместо экрана
// Параметры - координаты буквы, буква, задержка
void down(int i, int j, char c, int ms=0){
  gotoxy(i+1, y+j);
  putch(' ');
  gotoxy(i+1, y+j+1);
  putch(c);
#ifdef DELAY
  delay(ms);
#endif
}

// Поднять букву
void up(int i, int j, char c, int ms=0){
  gotoxy(i+1, y+j);
  putch(' ');
  gotoxy(i+1, y+j-1);
  putch(c);
  textcolor(WHITE);
#ifdef DELAY
  delay(ms);
#endif
}

// Сместить букву влево
void left(int i, int j, char c, int ms=0){
  gotoxy(i+1, y+j);
  putch(' ');
  gotoxy(i, y+j);
  putch(c);
  textcolor(14);
#ifdef DELAY
  delay(ms);
#endif
}

// Сместить букву вправо
void right(int i, int j, char c, int ms=0){
  textcolor(12);
  gotoxy(i+1, y+j);
  putch(' ');
  gotoxy(i+2, y+j);
  putch(c);

#ifdef DELAY
  delay(ms);
#endif
}
// Сортировка выбором
void Sort(unsigned char *c, int ms=0){
  int sz = strlen(c), min_i;
  int i, j;
  unsigned char min_el, temp;
  gotoxy(1, y);
  puts(c);
  for(i=0; i<sz-1; i++){			// Берем i-тый элемент
	down(i, 0, c[i], ms);			// (он падает вниз)
	min_el = c[i];
	min_i = i;
	for(j=i +1; j<sz; j++){			// Ищем минимальный элемент
	  right(j-1, 1, c[i], ms);			// от i-того (ползет вправо
						   //	 под строкой)
	  up(j, 0, c[j], ms);			// до последнего
	  up(j, -1, c[j], ms);			// (они тут прыгают)
	  up(j, -2, c[j], ms);
	  if(c[j]<min_el){
	  if (kbhit()) return;
	if(i-min_i)
	  down(min_i, -1, c[min_i], ms);	// падает на место ранее
						//найденый минимальный элемент
	min_el = c[j];
	min_i = j;
	down(j, -3, c[j], ms);			// минимальный не падает
						//до конца
	down(j, -2, c[j], ms);
	  }
	  else{
	down(j, -3, c[j], ms);			// не минимальный -
	down(j, -2, c[j], ms);			// падает!
	down(j, -1, c[j], ms);
	  }
	}
	right(sz-1, 1, c[i], 4*ms);			// i-тый элемент обходит
	right(sz, 1, c[i], 4*ms);			// цепочку
	up(sz+1, 1, c[i], 4*ms);			// справа
	up(sz+1, 0, c[i], 4*ms);
	for(j=sz+1; j>min_i+1; j--)			// идет влево до минимального
	  left(j, -1, c[i], 4*ms);
	if(i-min_i)
	  left(min_i, -1, c[min_i], ms);		// толкает его
	left(min_i+1, -1, c[i], ms);
	 textcolor(WHITE);
	down(min_i, -1, c[i], ms);			// ложится на его место
	if(i-min_i){
	  for(j=min_i-1; j>i; j--)			// минимальный катится на место
	left(j, -1, c[min_i], ms);		// i-того
	  down(i, -1, c[min_i], ms);
	}
	temp = c[i];				// настоящий обмен элементов
	c[i] = c[min_i];				// (в строке, а не
	c[min_i] = temp;				// на экране)
  }
}

// Главная функция
void main(void){
  int ms=0;
#ifdef DELAY
  ms = 100;				// Если есть задержка -
					//то вот ее время
#endif
  clrscr();
  _setcursortype(0);
  Sort(C, ms);				// Сортируем
   gotoxy(1,13);
 /* puts("Введите другую строку.");	// Предлагаем ввести свою строку
  gotoxy(1,15);
  char newC[81];
  _setcursortype(2);
  gets(newC);				// Вводим
  _setcursortype(0);
  y=20;
  Sort(newC, ms);			// Сортируем
  gotoxy(1, 24);
  puts("Нажмите какую-нибудь кнопку...");
  getch();
  _setcursortype(2);*/
}












