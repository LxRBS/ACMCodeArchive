/**
 * 定义求和操作为位或，给定一个图，求最小生成树
 * 最多只有31位，可以从高到底枚举每一位确定答案
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
int const SIZE = 15;
#else
int const SIZE = 201010;
#endif

int Father[SIZE];
void init(int n){for(int i=1;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)]=find(x);}

typedef tuple<int, int, int> t3t;

int N, M;
t3t Edges[SIZE];

int f(int ans, int idx){
	int bit = 1 << idx;
	init(N);
    ans ^= bit;
	for(int a,b,w,i=1;i<=M;++i){
        a = get<0>(Edges[i]);
        b = get<1>(Edges[i]);
        w = get<2>(Edges[i]);
		if(find(a) != find(b) && (ans | w) == ans){
            unite(a, b);
		}
	}
	int t = find(1);
	for(int i=2;i<=N;++i)if(t!=find(i)) return ans | bit;
	return ans;
}

int proc(){
	int ans = 0x7FFFFFFF;
    for(int i=30;i>=0;--i){
        ans = f(ans, i);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
	int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		M = getInt();
		for(int i=1;i<=M;++i){
			get<0>(Edges[i]) = getInt();
			get<1>(Edges[i]) = getInt();
			get<2>(Edges[i]) = getInt();
		}
		printf("%d\n", proc());
	} 
    return 0;
}
