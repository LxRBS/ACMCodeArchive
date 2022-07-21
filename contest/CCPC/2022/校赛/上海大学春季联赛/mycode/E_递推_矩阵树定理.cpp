/**
 * 首先写一个行列式，令
 *         | a+1 1   1   |
 * gn(a) = | 1   a+1 1   |
 *         | 1   1   a+1 | n*n
 * 即主对角线为a+1，其余全为1的行列式，
 * 该式可以直接化为上三角行列式得 gn = (1+n/a)*a^n
 * 再令 fn(a) = |主对角线为a，其余全为-1|
 * 有 fn(a) = (-1)^n*g(-a-1) = (a+1)^n * (a+1-n)/(a+1) 
 *         = (a+1)^(n-1) * (a+1-n)
 * 
 * 该题本质上就是一个完全图，边的权值由max(i, j)/b决定，所以有若干组若干个权值一样的边
 * 问最小生成树的数量，权值数量在1E6。
 * 考虑权值为1的边，这些点的生成树肯定只用权值为1的边，假设其节点数量为N1，则生成树数量为N1^(N1-2)。
 * 可以用prufer序列证明，也可以用矩阵树定理，令n=N1，实际上就是计算 f[n-1](n-1) = n^(n-2)
 * 再考虑权值为2的边的关联的点，把N1看做是一个没有结构的点，则现在是要做N2+1个节点的MST，
 * 同样使用矩阵树定理，这个图的拉普拉斯矩阵是一个(N2+1)方阵
 * N1*N2 -1      -1      -1        
 * -1    N1+N2-1 -1      -1
 * -1    -1      N1+N2-1 -1
 * -1    -1      -1      N1+N2-1
 * 则该图的MST数量就是 f[N2](N1+N2-1) = N1 * (N1+N2)^(N2-1)
 * 再考虑N1内部一共有N1^(N1-2)个不同的结构，所以考虑2组边之后MST的数量是二者乘起来
 * 当A>=B时，则没有完全图使得内部边权一致，也就是说都是单点的，即所有分组的点数量均为1
 * 当A<B时，则可能存在完全图其内部边权相等，需要求出每个完全图的顶点数量
 * 所有分组的定点数量确定，可用上述原理递推。
 */
#include <bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
int const SIZE = 1E6+10;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long int;
llt const MOD = 998244353LL;

llt pow(llt a, llt n){
	llt ret = 1; a %= MOD;
	while(n){
		if(n & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}

llt N, A, B;
llt Cnt[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin >> N >> A >> B;  
	
	/// 首先计算每组边的数量
    llt cnt = 0;
	llt prev = 0, k = 2, cur;
	if(A<=B)while(1){
	    llt tmp = k * B;
		cur = tmp / A;
		if(0 == tmp % A) --cur;
		cnt += Cnt[k-1] = cur - prev;
		if(cnt >= N){
			Cnt[k-1] -= cnt - N;
			break;
		}
		prev = cur;
		++k;
		// cout<<k<<endl;
	}else{ // 此时，没有成堆的点
		for(int i=N;i;--i){
			Cnt[i] = 1;
		}
		k = N + 1;
	}
	
	/// 依次计算结果
	llt ans = 1 == Cnt[1] ? 1 : pow(Cnt[1], Cnt[1]-2);
	cnt = Cnt[1];
	for(llt i=2;i<k;++i){
        ans = ans * (cnt * pow(cnt + Cnt[i], Cnt[i]-1) % MOD) % MOD;  
		cnt = (cnt + Cnt[i]) % MOD;
	}
	cout << ans << endl;
    return 0;
}
