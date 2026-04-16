#include <stdio.h>
//------------------------------------------------------95-04.cpp
//---- Файл - таблица произвольной размерности
struct cDef {						// Описатель столбца
	int type;                       // тип столбца
	int size;                       // размерность столбца в байтах
	char name[30]; };				// Имя столбца 
 
struct FTABLE{
	FILE *fd;                       // Файл в stdio
	int nc;                         // Количество столбцов
	int nr;							// Количество строк
	int lr;                         // Размер строки таблицы
	long adata;                     // Начальный адрес области строк
	cDef *ST;                       // Динамический массив описателей
//------ Открыть файл и прочитать описатели столбцов 
 int open(char *name) {
	int i; 
	if ((fd=fopen(name,"rb"))==NULL) return 0;
	fread(&nc,sizeof(int),1,fd);	// Чтение nc
	fread(&nr,sizeof(int),1,fd);    // Чтение nr
	ST= new cDef[nc];               // Память под массив описателей
	fread(ST,sizeof(cDef),nc,fd);	// Чтение массива описателей
	adata=sizeof(int)*2+sizeof(cDef)*nc;        
									// Определение adata - адрес области данных 
	for (i=0,lr=0; i<nc; i++)       // Определение длины строки 
		lr += ST[i].size; 
	return 1;}
//----- Чтение элемента таблицы из столбца j строки i
void *get(int i, int j){ 
	int k,lnt;
	if (fd==NULL) return NULL;
	if (nc <=j || nr <=i) return NULL; 
	for ( k=0,lnt=0; k<j; k++)		// Смещение j-го столбца в строке
		lnt += ST[k].size;
	void *data=new char[ST[j].size];// Память под ячейку таблицы
	fseek(fd, adata+i*lr+lnt,SEEK_SET); 
									// Адрес ячейки таблицы в файле
	fread(data,ST[j].size,1,fd); 
	return data;} 
};

void main(){
	cDef TB[3]={					// Создание файла со структурой таблицы
		{0,sizeof(int),"INT"},		// Заголовок таблицы
		{0,sizeof(int),"INT2"},
		{1,20,"STRING"}};
	struct my_rec{					// Записи (строки) таблицы
		int a,b;
		char c[20];
		} DT[5]={{1,5,"aaaa"},{2,6,"bbbb"},{3,7,"cccc"},{4,8,"dddd"},{5,9,"eeeeeeeeeee"}};	
	int nc0=3,nr0=5;
	printf("%d\n",sizeof(my_rec));
	FILE *fd=fopen("95-04.dat","wb");
	fwrite(&nc0,sizeof(int),1,fd);
	fwrite(&nr0,sizeof(int),1,fd);
	fwrite(TB,sizeof(cDef),nc0,fd);
	fwrite(DT,sizeof(my_rec),nr0,fd);
	fclose(fd);
	FTABLE FF={NULL};				// Использование структурированного типа
	if (!FF.open("95-04.dat")) return;
	for (int i=4;i>=0;i--){
		int *p=(int*)FF.get(i,1);
		int *q=(int*)FF.get(i,0);
		char *s=(char*)FF.get(i,2);
		printf("[%d] %d %d %s\n",i,*q,*p,s);
		delete p;
		delete q;
		delete []s;
		}
}