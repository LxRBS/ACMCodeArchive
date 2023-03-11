/**
 * 有N跟绳子，M个操作。每次将两根绳子的一端连接。问最后有多少个圈和非圈。
 * 题目中绳子两端有颜色，但并不影响，因为题目保证不会将一根绳子的一端与多根绳子相连
 * 因此做一个并查集即可。连接前查询一下，如果已经在一个集合中，则此次连接会形成一个圈，而且圈内的绳子再也不会用上。
 * 最后再查一下非圈的有几个。
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
	while(ch != 'R' and ch != 'B') ch = __hv007();
	return ch;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

struct _t{

vi father;
void init(int n){father.assign(n + 1, 0);for(int i=1;i<=n;++i)father[i]=i;}
int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
void unite(int x, int y){father[find(y)]=find(x);}

}U;

int N, M;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    U.init(N = getInt());
	M = getInt();

	set<int> cycle;
	for(int i=0;i<M;++i){
		int a = getInt();
		char b = getChar();
		int c = getInt();
		char d = getChar();
		if(U.find(a) == U.find(c)){
			cycle.insert(U.find(a));
		}else{
			U.unite(a, c);
		}
	}

    int ans1 = cycle.size();
	int ans2 = 0;
	vi flag(N + 1, 0);
	for(int i=1;i<=N;++i){
        auto t = U.find(i);
		if(cycle.count(t)) continue;
		if(0 == flag[t]){
			flag[t] = 1;
			++ans2;
		}
	}
	printf("%d %d\n", ans1, ans2);
    return 0; 
}


