/*
    给定字符串，判断是否符合数字格式 
*/
#include <cctype>
#include <cstdio>

inline int tr(char ch){
    if ( isdigit(ch) ) return 0;
	if ( '.' == ch ) return 1;
	if ( 'E' == ch || 'e' == ch ) return 2;
	if ( '+' == ch || '-' == ch ) return 3;
	if ( ' ' == ch ) return 4;
	return 5;	
}

int DFA[10][6] = {
    {0},
    3,0,0,2,0,0,
    3,0,0,0,0,0,
    3,4,6,0,9,0,//final
    5,0,0,0,0,0,
    5,0,6,0,9,0,//final
    8,0,0,7,0,0,
    8,0,0,0,0,0,
    8,0,0,0,9,0,//final
    0,0,0,0,9,0 //final
};

int run(char const word[]){
	int state = 1;
	for(char const*p=word;*p;++p){
		state = DFA[state][tr(*p)];
		if ( 0 == state ) return state;
	}
	return state;
}

inline bool isFinal(int state){
	return 3 == state || 5 == state || 8 == state || 9 == state;
}

char S[1005];
int main(){
	int kase;
	scanf("%d",&kase);
	gets(S);
	while(kase--){
		gets(S);
		char *p = S;
		while( ' ' == *p ) ++p;
		
		printf(isFinal(run(p))?"LEGAL\n":"ILLEGAL\n");
	}
	return 0;
}

