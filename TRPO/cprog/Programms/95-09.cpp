#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
//------------------------------------------------------95-09.cpp
//---- Массив указателей на строки - загрузка управляющих данных
// Для приведения двоичного файла в исходный вид выполнить 95-06.cpp
struct DMUS{
	FILE *fd;						// Файл в stdio
	int sz,ns;
	long p0, *pp;					// Образ массива файловых указателей
// Открытие файла и загрузка управляющих структур
int open(char name[]){
	if ((fd=fopen(name,"rb+"))==NULL)
		return 0;					// Режим чтения/записи/добавления
	fread(&sz,sizeof(int),1,fd);	// Считать размерность МУ
	fread(&ns,sizeof(int),1,fd);	// Считать количество указателей
	fread(&p0,sizeof(long),1,fd);	// и начальный адрес МУ в файле
	pp=new long[sz];				// Создать образ МУ
	fseek(fd,p0,SEEK_SET);			// и прочитать его содержимое из файла
	fread(pp,sizeof(long),sz,fd);
	return 1;
	}
// Обновление управляющих структур
void updateSys(){
	fseek(fd,0,SEEK_SET);			// В начале файла
	fwrite(&sz,sizeof(int),1,fd);	// Обновить заголовок
	fwrite(&ns,sizeof(int),1,fd); 
	fwrite(&p0,sizeof(long),1,fd);
	fseek(fd,p0,SEEK_SET);
	fwrite(pp,sizeof(long),sz,fd);	
	}
// Перераспределение памяти под массив файловых указателей
void extend(){
	if (ns!=sz) return;
	sz*=2;							// расширить образ МУ в памяти
	pp=(long*)realloc(pp,sizeof(long)*sz);
	fseek(fd,0,SEEK_END);			// Установиться на конец файла
	p0=ftell(fd);					// и получить новый адрес МУ в файле
	updateSys();					// Обновить заголовок и МУ на новом месте
	}
// Чтение по логическому номеру
char *get(int k){
	if (fd==NULL || k>=ns) return NULL;
	fseek(fd,pp[k],SEEK_SET);
	int ll;
	fread(&ll,sizeof(int),1,fd);	// Прочитать длину записи
	char *p=new char[ll];           // Создать динамический массив
	fread(p,ll,1,fd);				// Прочитать запись - строку
	return p;
	}
// вставка по логическому номеру
int insert(char *s, int k){
	if (fd==NULL || k>=ns) return 0;
	extend();						// Отработать переполнение
	fseek(fd,0,SEEK_END);			// Спозиционироваться в конец файла
	for(int j=ns-1;j>=k;j--)
		pp[j+1]=pp[j];				// Сдвинуть указатели в массиве
	ns++;
	pp[k]=ftell(fd);				// Записать адрес новой строки
	int ll=strlen(s)+1;
	fwrite(&ll,sizeof(int),1,fd);	// Записать строку в формате ЗПД
	fwrite(s,ll,1,fd);			
	return 1;
	}
// Закрытие файла
void close(){ updateSys(); fclose(fd); }
};

 void main(){
	DMUS FF={NULL};
	if (!FF.open("95-06.dat")) return;
	FF.insert("aaaaa\n",10);
	FF.insert("bbbbbbbb\n",5);
	for (int i=20; i>=0; i--){
	char *s=FF.get(i); if (s!=NULL) { CharToOemA(s,s); printf("[%d] %s",i,s); delete []s;}}
	FF.close();
 }
