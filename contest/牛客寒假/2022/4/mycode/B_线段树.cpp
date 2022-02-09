/**
 * 长度为N的数字串S，N在1E5，一共有Q个操作，操作有两种
 * 1 pos v: 将pos位置修改为v，v必然在0~9
 * 2 x y: S[x..y]在任意合法进制下所能表示的最小的数值
 * 显然进制越小值越小，所以假设d是S[x..y]的最大值，则只需计算d+1进制下的数值即可
 * 直接算必然超时，考虑到这其实是求和操作，可以使用线段树
 * 对每个进制建立一个线段树，对于d进制的线段树而言：
 * pushUp操作是: sum = leftsum * d ^ (e-mid) + rightsum
 * query操作中的合并需要注意一下，其余跟普通线段树没区别
 * 当然还需要一个查询最大值的线段树。
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
int const SIZE = 12;
#else
int const SIZE = 101010;
#endif

typedef long long llt;
llt const MOD = 1000000007LL;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;};

int StPeak[SIZE<<2];

inline void _pushUp(int t){
	StPeak[t] = max(StPeak[lson(t)], StPeak[rson(t)]);
}

void modify(int t, int s, int e, int pos, int newValue){
	if(s == e){
		StPeak[t] = newValue;
		return;
	}

    int mid = (s+e) >> 1;
	if(pos<=mid) modify(lson(t), s, mid, pos, newValue);
	else modify(rson(t), mid+1, e, pos, newValue);
	_pushUp(t);
	return;
}

int query(int t, int s, int e, int a, int b){
	if(a<=s&&e<=b){
		return StPeak[t];
	}
	int mid = (s+e) >> 1;
	int ans = -1;
    if(a<=mid) ans = max(ans, query(lson(t), s, mid, a, b));
	if(mid<b) ans = max(ans, query(rson(t), mid+1, e, a, b));
	return ans;
}


llt Pow[11][SIZE];

struct _t{
    llt st[SIZE<<2];
	int d;
	void pushUp(int t, int s, int e){
        int mid = (s+e) >> 1;
		int n = e - mid;
		this->st[t] = (this->st[lson(t)] * Pow[d][n] % MOD + this->st[rson(t)]) % MOD;
	}
	void modify(int t, int s, int e, int pos, int newValue){
		if(s == e){
			this->st[t] = newValue;
			return;
		}

		int mid = (s+e) >> 1;
		if(pos<=mid) this->modify(lson(t), s, mid, pos, newValue);
		else this->modify(rson(t), mid+1, e, pos, newValue);
		this->pushUp(t, s, e);
	}
	llt query(int t, int s, int e, int a, int b){
		if(a<=s&&e<=b){
			return this->st[t] % MOD;
		}
		
		int mid = (s+e) >> 1;
		llt lans = -1;
		if(a<=mid) lans = this->query(lson(t), s, mid, a, b);
		llt rans = -1;
		if(mid<b) rans = this->query(rson(t), mid+1, e, a, b);
		if(lans != -1){
			int n = min(b, e) - mid;
			if(rans != -1) return (lans * Pow[this->d][n] % MOD + rans) % MOD;
			return lans;
		}
		return rans;
	}
}St[10];

int N, Q;
char Input[SIZE];

void build(int t, int s, int e){
    if(s == e){
		int x = Input[s] - '0';
		StPeak[t] = x;
		for(int i=0;i<10;++i){
			St[i].st[t] = x;
		}
		return;
	}

	int mid = (s+e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t);
	for(int i=0;i<10;++i) St[i].pushUp(t, s, e);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%s", &N, &Q, Input+1);
	for(int i=1;i<=10;++i) {
	    Pow[i][0] = 1LL;
	    St[i-1].d = i;
	}
	for(int i=1;i<=N;++i){
		for(int j=1;j<=10;++j){
			Pow[j][i] = Pow[j][i-1] * j % MOD;
		}
	}
    build(1, 1, N);
    for(int cmd,x,y,q=1;q<=Q;++q){
        cmd = getInt();
		x = getInt();
		y = getInt();
		if(1==cmd){
            modify(1, 1, N, x, y);
			for(int i=0;i<10;++i) St[i].modify(1, 1, N, x, y);
		}else if(2==cmd){
            int d = query(1, 1, N, x, y);
			printf("%lld\n", St[d].query(1, 1, N, x, y));
		}else{
			throw runtime_error("XX");
		}
	}
    return 0;
}


