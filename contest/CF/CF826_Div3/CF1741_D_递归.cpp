/**
 * 给一个满二叉树，所有叶子赋权形成一个排列
 * 问能否通过交换左右子树，使得叶子权值严格升序，如果能，最少要几次操作
 * 假设12345678在一个子树下，
 * 如果1234整体在5678的左边，则根节点无需调整
 * 如果在右边，则次数加1
 * 如果是夹杂分布的，则不能
 * 写一个递归即可
 */
#include <assert.h>
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E6+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;

int N;
int A[SIZE], B[SIZE];
int Ans = 0;

int check(int s, int m, int e, int left, int val, int right){
	int t = -2;
	for(int i=s;i<=m;++i){
		if(left <= A[i] && A[i] <= val){
            if(-2 == t || 0 == t) t = 0;
			else return -1;
		}else if(val < A[i] && A[i] <= right){
			if(-2 == t || 1 == t) t = 1;
			else return -1;
		}
		else return -1;
	}
	return t;
}

void dfs(int s, int e, int left, int right){
	if(s == e){
		assert(left == right);
		return;
	}
    int mid = (left + right) >> 1;
	// [left, mid] 应该在一起, [mid+1, right]在另一半 
	int pos = (s + e) >> 1;
	int t = check(s, pos, e, left, mid, right);
	if(-1 == t){
		Ans = -1; return;
	}
	if(0 == t){
		dfs(s, pos, left, mid);
		if(-1 == Ans) return;
		
		dfs(pos+1, e, mid+1, right);	
		return;
	}

    ++Ans;
	dfs(s, pos, mid+1, right);
	if(-1 == Ans) return;

	dfs(pos+1, e, left, mid);
	return;
}

int proc(){
    Ans = 0;
    dfs(1, N, 1, N);
	return Ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) (A[i] = getInt());
		printf("%d\n", proc());
	}
    return 0;
}
