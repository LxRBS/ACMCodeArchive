/**
 * 初始给定字符串s="a"和t="a"
 * 有Q个操作，每次操作要么选择s，要么选择t，再其后添加k个x，其中x代表小写字母
 * 对每次操作问：该操作之后，如果可以各自自由调整S和T中的字母的次序，是否可以令S小于T
 * 只需记住每个字符串中字母的数量即可
 * 如果t中有‘b‘以上的字母，肯定可以。
 * 如果t中只有'a'，则s中必须也只有'a'且数量少于t的，才行。
 * 除此之外，无法满足
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

char getChar(){
    char ch = __hv007();
    while(!islower(ch) && ch != '\n') ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 14;
#else
int const SIZE = 2E5+12;
#endif

using llt = long long;
using vi = vector<llt>;

vi A, B;
int Q;

void proc(vi & dst, const vi & src, llt k){
    for(int i=0;i<26;++i) dst[i] += k * src[i];
}
bool judge(const vi & a, const vi & b){
    int lastb = 25;
    while(1){
        if(b[lastb]) break; 
        --lastb;        
    }
    if(lastb > 0) return true;
    int lasta = 25;
    while(1){
        if(a[lasta]) break;
        --lasta;
    }
    return 0 == lasta && a[0] < b[0];
}
void proc(){
    int d = getInt();
    int k = getInt();
    vi tmp(26, 0LL);
    while(1){
        char ch = getChar();
        if(ch == '\n') break;
        ++tmp[ch-'a'];
    }
    if(1 == d){
        proc(A, tmp, k);
    }else{
        proc(B, tmp, k);
    }
    puts(judge(A, B)?"YES":"NO");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        Q = getInt();
        A.assign(26, 0LL);
        B.assign(26, 0LL);
        A[0] = B[0] = 1;
        for(int q=1;q<=Q;++q){
            proc();
        }
    }
    return 0;
}

