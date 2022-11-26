/**
 * 给定一个数组，问有多少对i、j满足Ai<i<Aj<j
 * 使用树状数组
 * 对每一个满足条件的Ai<i
 * 查询之前出现的小于Ai的一共多少个，累加
 * 然后在Ai位置加1即可
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
    while(!isalpha(ch)) ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;

int N;
int A[SIZE];
int W[SIZE];

struct bit_t{

int n;
llt c[SIZE];

static int lowbit(int x){return x & -x;}

void init(int total){
    fill(this->c, this->c+(this->n=total)+1, 0LL);
}

llt query(int pos){
    llt ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += c[i];
    return ans;
}

llt query(int s, int e){return query(e) - query(s-1);}

void modify(int pos){
    for(int i=pos;i<=n;i+=lowbit(i)) c[i] += 1;
}

}Bit;

llt proc(){
    Bit.init(N);
    llt ans = 0;
    for(int i=1;i<=N;++i){
        if(A[i] >= i) continue;

        int key = A[i] > N ? N : A[i];
        ans += (key > 0 ? Bit.query(key-1) : 0);
        Bit.modify(i);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        N = getInt();
        for(int i=1;i<=N;++i) W[i] = A[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}

