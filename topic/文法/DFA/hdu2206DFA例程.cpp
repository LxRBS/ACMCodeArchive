/*
    给定字符串判断是否为IP地址格式 
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int const T[17][3] = {
//     d  .  other
/*0*/  0, 0, 0,//Error state
/*1*/  2, 0, 0,
       3, 5, 0,
       4, 5, 0,
       0, 5, 0,
/*5*/  6, 0, 0,
       7, 9, 0,
       8, 9, 0,
       0, 9, 0,
/*9*/  10,0, 0,
       11,13,0,
       12,13,0,
       0, 13,0,
/*13*/ 14,0, 0,
       15,0, 0,//final state 
       16,0, 0,//final state 
       0, 0, 0 //final state                
};

inline int tr(char ch){
	if ( '0' <= ch && ch <= '9' ) return 0;
	if ( '.' == ch ) return 1;
	return 2;
}

int run(char const word[]){
	int state = 1;
	for(char const*p=word;*p;++p){
		state = T[state][tr(*p)];
		if ( 0 == state ) return state;
	}
	return state;
}

inline bool isFinal(int state){
    return 14 == state || 15 == state || 16 == state;       
}

char S[110];
int main(){
    while ( gets(S) ){       
        if ( !isFinal(run(S)) ){
            printf("NO\n"); 
            continue;   
        }
        
        int a,b,c,d;
        sscanf(S,"%d.%d.%d.%d",&a,&b,&c,&d);
        if ( a > 255 || b > 255 || c > 255 || d > 255 )
            printf("NO\n"); 
        else
            printf("YES\n"); 
    }
    return 0;
}

