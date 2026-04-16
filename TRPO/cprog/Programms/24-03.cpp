//------------------------------------------------------24-03.cpp
//--- Поиск подстроки в строке
int search(char c1[],char c2[]){
	int i,j;
for ( i=0; c1[i]!='\0'; i++){
	for ( j=0; c2[j] !='\0'; j++)
		if (c1[i+j] != c2[j]) break;
	if (c2[j] =='\0') return i;
	} 
return -1;}

int search2(char c1[],char c2[]){
	int i,j;
for (i=0,j=0; c1[i]!='\0'; i++,j++){
	if (c2[j]==0) return i-j;
	if (c1[i]!=c2[j]) { i=i-j; j=-1; }
	} 
return -1;}

#include <stdio.h>
void main(){ 
char cc[]="abcdefg  12345";
puts(cc+search(cc,"123"));
puts(cc+search2(cc,"123")); }
