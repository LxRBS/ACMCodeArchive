/**
 * 两排节点，给定一个数组，Ai表示上一行第i个节点连一条直线到下一行第Ai个节点
 * 问给定的连接线，一共有多少个交点
 * 对于某个Ai而言，如果前面存在比他大的连接点，则就两线就会相交
 * 因此实际上就是问比Ai大的数的数量，树状数组。
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
int const SIZE = 14;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;

struct bit_t{

int n;
int c[SIZE];

static int lowbit(int x){return x & -x;}

void modify(int pos){
    for(int i=pos;i<=n;i+=lowbit(i)) c[i] += 1;
}

int query(int pos){
    int ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += c[i];
    return ans;
}

int query(int s, int e){
    return this->query(e) - this->query(s-1);
}

void init(int total){
    fill(this->c, this->c+(this->n=total)+1, 0);
}

}C;

int N;
int A[SIZE];

llt proc(){
    C.init(N);
    llt ans = 0;
    for(int i=1;i<=N;++i){
        ans += C.query(A[i], N);
        C.modify(A[i]);
    }
    return ans;    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); 
        for(int i=1;i<=N;++i) A[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}

