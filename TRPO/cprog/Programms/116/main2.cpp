#include "table.h"
#include <conio.h>
void main(){
	Mtable TB;
while(1){
	printf("0-load,1-save,2-show,3-add,4-sort(0),5-sort(1),6-sort(2),7-new col\n");
	switch(getch()-'0'){
case 0: TB.load("126.dat"); break;
case 1: TB.save("126.dat"); break;
case 2: TB.show(); break;
case 3: TB.add(); break;
case 4: TB.sort(0); break;
case 5: TB.sort(1); break;
case 6: TB.sort(2); break;
case 7: TB.add_col(); break;
default: return;
		}
	}
}