#include <stdio.h>
#include <conio.h>
#include <string.h>
//------------------------------------------------------54-01.cpp
// Иерархия типов данных и функций
// Уровень 1. Представление даты
struct date{
	int dd,mm,yy;
	void setDate(int dd0, int mm0, int yy0){
		dd=dd0; mm=mm0; yy=yy0; }
	void getDate(){
		printf("\nday:"); scanf("%d",&dd);
		printf("month:"); scanf("%d",&mm);
		printf("year:"); scanf("%d",&yy);
		}
	int cmpDate(date &T){
		if (yy!=T.yy) return yy-T.yy;
		if (mm!=T.mm) return mm-T.mm;
		return dd-T.dd;
		}
	void loadDate(FILE *fd){ fscanf(fd,"%d%d%d",&dd,&mm,&yy); }
	void saveDate(FILE *fd){ fprintf(fd,"%d %d %d ",dd,mm,yy); }
	void showDate(){ printf("%02d.%02d.%04d ",dd,mm,yy); }
	int testDate(){
		if (dd<1 || dd>31 || mm<1 || mm>12) return 0;
		if (dd==30 && (mm==2 || mm==4 || mm==6 || mm==9 || mm==11)) return 0;
		if (dd==29 && mm==2 && yy%4==0) return 1;
		return 1;
		}
	};
// Уровень 1. Представление строки таблицы (записи)
const int N=100;
const int NP=100;
struct user{
	char name[20],pass[10];
	date birth;
	int np;
	date SS[NP];
	double credit;
	void setUser(char nm[], char ps[], date b0){
		strcpy(name,nm);
		strcpy(pass,ps);
		birth=b0;
		np=0;
		}
	void addDate(date d0){
		if (np!=NP) SS[np++]=d0; }
	void showUser(){ 
		printf("%20s  %10s   ",name,pass);
		birth.showDate();
		printf("%2d\n",np);
		}
	void showDate(){
		for (int i=0;i<np;i++) { 
			SS[i].showDate(); printf("\n"); }
		}
	void loadUser(FILE *fd){
		fscanf(fd,"%s%s",name,pass);
		birth.loadDate(fd);
		fscanf(fd,"%d",&np);
		for (int i=0;i<np;i++) SS[i].loadDate(fd);
		}
	void saveUser(FILE *fd){
		fprintf(fd,"%s\n%s\n",name,pass);
		birth.saveDate(fd);
		fprintf(fd,"\n%d\n",np);
		for (int i=0;i<np;i++) SS[i].saveDate(fd);
		fprintf(fd,"\n");
		}
	int cmpUser(user &T,int mode){
		switch (mode){
case 0:	return strcmp(name,T.name);
case 1:	return birth.cmpDate(T.birth);
case 2:	return np-T.np;
		}}
	};
// Уровень 3 - представление таблицы
struct table{
	user TBL[N];
	int  nn;
	void addUser(char nm[], char ps[], date b0){
		if (nn!=NP) { TBL[nn].setUser(nm,ps,b0); nn++; }
		}
	void loadTable(char nm[]){
		FILE *fd=fopen(nm,"r");
		if (fd==NULL) return;
		fscanf(fd,"%d\n",&nn);
		if (nn>=N) return;
		for (int i=0;i<nn;i++) TBL[i].loadUser(fd);
		fclose(fd);
		}
	void saveTable(char nm[]){
		FILE *fd=fopen(nm,"w");
		if (fd==NULL) return;
		fprintf(fd,"%d\n",nn);
		for (int i=0;i<nn;i++) TBL[i].saveUser(fd);
		fclose(fd);
		}
	void sortTable(int mode){
		int i,j,k;
		for (i=0;i<nn;i++){
			for(j=k=i; j<nn;j++)
				if (TBL[j].cmpUser(TBL[k],mode)<0)
					k=j;
			user cc=TBL[i]; TBL[i]=TBL[k]; TBL[k]=cc;
			}
	}};

// Уровень 4 - основная программа
table TT;
void main(){
	int i;
	TT.nn=0;
	char c1[80],c2[80];
	date d0={1,1,2001};
	TT.addUser("admin","12345",d0);
	while(1){
		printf("\na(dd),v(iew),l(oad),s(ave),o(rd by),d(ate)\nwhat to do:");
		switch(getch()){
case 27:	return;				// escape - выход
case 'a':	printf("\nname:"); scanf("%s",c1);
			printf("password:"); scanf("%s",c2);
			d0.getDate();
			TT.addUser(c1,c2,d0);
			break;
case 'v':	printf("\nnn                name     password  birth       np\n");
			for (i=0;i<TT.nn;i++) {
			printf("%-2d",i);
			TT.TBL[i].showUser();}
			break;
case 's':	TT.saveTable("54-01.txt");
			break;
case 'l':	TT.loadTable("54-01.txt");
			break;
case 'o':	printf("\nsort mode (0-by name, 1-by date, 2-by count(np)):");
			TT.sortTable(getch()-'0');
			break;
case 'd':	printf("\nuser number:"); scanf("%d",&i);
			printf("\na(dd), v(iew):");
			char cc=getch();
			if (cc=='a'){ d0.getDate(); TT.TBL[i].addDate(d0);}
			if (cc=='v'){
				for (int j=0;j<TT.TBL[i].np;j++){
					printf("\n%d ",j);
					TT.TBL[i].SS[j].showDate();}
				}
			break;
		}}
	}