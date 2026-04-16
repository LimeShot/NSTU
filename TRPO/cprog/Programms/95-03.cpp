#include <stdio.h>
//------------------------------------------------------95-03.cpp
//  Файл записей фиксированной длины
//  Структурированный тип со встроенными функциями
struct BFILE{
	FILE *fd;					// Файл в stdio
	int nr,sz;					// Образ структур данных файла 
int create(char *name,int sz0){	// Создать пустой файл
	if ((fd=fopen(name,"wb"))==NULL)         
		return 0;				// Создать новый для записи
	int nr0=0;					// Записать счетчик и размерность
	fwrite((void*)&sz0,sizeof(int),1,fd);   
	fwrite((void*)&nr0,sizeof(int),1,fd);
	fclose(fd); fd=NULL; return 1; }
// Открыть существующий файл с проверкой
int open(char *name,int sz0){
	if (fd!=NULL) return 0;				// Файл уже открыт
	if ((fd=fopen(name,"rb+"))==NULL)         
		return 0;						// Открыть для чтения и записи
	fread((void*)&sz,sizeof(int),1,fd);	// Читать из файла nr и sz
	fread((void*)&nr,sizeof(int),1,fd);
	fseek(fd,0L,SEEK_END);				// Соответствует ли длина файла
	if (ftell(fd)!=
		2*sizeof(int)+(long)nr*sz)		// значениям nr и sz?
		{ fclose(fd); fd=NULL; return 0;}
	return 1;}
// Читать запись с заданным номером из открытого файла
void *get(int i){
	if (fd==NULL) return NULL;		// Файл не открыт
	if (i<0 || i>=nr) return NULL;  // Номер записи некорректен
	void *q=new char[sz];           // Выделить память (в байтах)
	if (fseek(fd,2*sizeof(int)+i*sz,SEEK_SET)==EOF)
	  { delete []q; return NULL; }  // Ошибка позиционирования
	if (fread(q,sz,1,fd)!=1)
	  { delete []q; return NULL; }	// Ошибка чтения
	return q; }
// Добавить запись
int append(void *pp){
	if (fd==NULL) return NULL;		// Файл не открыт
	fseek(fd,0L,SEEK_END);          // Установиться на конец файла
	if (fwrite(pp,sz,1,fd)!=1) 
		return 0;					// Добавить запись
	nr++;							// Обновить переменную nr в файле
	fseek(fd,sizeof( int),SEEK_SET);  
	if (fwrite((void*)&nr,sizeof(int),1,fd)!=1)
		return 0;                                            
	return 1; }
};

void main(){
	BFILE FF={NULL,0,0};
	double A[]={4,6,2,8,3,4,1,5,6};
	int n=sizeof(A)/sizeof(double);
	FF.create("95-03.dat",sizeof(double));
	if (!FF.open("95-03.dat",sizeof(double)))
		return;
	int i;
	for (i=0;i<n;i++) FF.append(&A[i]);
	for (i=n-1; i>=0; i--){
		double *pd=(double*)FF.get(i);
		printf("%lf\n",*pd); delete pd;
		}
	}
