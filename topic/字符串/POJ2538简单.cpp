//简单，不用解题报告
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

char Table[128] = {0};

void init(){
	Table['Q'] = '\t';
	Table['W'] = 'Q';
	Table['E'] = 'W';
	Table['R'] = 'E';
	Table['T'] = 'R';
	Table['Y'] = 'T';
	Table['U'] = 'Y';
	Table['I'] = 'U';
	Table['O'] = 'I';
	Table['P'] = 'O';
	Table['['] = 'P';
	Table[']'] = '[';
	Table['\\'] = ']';
	Table['1'] = '`';
	for(char c='2';c<='9';++c) Table[c] = c - 1;
	Table['0'] = '9';
	Table['-'] = '0';
	Table['='] = '-';
	Table['S'] = 'A';Table['D'] = 'S';Table['F'] = 'D';Table['G'] = 'F';Table['H'] = 'G';Table['J'] = 'H';Table['K'] = 'J';Table['L'] = 'K';Table[';'] = 'L';Table['\''] = ';';
	Table['X'] = 'Z';Table['C'] = 'X';Table['V'] = 'C';Table['B'] = 'V';Table['N'] = 'B';Table['M'] = 'N';Table[','] = 'M';Table['.'] = ',';Table['/'] = '.';
	Table[' '] = ' ';
}
string Str;

void f(char& ch){
	ch = Table[ch];
}

int main(){
	init();
   
	while(getline(cin,Str)){
        for_each(Str.begin(),Str.end(),f);
		cout<<Str<<endl;
	}

	return 0;
}