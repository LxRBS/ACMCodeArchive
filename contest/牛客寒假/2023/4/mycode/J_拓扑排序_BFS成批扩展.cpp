/**
 * 给定N个整数以及M对偏序关系，问如果对这N个整数排序，能否确定每个整数的位置
 * 对第i个整数，如果其排序后的位置是唯一确定的，输出那个位置，如果不确定输出-1
 * 偏序关系显然具有有向边的特征。构造一个M条边的有向图，假设边是从小到大。
 * 显然入度为0的点要排在前面。如果有sz个入度为0的点怎么版？说明这些点可选的位置是{1, sz}
 * 因此使用成批扩展的BFS，对同批次入队的节点，其可选位置是{cur, cur + sz - 1}
 * 然后维护cur，根据度数入队即可。于是对每个节点得到了其位置的可能范围{first, second}
 * 仅这样还不够，还要对反向图再做一遍，再得到一个范围{s, e}
 * 如果 s == e == first == second，则该点是唯一确定的。否则-1
 * 拓扑排序是线性的。
 * 标程是暴力，对每个数搜索一遍，看是否能够确定比其小的数以及比它大的数的数量。
 * O(NM)，比较极限，但是可以用bitset优化一下。O(NM/64)应该没问题。
 */
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

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int N, M;
vvi G, U;
vi GDeg, UDeg;
vector<array<int, 2>> BackAns, ForAns;

void proc(){
    queue<int> q;
    for(int i=1;i<=N;++i)if(0==GDeg[i])q.push(i);

    int sz = 0;
    int k = N;
    while(sz = q.size()){
        auto two = k;
        auto one = k - sz + 1;

        while(sz--){
            auto h = q.front(); q.pop();
            BackAns[h] = {one, two};
            for(auto v : G[h]){
                if(0 == --GDeg[v]) q.push(v);
            }
        }      

        k = one - 1;
    }

    for(int i=1;i<=N;++i)if(0==UDeg[i])q.push(i);

    sz = 0;
    k = 1;
    while(sz = q.size()){
        auto one = k;
        auto two = k + sz - 1;

        while(sz--){
            auto h = q.front(); q.pop();
            ForAns[h] = {one, two};
            for(auto v : U[h]){
                if(0 == --UDeg[v]) q.push(v);
            }
        }

        k = two + 1;
    }


    // for(int i=1;i<=N;++i){
    //     printf("%d: (%d, %d), (%d, %d)\n", i, ForAns[i][0], ForAns[i][1], BackAns[i][0], BackAns[i][1]);
    // }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
    G.assign(N + 1, vi());
    U.assign(N + 1, vi());
    GDeg.assign(N + 1, 0);
    UDeg.assign(N + 1, 0);
    for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
        G[b].emplace_back(a);
        U[a].emplace_back(b);
        ++GDeg[a]; ++UDeg[b];
    }

    BackAns.assign(N + 1, {-1, -1});
    ForAns.assign(N + 1, {-1, -1});
    proc();
    vi flag(N + 1, -1);
    for(int i=1;i<=N;++i){
        if(ForAns[i][0] == ForAns[i][1] && BackAns[i][0] == BackAns[i][1] && ForAns[i][0] == BackAns[i][0]){
            flag[ForAns[i][0]] = i;
        }
    }
    for(int i=1;i<=N;++i)printf("%d%c", flag[i], (i==N?'\n':' '));
    return 0;
}