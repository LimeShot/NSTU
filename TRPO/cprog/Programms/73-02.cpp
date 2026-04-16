//------------------------------------------------------73-02.cpp
#include <stdlib.h>
//------- Задача о восьми ферзях
 int R[8];
 int TEST(int i){
	  for (int j=i-1; j>=0; j--){
	  if(R[i]==R[j]) return 0;				// По горизонтали
      if(abs(R[i]-R[j])==i-j) return 0;     // По диагонали
      }
 return 1; }
 int step(int i){
 if (i==8) return 1;
 for (int j=0; j<8; j++){					// Перебор по вертикали
      R[i]=j;
      if (!TEST(i)) continue;               // Под боем - пропустить
      if (step(i+1)) return 1;				// Цепочка достроена - выйти
      }
 return 0;}                                 // Цикл завершен неудача 
 #include <stdio.h>
 void main(){ step(0);
 for (int i=0; i<8; i++) printf("%d  ",R[i]);
 printf("\n");
 }
