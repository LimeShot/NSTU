#include "ADT_mem.h"
#include "Int.h"
#include "Float.h"
#include "String.h"
#include "lmatrix.h"
#include "record.h"

class Mtable{
public:
	int nc,nr;
	DMU<record> TBL;
	void sort(int,int,int);
	record HEAD;
	DMU<String> NAMES;
	int load(char []);
	int save(char []);
	void add_col();
	Mtable(){ nr=0; nc=0; }
	void sort(int);
	void show();
	void add();
	static ADT_mem *create_ADT(int);
	};