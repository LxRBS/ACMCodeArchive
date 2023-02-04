/**
 * 一共N轮，每一轮可以压任意数目筹码(必须是正数!!!)，如果输了，就失去这些筹码
 * 如果赢了，可以额外获得等量数目。
 * 现在确定N轮中只有一场能赢。且筹码总数是M。
 * 现在要求分配一个压筹码的方案，要求该方案必定不亏，且是最优的。所谓最优是指
 * 任意两个方案，如果第i轮获胜则，则之前每轮结束剩余筹码数量相同，且获胜后总数越多越优。
 * 首先考虑必定不亏的方案。如果第i轮获胜，则第i轮额外赢得的筹码是Ai，前i-1轮亏的总数是S[i-1]
 * 所以必然有A[i] >= S[i-1]。所以An至少是M的一半，根据M的奇偶性还要做一点调整。
 * 然后依次往前推类似。如果M分完了，N还没有完，由于必须压正数，此时返回 -1， 表示没有方案。
 * 如果到N，M也刚好分完，就OK了。如果到N，M还没有完，则考虑第二个条件，要求方案最优。
 * 显然要求第一轮在允许范围内压的越多越好。
 * 因为一旦第一轮获胜，压的多的方案显然优于压的少的。后续轮次也是一样的，在范围内，压得越多越好
 * 于是再循环一遍，把剩下的筹码分配出去。
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 33;
#endif

using llt = long long;

int N;
long long M;

void proc(){
	if(1 == N){
		return (void)printf("%lld\n", M);
	}
	// if(proc2()){
	// 	return;
	// }
    vector<llt> d; d.reserve(N);
	auto v = M;
	while(1){
		if(v & 1){
			auto tmp = v - v / 2;
			d.emplace_back(tmp);
			v = v - tmp;
		}else{
			auto tmp = v / 2;
			d.emplace_back(tmp);
			v = v - tmp;
		}
		if(d.size() == N) break;
		if(0 == v) return (void)puts("-1");
	}
    
	if(0 == v){
		auto tmp = N - d.size();
		for(int i=0;i<tmp;++i)printf("0 ");
		for(auto it=d.rbegin(),et=d.rend();it!=et;++it)printf("%lld ", *it);
		printf("\n");	
		return;	
	}

    int k = N - 1;
    while(v){
		if(k >= 1){
            auto cha = min(v, d[k-1] - d[k]);
			d[k] += cha;
			v -= cha;
		}else{
			d[k] += v;
			v = 0;
		}
        
		if(0 == v) break;
		--k;
	}
	for(auto it=d.rbegin(),et=d.rend();it!=et;++it)printf("%lld ", *it);
	printf("\n");	
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    cin >> N >> M;
	proc();
    return 0;
}