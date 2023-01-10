/**
 * 给定N*M的矩阵，找到一个最大的K，使得矩阵中存在K*K的子矩阵且子矩阵的元素均大于等于K
 * 显然子矩阵具有单调性，假设存在3*3的矩阵大于等于3，则必然存在2*2的矩阵大于等于2
 * 因此可以二分K
 * 对每一个K，要检查是否存在K*K的方阵，最小元素大于等于K，使用二维ST表
 * O(NMlogN)
 * 检查方阵时，也可以不用ST表，而用前缀和，不过没有ST表直接。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vvi A;
vvi S[22];

int query(int r, int c, int x){
    int k = (int)(log((double)x) / log(2.0));
    int ans = S[k][r][c];
    // if((1 << k) == x) return ans;
    // assert((1 << k) < x);
    ans = min(ans, S[k][r][c+x-(1<<k)]);
    ans = min(ans, S[k][r+x-(1<<k)][c]);
    ans = min(ans, S[k][r+x-(1<<k)][c+x-(1<<k)]);
    return ans;
}

bool check(int x){
    for(int i=0;i<=N-x;++i)for(int j=0;j<=M-x;++j){
        if(query(i, j, x) >= x){
            return true;
        }
    }
    return false;
}

int proc(){
    for(int i=0;i<22;++i) S[i].assign(N, vi(M, 0));

    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        S[0][i][j] = A[i][j];
    }   

    for(int t,k=1;(t=(1<<k))<=M;++k){
        for(int i=0;i+t<=N;++i)for(int j=0;j+t<=M;++j){
            auto p1 = S[k-1][i][j];
            auto p2 = S[k-1][i+(1<<k-1)][j];
            auto p3 = S[k-1][i][j+(1<<k-1)];
            auto p4 = S[k-1][i+(1<<k-1)][j+(1<<k-1)];
            S[k][i][j] = min(min(p1, p2), min(p3, p4));
        }    
    }

    int left = 1, right = N, mid;
    do{
        mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    return right;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        A.assign(N, vi(M, 0));
        for(auto & v : A)for(int & i : v) i = getInt();
        printf("%d\n", proc());       
    }
    return 0;
}


