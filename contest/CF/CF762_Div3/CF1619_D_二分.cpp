/**
 * M×N个数，要求最多选取N-1行，这N-1行中的每一行可以选取多个数
 * 但最后每一列只能选一个数，因此一个选择方案最后可以选出N个数
 * 令这N个数的最小值为该方案的数值
 * 问如何选取可以令方案数值最大，只需输出这个最大值即可
 * N×M在1e5
 * 可选的方案总数显然是一个组合数求和，比较大。
 * 但是方案数值显然具有单调性，即如果存在方案使得数值大于等于4，
 * 则必然存在方案使得数值大于等于3，反之亦然。
 * 因此使用二分法，检测是否存在方案使得数值大于等于x
 * 需要满足2个条件：
 * 1 N列中均有大于等于x的数
 * 2 至少有一行包含2个或2个以上的x
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

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 100010;
#endif

#define fi first
#define se second

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

int N, M;
vi W[SIZE];

bool Flag[SIZE];

bool check(int anchor){
    fill(Flag, Flag+N, false);
    int two = 0;
    for(int t,i=0;i<M;++i){
        t = 0;
        for(int j=0;j<N;++j){
            if(W[j][i] >= anchor){
                ++t;
                Flag[j] = true;
            }
        }
        if(t >= 2) two = 1;
    }
    if(!two) return false;
    for(int i=0;i<N;++i)if(!Flag[i])return false;
    return true;
}

int proc(){
    int left = 1, right = 1000000000, mid;
    do{
        mid = (left + right)>>1;
        if(check(mid)) left = mid + 1;
        else right = mid - 1; 
    }while(left<=right);
    return right;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        M = getInt(); N = getInt();  
        for(int i=0;i<N;++i) W[i].assign(M, 0);
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                W[j][i] = getInt();
            }
        }
        printf("%d\n", proc());
    }
    return 0;
}
