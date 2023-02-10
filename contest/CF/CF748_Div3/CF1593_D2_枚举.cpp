/**
 * 给定N（偶数）元素的数组A，选定K，每次操作选定Ai令Ai-=K
 * 要求不限次数的操作后，令数组中至少有一半元素相等，
 * 问最大的可能的K是多少。
 * 
 * 首先特判要不要输出-1
 * 跟D1一样，必然是gcd，但是不确定是哪一半
 * 因为N仍然在40，首先求出所有两两之差。
 * 然后求出所有的差的因子
 * 然后枚举每一个因子f，检查以f为因子的差所对应Ai是否达到了一半
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

typedef long long llt;

#define fi first
#define se second

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 50;
#endif

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

typedef unordered_map<int, int> hash_t;
int N, OriginN;
int A[SIZE];

hash_t Map;
map<int, vector<int> > Fac2Cha;
unordered_map<int, vector<pair<int, int> > > Cha2Pair;

int f(int fac, int start){
	int ans = Map[A[start]];
	for(int i=start+1;i<=N;++i){
		if((A[i] - A[start])%fac == 0){
			ans += Map[A[i]];
		}
	}
	return ans;
}

bool check(decltype(Fac2Cha.rend()) it){
	int ans = 0;
	for(int i=1;i<N;++i){
		ans = max(ans, f(it->first, i));
		if(ans >= (OriginN+1) / 2) return true;
	}
	return false;
}

int proc(){	
    sort(A+1, A+N+1);
	N = unique(A+1, A+N+1) - A - 1;

    Fac2Cha.clear();Cha2Pair.clear();
	for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
		Cha2Pair[A[j] - A[i]].push_back({A[i], A[j]});
	}    

	for(auto pp: Cha2Pair){
        for(llt i=2;i*i<=pp.fi;++i){
			if(pp.fi%i==0){
				Fac2Cha[i].push_back(pp.fi);
				if(i*i != pp.fi) Fac2Cha[pp.fi/i].push_back(pp.fi);
			}
		}
		Fac2Cha[pp.fi].push_back(pp.fi);
	}

	for(auto it=Fac2Cha.rbegin();it!=Fac2Cha.rend();++it){
		if(check(it)) return it->first;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		Map.clear();
		OriginN = N = getInt();
	    int mmax = 0;
		for(int i=1;i<=N;++i) mmax = max(mmax, ++Map[A[i] = getInt()]);
		printf("%d\n", mmax >= (N + 1) / 2 ? -1 : proc());
	}
    return 0;
}