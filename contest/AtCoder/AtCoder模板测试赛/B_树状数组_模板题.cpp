#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

struct FenwickTree{ // 树状数组

using value_type = long long int;
using vec_type = vector<value_type>;

int n;
vec_type c;

FenwickTree() = default;

static int lowbit(int x){return x & -x;}

void init(int nn){this->c.assign((this->n=nn) + 1, 0);}

void modify(int pos, value_type delta){
    for(int i=pos;i<=this->n;i+=lowbit(i)) this->c[i] += delta;
}

value_type query(int pos)const{
    value_type ans = 0;
    for(int i=pos;i;i-=lowbit(i)) ans += this->c[i];
    return ans;
}

value_type query(int s, int e)const{return this->query(e) - this->query(s - 1);}

};


using llt = long long;
using vll = vector<llt>;

int N, Q;
FenwickTree B;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    B.init(N = getInt());
    Q = getInt();
    for(int i=1;i<=N;++i) B.modify(i, getInt());
    for(int c,a,b,q=1;q<=Q;++q){
        c = getInt(); a = getInt(); b = getInt();
        if(c) printf("%lld\n", B.query(a+1, b));
        else B.modify(a+1, b);
    }
    return 0;
}
