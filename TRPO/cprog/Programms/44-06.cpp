//------------------------------------------------------44-06.cpp
//---- возвращается индекс скобки " {" для первой самой внутренней пары
      int find(char c[]){
      int i;                              // Индекс в строке
      int b;                              // Индекс максимальной " {" 
           for (i=0, b=-1; c[i]!=0; i++){
           if (c[i]== '}' ) return b;
           if (c[i]== '{' ) b=i;
           }
      return b;}

 #include <stdio.h>
 void main(){
 char cc[80]="gggg{dd{ggg}dd{ff{y{*}y}ff}d}";
 puts(&cc[find(cc)]);
 while(1);
 }
