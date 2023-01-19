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

struct UFSet{

vector<int> father;

void init(int n){father.assign(n+1, 0);for(int i=1;i<=n;++i)father[i]=i;}

int find(int x){return father[x]==x?x:father[x]=find(father[x]);}

void unite(int x, int y){father[find(y)]=find(x);}

};


using llt = long long;
using vll = vector<llt>;

int N, Q;
UFSet U;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    U.init(N = getInt());
    Q = getInt();
    for(int c,u,v,q=1;q<=Q;++q){
        c = getInt(); 
        u = getInt() + 1;
        v = getInt() + 1;
        if(c) puts(U.find(u)==U.find(v)?"1":"0");
        else U.unite(u, v);
    }
    return 0;
}
