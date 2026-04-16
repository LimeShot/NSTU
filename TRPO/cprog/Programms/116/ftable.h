#include "ADT_mem.h"
#include "Int.h"
#include "Float.h"
#include "String.h"
#include "record.h"
#include <iostream>
#include <fstream>
using namespace std;
class Ftable:fstream{
	int nc,nr,sz;
	long p0;				// Адрес ДМУ в ДФ
	long *pp;				// Массив указателей на записи
	record HEAD;
	DMU<String> NAMES;
	void sort(int,int,int);
	void extend();
	void add(record *);
	void sort(DMU<ADT_mem>*,int,int);
public:
	void update_sys();
static void create(char [],int=5);
	void create_head(char []);
	void compress(char nm[]);
	int load(char []);
	int save(char []);
	void add_col();
	Ftable(){ nr=0; nc=0; }
	void sort(int);
	void show();
	void add();
	void close();
	record *get(int);
	void update(record *,int);
	};