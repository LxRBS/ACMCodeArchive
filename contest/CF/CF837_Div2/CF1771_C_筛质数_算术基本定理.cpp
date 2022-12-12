/**
 * 给定数组A，问能不能找到两个元素具有大于1的公约数
 * 将每个Ai按照质因子分解即可
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
int const SIZE = 35000;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;

vector<bool> isComp;
vi P;

void sieve(int sz){
    isComp.assign(sz, false);
    P.reserve(sz);
    llt tmp;
    for(int i=2;i<sz;++i){
        if(!isComp[i]) P.push_back(i);
        for(int j=0,n=P.size();j<n&&(tmp=i*P[j])<sz;++j){
            isComp[tmp] = true;
            if(0 == i % P[j]) break;
        }
    }
}

int N;
vi A;
si S;

bool proc(){
    S.clear();
    for(int n : A){
        for(int i : P){
            if(n % i == 0){
                if(S.count(i)) return true;
                S.insert(i);

                while(n % i == 0) n /= i;
            }
            if(i * i > n) break;
        }
        if(n != 1){
            if(S.count(n)) return true;
            S.insert(n);
        }
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    sieve(35000);
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
        A.assign(N = getInt(), 0);
        for(int & i : A) i = getInt();
        puts(proc()?"YES":"NO");
	}
    return 0;
}