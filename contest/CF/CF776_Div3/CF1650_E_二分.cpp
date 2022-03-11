/**
 * 给定一行白格共D个，其中N个涂黑，两个黑个之间的白格数量的最小值记作收益
 * 特别的，第一个黑格前面的白格数量也要纳入比较。
 * 现在允许移动一个黑格的位置，即将原位置变白且另找一个白格变黑
 * 问移动后收益最大是多少，N在2E5，D在1E9
 * 显然可以二分，对给定x，问是否经过一次操作满足间距都大于等于x
 * 首先检查一遍两两间距，如果合格就直接返回了
 * 如果有间距小于x，且数量超过2，肯定就不行了
 * 如果小于x的间距数量为2个，且是分开的，那也不行
 * 如果小于x的间距数量为2个，且连在一起，则必须将中间那个拿走，看是否满足
 * 如果小于x的间距只有一个，则可以移动左边也可以右边，有一个满足即可
 * 至于能否找到新的位置放下，挨个检查一下即可，如果有间距大于等于2x+2，就可以放
 * 头尾可以特判一下。NlogD
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 37;
#else
int const SIZE = 2E5+10;
#endif

typedef pair<int, int> pii;
int N, D;
int A[SIZE] = {0};

bool isOK(int gap, int idx){
    if(0 == idx) return false;	
	if(A[idx+1] - A[idx-1] < gap + 1) return false;    
	if(A[idx+1] - A[idx-1] >= gap + gap + 2) return true;		
    /// 直接放在最后一个即可
	if(idx != N && D - A[N] >= gap + 1) return true;
	if(idx == N && D - A[N-1] >= gap + 1) return true;

    for(int i=0;i<idx;++i){
		if(A[i+1] - A[i] >= gap + gap + 2){
			return true;
		}
	}
	for(int i=idx+1;i<N;++i){
		if(A[i+1] - A[i] >= gap + gap + 2){
			return true;
		}
	}
	return false;
}

bool check(int gap){	
	vector<pii> vec;
    for(int i=1;i<=N;++i){
        if(A[i] - A[i-1] < gap + 1){
			vec.emplace_back(i-1, i);
		}
	}
	if(vec.empty()) return true;
	if(vec.size() > 2) return false;
	if(2 == vec.size()){
		if(vec.front().second != vec.back().first){
			return false;
		}
		if(isOK(gap, vec.front().second)){
			return true;
		}
		return false;
	}
    if(isOK(gap, vec.front().first)){
		return true;
	}	
	if(isOK(gap, vec.front().second)){
		return true;
	}
	return false;
}

int proc(){
    int left = 0, right = D, mid;
	do{
		int mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);
	return right;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
	    N = getInt(); D = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
		A[N+1] = D + 1;
        printf("%d\n", proc());
	}
    return 0;
}
