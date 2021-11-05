/**
  N组数，每组数编号从1到ci，不降序排列
  再给定M组数，每组数N个，表示序号
  现在要求从N个组里每组挑出一个数，满足：
  序号排列没有出现在M中，和尽可能大
  例如：
  2
  3 1 2 3
  3 1 2 3
  1
  3 3
  一共2组数，每组数3个
  挑出33是和最大的，但是33属于M，因此是禁止的
  因此答案是32或者23
  显然从ci序列开始搜索，用优先级队列保证和最大，用哈希来编码状态
  注意哈希要用大一点，131和1331均不行，13331正确。
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_set

typedef long long int llt;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vp;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 200100;
#endif

int N, M;
int C[11];
llt A[11][SIZE];

struct _t{
	vi vec;
	llt sum;
	_t():vec(), sum(0LL){}
};

bool operator < (const _t &a, const _t &b){
	return a.sum < b.sum;
}

priority_queue<_t> Q;
// priority_queue<_t> T;
hash_t<llt> Flag;
hash_t<llt> Set;

inline llt h(const vi &v){
	llt t = 0;
	for(auto i: v) t = t * 13331LL + i;
	return t;
}

vi proc(){
    _t start;
	for(int i=1;i<=N;++i){
		start.vec.pb(C[i]);
		start.sum += A[i][C[i]];
	}

	llt code = h(start.vec);
	if(Set.find(code) == Set.end()) return start.vec;

	Q.push(start);
	Flag.insert(code);

	while(!Q.empty()){		
		_t t = Q.top(); Q.pop();
        llt c = h(t.vec);
		if(Set.find(c) == Set.end()) return t.vec;

		for(int j,i=1;i<=N;++i){
			if(1 == (j=t.vec[i-1])) continue;

			llt ns = t.sum + A[i][j-1] - A[i][j];
			--t.vec[i-1]; 
			llt nc = h(t.vec);
			swap(t.sum, ns);
			if(Flag.find(nc) == Flag.end()){
				Q.push(t);
				Flag.insert(nc);
			}

			++t.vec[i-1];
			swap(t.sum, ns);
		}

	}

	throw runtime_error("XXX");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = 1;
    while(nofkase--){
        N = getUnsigned();
		for(int i=1;i<=N;++i){            
			for(int j=1,n=C[i]=getUnsigned();j<=n;++j){
				A[i][j] = getUnsigned();
			}			
		}

		M = getUnsigned();
		for(int i=1;i<=M;++i){	
			llt t = 0;		
            for(int j=1;j<=N;++j){
				t = t * 13331LL + getUnsigned();
			}
			Set.insert(t);
		}
		vi ans = proc();
		for(auto i: ans) printf("%d ", i);
        printf("\n");
    }
    return 0;
}
