/**
 * 简单模拟
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

char getChar(){
    while(1){
        char ch = __hv007();
        if(('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) return ch;        
    }
}

int Score[6];
int Jing[6];
int Total[6];

void record(int a, int b, int af, int bf){
    if(af > bf){
        Score[a] += 3;
    }else if(af < bf){
        Score[b] += 3;
    }else{
        ++Score[a];
        ++Score[b];
    }
    Jing[a] += af - bf;
    Jing[b] += bf - af;
    Total[a] += af;
    Total[b] += bf;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        for(int i=0;i<6;++i) Score[i] = Jing[i] = Total[i] = 0;

        for(int a,b,x,y,i=0;i<15;++i){
            a = getChar() - 'A';
            b = getChar() - 'A';
            x = getUnsigned();
            y = getUnsigned();
            record(a, b, x, y);

            x = getUnsigned();
            y = getUnsigned();
            record(a, b, x, y);
        }
        for(int i=0;i<6;++i){
            printf("%d %d %d\n", Score[i], Jing[i], Total[i]);
        }
        assert(0 == accumulate(Jing, Jing+6, 0));
    }
    return 0;
}