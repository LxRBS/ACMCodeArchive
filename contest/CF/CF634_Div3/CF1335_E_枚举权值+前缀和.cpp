/**
 * 给定一个模式，形如a...ab...ba...a，左右的a的数量要相等，a的数量和b的数量都可以为0，a和b可以相等
 * 给定一个数组A，要求找出A的满足上述模式的最长子序列
 * 注意到Ai只有200，记录每一个Ai的在数组中的位置的数量
 * Left[v][pos], 表示v在[1...pos]的数量
 * Right[v][pos]表示v在[pos...N]的数量
 * Cnt[v]表示v的总数量
 * Pos[v][k]表示v的数量达到k时的最靠左的位置
 * for每一个位置i和当前元素Ai，倒序
 *     k = Right[Ai][i]
 *     pos = Pos[Ai][k]
 *     m = max(Cnt[v]-Left[v][pos]-Right[v][i], 对所有的i)
 *     ans = max(ans, k + k + m)
*/
#include <bits/stdc++.h>
using namespace std;
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 200020;
#endif

int N;
int A[SIZE];
int Cnt[210];
int Left[210][SIZE];
// int Right[210][SIZE];
vector<int> Pos[210];

int proc(){
	if(1 == N) return 1;
	if(2 == N) return A[1] == A[2] ? 2 : 1;

	for(int v=1;v<=200;++v){
		Cnt[v] = 0;
		fill(Left[v], Left[v]+N+2, 0);
		// fill(Right[v], Right[v]+N+2, 0);
		Pos[v].assign(1, 0);
	}

	for(int v, i=1;i<=N;++i){
		++Cnt[A[i]];
		Pos[A[i]].push_back(i);
        for(int v=1;v<=200;++v){
			Left[v][i] = Left[v][i-1] + (A[i]==v?1:0);			 
		}
	}

	int r[210] = {0};
	int ans = 1;
    for(int ai, pos, k, i=N;i;--i){
        k = ++r[ai=A[i]]; // k是当前右边的Ai的数量
        pos = Pos[ai][k]; // pos是ai左边数量为k时的坐标
		if(pos>=i) continue;

        int tmp = 0;
		for(int v=1;v<=200;++v){
            tmp = max(Cnt[v]-r[v]-Left[v][pos], tmp);
		}   
		ans = max(tmp+k+k, ans);
	}
	return ans; 
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%d\n", proc());
    }
    return 0;
}

