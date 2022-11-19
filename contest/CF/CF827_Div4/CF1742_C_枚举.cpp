/**
 * 8*8的棋盘，可以在行刷上R，也可以在列刷上B
 * 后刷的字母会盖住前面的字母
 * 给定最后的样子，问最后刷的是什么
 * 挨个枚举检查一下即可
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = +13;
#endif

int N;
char A[SIZE][SIZE];

char checkRow(int r){
    char ch = A[r][0];
    if(ch != 'R') return 0;
    for(int i=1;i<8;++i){
        if(A[r][i] != ch) return 0;
    }
    return ch;
}

char checkCol(int c){
    char ch = A[0][c];
    if(ch != 'B') return 0;
    for(int i=1;i<8;++i){
        if(A[i][c] != ch) return 0;
    }
    return ch;
}

char proc(){
    for(int i=0;i<8;++i){
        char tmp = checkRow(i);
        if(tmp) return tmp;
        tmp = checkCol(i);
        if(tmp) return tmp;
    }
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        for(int i=0;i<8;++i)scanf("%s", A[i]);
        auto ans = proc();
        assert(ans && ans != '.');
        printf("%c\n", ans);
    }   
    return 0;
}
