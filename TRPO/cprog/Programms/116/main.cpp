#include "table.h"
#include "ftable.h"
#include <conio.h>
void main(){
	int k;
	record *q;
	Mtable TB;
	Ftable TBF;
	printf("0-mem_table, 1-file_table\n");
	switch(getch()-'0'){
case 0:
	while(1){
	printf("0-load,1-save,2-show,3-add,4-sort,5-edit,7-new col\n");
	switch(getch()-'0'){
case 0: TB.load("126.dat"); break;
case 1: TB.save("126.dat"); break;
case 2: TB.show(); break;
case 3: TB.add(); break;
case 4: printf("col="); scanf("%d",&k); getchar();
		TB.sort(k); break;
case 7: TB.add_col(); break;
default: return;
		}
	}
case 1:
	while(1){
	printf("0-load,1-save,2-show,3-add,4-sort,5-edit,7-create,8-compress\n");
	switch(getch()-'0'){
case 0: TBF.load("126_F.dat"); break;
case 1: TBF.update_sys(); break;
case 2: TBF.show(); break;
case 3: TBF.add(); break;
case 4: printf("col="); scanf("%d",&k); getchar();
		TBF.sort(k); break;
case 5: printf("rec="); scanf("%d",&k); getchar();
		q=TBF.get(k);
		q->edit();
		TBF.update(q,k);
		delete q; 
		break;
case 7: Ftable::create("126_F.dat"); TBF.close(); return;
case 8: TBF.compress("126_FF.dat"); break;
default: TBF.close(); return;
		}
	}
}}