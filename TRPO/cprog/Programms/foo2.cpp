#include <stdio.h>
//-------------------------------------------------foo2.cpp
// Относительная адресация в ДФ
void main(){
	FILE *fd=fopen("foo2.dat","wb");
	long i,k=0,p=80,t=10;
	for (i=0; i<100;i++) fwrite(&k,1,1,fd);
	long v=p-t-sizeof(long);
	fseek(fd,t,SEEK_SET);
	fwrite(&v,sizeof(long),1,fd);
	fclose(fd);
	fd=fopen("foo2.dat","rb");
	fseek(fd,t,SEEK_SET);
	fread(&i,sizeof(long),1,fd);
	printf("%ld\n",i);
	fseek(fd,i,SEEK_CUR);
	printf("%ld\n",ftell(fd));
	}