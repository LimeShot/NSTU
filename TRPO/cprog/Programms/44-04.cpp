//------------------------------------------------------44-04.cpp
//---- —равнение строк с заданными "весами" смиволов
 int Carry(char c){
 static char ORD[] = "Рј†ЅХ¬р√щƒа≈1234567890"; 
 if (c=='\0') return 0;
 int n;
 for ( n=0; ORD[n]!='\0'; n++)
	  if (ORD[n]==c) return n;
 return n+1; }
 int my_strcmp(char s1[],char s2[]){
 int n; char c1,c2;
 for (n=0; (c1=Carry(s1[n]))!='\0' &&(c2=Carry(s2[n]))!='\0'; n++)
	  if (c1 != c2) break;
 if (c1 == c2) return 0;
 if (c1 < c2) return -1;
 return 1; }

 #include <stdio.h>
 void main(){
 printf("v=%d\n",my_strcmp("ЅаЅа ј","бјб ј"));
 printf("v=%d\n",my_strcmp("бјб ј","12345"));
 printf("v=%d\n",my_strcmp("бјЅ ј","ЅјЅ ј"));
 }
