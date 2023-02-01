/**
 * C题的HARD版本，N和M改成了5000，所以不能再用立方算法，要用平方算法
 * 考虑Aiv和Biv两种DP，Aiv表示到i位置不超过v的最大收益，
 * Biv为从i到N代价不超过v的最大收益，注意不能滚动优化。
 * 则对每一个物品i，在某一个体积v下
 * A[i-1][v] + B[i+1][M-v-Vi] + Wi
 * 就是此情形下使用物品i能获得的最大收益
 * 遍历所有v，求一个最大值，MMax + 1 - 此最大值 可以保证物品i必选。
 * 还要考虑i本来就必选的情况，对每一个v，
 * A[i-1][v] + B[i+1][M-v] 就是此时不选物品i能拿到的最大值
 * 同样遍历v，可以得到不选物品i的最大值，如果该值小于Max，说明i本来就必选。
 * O(N^2)
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vll = vector<long long>;
using pil = pair<int, llt>;
using vpil = vector<pil>;
using vvll = vector<vll>;

int N, M;
vpil Hudie;
vvll A, B;
llt MMax;

llt proc(int pos){
    int pre = pos - 1;
	int nxt = pos + 1;

	auto daijia = Hudie[pos].first;
	auto shouyi = Hudie[pos].second;

    llt ans = INT64_MAX;
	llt d = 0LL;
	for(int v=0;v<=M;++v){
		d = max(d, A[pre][v] + B[nxt][M-v]);
		if(v + daijia <= M){
			auto tmp = A[pre][v] + B[nxt][M-v-daijia] + shouyi;
			assert(MMax >= tmp);
			ans = min(ans, MMax + 1LL - tmp); 			
		}
	}
	if(d < MMax) return 0;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
	Hudie.assign(N + 1, {});
	for(int w,v,i=1;i<=N;++i){
        cin >> w >> v;
		Hudie[i] = {w, v};
	}

    A.assign(N + 2, vll(M + 1, 0LL));
	B.assign(N + 2, vll(M + 1, 0LL));

	for(int i=1;i<=N;++i){
		const auto & p = Hudie[i];
		auto & Ai = A[i];
		auto & Aip = A[i - 1];
		for(int v=1;v<=M;++v){
			Ai[v] = Aip[v];
			if(v >= p.first) Ai[v] = max(Ai[v], Aip[v - p.first] + p.second);
		}
	}

	for(int i=N;i>=1;--i){
		const auto & p = Hudie[i];
		auto & Bi = B[i];
		auto & Bip = B[i + 1];
		for(int v=1;v<=M;++v){
			Bi[v] = Bip[v];
			if(v >= p.first) Bi[v] = max(Bi[v], Bip[v - p.first] + p.second);
		}
	}

	MMax = A[N][M];
	assert(MMax == B[1][M]);

    for(int i=1;i<=N;++i){
		printf("%lld\n", proc(i));
	}    
    return 0;
}