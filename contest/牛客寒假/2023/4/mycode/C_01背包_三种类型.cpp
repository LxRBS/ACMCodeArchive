/**
 * 给一个01背包，对每一种物品，问若要让该物品变为必选，该物品的收益至少要加多少。
 * 首先跑一个01背包，求出Max。
 * 然后对每一种物品，将其排除，再跑一个背包，如果此时的 max < Max, 说明此物品本来就是必选的， 答案为0
 * 否则, 比较麻烦。由于N和M只有100，可以二分。对每一个非必须的物品，如果将其收益改为mid，看看跑出来的max是多少
 * max显然具有单调性。第一个令 max > Max 的 mid 可以确保该物品必选。 计算一下差值即可。
 * O(N^3 * log(MaxValue))
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vll = vector<long long>;
using pil = pair<int, llt>;
using vpil = vector<pil>;

int N, M;
vpil Hudie;
vll D;
llt MMax;

llt check(int pos, llt mid){
	vll d(M+1, 0LL);
	for(int i=0;i<N;++i){
		if(i == pos)for(int v=M;v>=Hudie[pos].first;--v){
            d[v] = max(d[v], d[v - Hudie[pos].first] + mid);
		}else for(int v=M;v>=Hudie[i].first;--v){
			d[v] = max(d[v], d[v-Hudie[i].first] + Hudie[i].second);
		}
	}	
	return d[M];
}

llt proc(int pos){
	vll d(M+1, 0LL);
	for(int i=0;i<N;++i){
		if(i == pos) continue;
		for(int v=M;v>=Hudie[i].first;--v){
			d[v] = max(d[v], d[v-Hudie[i].first] + Hudie[i].second);
		}
	}
	if(d[M] < MMax) return 0;

	llt left = 0, right = MMax, mid;
	do{
		mid = (left + right) >> 1;
        if(check(pos, mid) > MMax) right = mid - 1;
		else left = mid + 1;
	}while(left <= right);
	return left - Hudie[pos].second;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
	Hudie.reserve(N);
	for(int w,v,i=0;i<N;++i){
        cin >> w >> v;
		Hudie.emplace_back(w, v);
	}

    D.assign(M + 1, 0LL);
    for(const auto & p : Hudie){
		for(int v=M;v>=p.first;--v){
			D[v] = max(D[v], D[v-p.first] + p.second);
		}
	}
	MMax = D[M];

	for(int i=0;i<N;++i){
		printf("%lld\n", proc(i));
	}
    return 0;
}