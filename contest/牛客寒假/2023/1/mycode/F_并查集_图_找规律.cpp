/**
 * 无向图，从某个点出发，到某个点结束，可以进行如下操作任意次：
 * 1 移动一步，但不能移动到炸弹上
 * 2 当前位置放炸弹
 * 初始节点没有炸弹。给定结束时每个节点的炸弹数量，问
 * 有多少个起点终点点对可以满足给定条件。
 * 即从起点出发，到终点结束，经过若干操作后，使得每个节点的炸弹数量满足给定条件。
 * 注意，虽然不能移动到炸弹上，但是可以在当前位置放任意多的炸弹
 * 所以对每一个连通块，对任意点，对其做一个深搜遍历序，对每个有炸弹的点，出点时将炸弹放足即可
 * 因此无论多少炸弹，无论什么位置，均能完成。
 * 同理可知，对任意连通点对也总有办法放下炸弹。
 * 因此首先找出连通块及其大小，然后根据炸弹分布计算即可
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
int const BLOCKSIZE = 3;
#else
int const SIZE = 100010;
int const BLOCKSIZE = 300;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

vi Father;
void init(int n){
    Father.assign(n + 1, 0);
    for(int i=1;i<=n;++i) Father[i] = i;
}
int find(int x){
    return Father[x] == x ? x : Father[x] = find(Father[x]);
}
void unite(int x, int y){
    Father[find(y)] = find(x);
}

int N, M;
vi W;

llt proc(){
    vi flag(N+1, 0);
    vi cc(N+1, 0);
    int cnt = 0;
    for(int t,i=1;i<=N;++i){
        ++cc[t = find(i)];
        if(W[i] && 0 == flag[t]) {
            cnt += flag[t] = 1;
        }
    }
    if(cnt >= 2) return 0;
    if(1 == cnt)for(int t,i=1;i<=N;++i){
        if(0 == flag[t = find(i)]) continue;
        return (llt)cc[t] * (llt)cc[t];
    }

    llt ans = 0;
    for(int i=1;i<=N;++i){
        if(i != find(i)) continue;
        ans += (llt)cc[i] * (llt)cc[i];
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    init(N);
    for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
        unite(a, b);
    }
    W.assign(N + 1, 0);
    for(int i=1;i<=N;++i) W[i] = getInt();
    cout << proc() << endl;
    return 0;
}


