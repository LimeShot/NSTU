#include <stdio.h>
//------------------------------------------------------92-05.cpp
//--- Функция с параметром форматной строкой ( printf)
 void my_printf(char *s,...)
 { char *p = (char*)(&s+1);			// Указатель на начало списка параметров
	  while (*s != '\0') {          // Просмотр форматной строки
	  if (*s != '%') putchar(*s++); // Копирование форматной строки
	  else
		   { s++;					// Спецификация параметра вида "%d"
				switch(*s++){		// Извлечение параметра и переход к следующему
		   case 'c': putchar(*p++); break;								// Извлечение символа
		   case 'd': printf( "%d", *((int*)p)); p+=sizeof(int); break;	// Извлечение целого
		   case 'f': printf( "%lf", *((double*)p)); p+=sizeof(double); break; // Извлечение вещественного
		   case 's': puts( *((char**)p)); p+=sizeof(char*);				// Извлечение указателя
				break;													// на строку
				}}}}
void main(){
my_printf("int=%d double=%f char[]=%s char=%c ",44,5.5,"qwerty",'f'); }
