#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
//-------------------------------------------------87-01.cpp
// Дерево с распределением по разрядам ключа
struct node{
	char *data;		// Связанные данные для текущего ключа
	int cnt;		// Счетчик повторений
	node *pr[256];	// Вершины - потомки по разрядам ключа
void create(){
	for (int i=0;i<256;i++) pr[i]=NULL;
	cnt=0;
	data=NULL;
	}
void insert(unsigned char *wd, int lv){
	if (wd[lv]==0 || wd[lv]==' ' || wd[lv]=='\t'){
		cnt++;
		if (cnt==1) data=strdup((char*)wd);
		}
	else{
		unsigned k=wd[lv];
		if (pr[k]==NULL) { 
			pr[k]=new node();
			pr[k]->create(); }
		pr[k]->insert(wd,lv+1);
		}
	}
void scan(int lv){
	if (cnt!=0) {
		char c2[80];
		CharToOemA(data,c2);
		printf("n=%d:%s\n",cnt,c2);
		}
	for (int i=0;i<256;i++) 
		if (pr[i]!=NULL) pr[i]->scan(lv+1);
	}
int count(){
	int i,n=(data!=NULL);			// Есть слово в этом узле
	for (i=0; i<256;i++)
		if (pr[i]!=NULL) n+=pr[i]->count();
	return n;}
void find(char wd[], int lv){
	if (wd[lv]==0) {
		printf("[%d]\n",count());
		scan(lv);
		}
	else{
		unsigned char c1=wd[lv];
		if (pr[c1]!=NULL) pr[c1]->find(wd,lv+1);
		else puts("No words");
		}
	}
};
	

void main(){
	node H;
	H.create();
	FILE *fd=fopen("87.txt","r");
	char c[80];
	while(fscanf(fd,"%s",c)==1){
		H.insert((unsigned char*)c,0);
		}
	fclose(fd);
	printf("total=%d\n",H.count());
	H.find("кок",0);
	H.find("мур",0);
	H.find("выр",0);
	}