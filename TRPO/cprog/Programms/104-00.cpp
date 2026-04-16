#include <iostream>
#include <strstream>
#include <fstream>
using namespace std;

void main(){
istrstream I("2 3.4 abcd");
int a; 
double b; 
char c,s[10],out[80];
I >> a >> b >> c >> s;
cout << a << " " << b << " " << c << " " << s << endl;
ostrstream O(out,80);
O << b << " " << c << "\n" << a << " " << s << '\0';
cout << out << endl;
ifstream F1("104-00.cpp");
ofstream F2;
F2.open("104-00.txt");
if (!F1.good() || !F2.good()) return;
while (!F1.eof()) { 
	F1.getline(out,80); 
	F2 << out << endl; }
F1.close(); F2.close();
}