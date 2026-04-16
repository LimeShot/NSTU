//------------------------------------------------------44-03.cpp
//---- Сравнение строк по значениям кодов
 int my_strcmp(unsigned char s1[],unsigned char s2[]) { 
 int n;
 for ( n=0; s1[n]!='\0' && s2[n]!='\0'; n++)
      if (s1[n] != s2[n]) break;
 if (s1[n] == s2[n]) return 0;
 if (s1[n] < s2[n]) return -1; 
 return 1; }
