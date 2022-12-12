/**
 * 给定若干有颜色的区间，对每一个区间问：具体其最近的不同颜色的其他区间的距离是多少
 * 对某个特定的区间，其最近距离的产生，必然要么依赖于其左端点，要么依赖于其右端点，即使是包含也是如此
 * 因此计算两遍，一遍考虑左端点，一遍考虑右端点
 * 首先将按左端点排序，然后维护两个颜色不同的区间，记作u和v
 * u和v是到i位置为止右端点最右的两个区间
 * 此时，所有右端点在i+1区间左端点之前的区间都应该可以计算一个答案
 * 答案根据这些区间的左端点和最右的两个右端点决定
 * 第二遍，只需要将每个区间的左右端点取成负数，再交换一下，用第一遍的流程即可
 * 也可以用线段树做，离散化或者动态开点
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
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif

using vi = vector<int>;

struct _t{
	int s, e, c;
};

int N;
vector<_t> A;
vi Ans;

/// 根据A[pos]，维护两个最右端
void update(int pos, int & kmost, int & k2nd){
	if(-1 == kmost){
		kmost = pos;
		return;
	}

	int omost = kmost;
	int o2nd = k2nd;
	if(A[pos].e > A[kmost].e){
        kmost = pos;
		if(A[omost].c != A[pos].c){
			k2nd = omost;
		}
	}

	if(A[pos].c == A[kmost].c) return;
	if(-1 != k2nd && A[pos].e <= A[k2nd].e) return;

	k2nd = pos;
	return;
}

/// 求A[index]的答案
bool proc(int index, int kmost, int k2nd){
    auto & ans = Ans[index];
	if(-1 != kmost && A[kmost].c != A[index].c){
        ans = min(ans, max(0, A[index].s - A[kmost].e));
	}
	if(-1 != k2nd && A[k2nd].c != A[index].c){
		ans = min(ans, max(0, A[index].s - A[k2nd].e));
	}
	return true;
}

/// 按left顺序求出右端延伸最远的两个区间
/// 按right的顺序依次求解答案
void proc(const vi & left, const vi & right){
    int kmost = -1, k2nd = -1;
	int r = 0;
	for(int i=0;i<N;++i){
        update(left[i], kmost, k2nd);
		while((i < N - 1 && A[right[r]].e < A[left[i+1]].s) || (i+1 == N && r < N)){
			proc(right[r], kmost, k2nd);
			++r;
		}
	}     
}

void proc(){
	Ans.assign(N, INT32_MAX);

    vi left(N, 0), right(N, 0);
    for(int i=0;i<N;++i) left[i] = right[i] = i;

	sort(left.begin(), left.end(), [&](int a, int b){
        const auto & x = A[a];
		const auto & y = A[b];
		if(x.s != y.s) return x.s < y.s;
		if(x.e != y.e) return x.e < y.e;
		return x.c < y.c;
	});
	sort(right.begin(), right.end(), [&](int a, int b){
        const auto & x = A[a];
		const auto & y = A[b];
		if(x.e != y.e) return x.e < y.e;
		if(x.s != y.s) return x.s < y.s;		
		return x.c < y.c;
	});
	proc(left, right);

    for(auto & i : A){
		swap(i.s, i.e);
		i.s = -i.s;
		i.e = -i.e;
	}
	sort(left.begin(), left.end(), [](int a, int b){
        const auto & x = A[a];
		const auto & y = A[b];
		if(x.s != y.s) return x.s < y.s;
		if(x.e != y.e) return x.e < y.e;
		return x.c < y.c;
	});
	sort(right.begin(), right.end(), [](int a, int b){
        const auto & x = A[a];
		const auto & y = A[b];
		if(x.e != y.e) return x.e < y.e;
		if(x.s != y.s) return x.s < y.s;		
		return x.c < y.c;
	});
	proc(left, right);

	for(int i : Ans) printf("%d ", i);
	printf("\n");
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		A.assign(N = getInt(), {0, 0});
		for(auto & p : A){
			p.s = getInt();
			p.e = getInt();
			p.c = getInt();
		}
		proc();
	}
    return 0;
}