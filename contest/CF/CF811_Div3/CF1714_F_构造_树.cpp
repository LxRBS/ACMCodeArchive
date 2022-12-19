/**
 * 给定N和D12、D23、D13，要求构造一棵树：
 * 1 一共有N个节点
 * 2 12、23、13的距离分别等于D12、D23和D13
 * 设Ci是节点i距离根的距离，i=1,2,3
 * 很容易解出，如果Ci是负数，或者D之和为奇数则无解
 * 否则根据Ci首先构造123的分支，如果超过了N个节点限制，也无解
 * 接着把剩下的节点都接在根上即可
 * 注意1/2/3自身就有可能是根
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long; 
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using t3t = tuple<int, int, int>;

int N;
int A[3];
int B[4][4];

int T;
int C[4];

void proc(int root){
	int k = (root <= 3) ? 4 : 5;
	vpii ans;
	for(int i=1;i<=3;++i){
        if(root == i) continue;
		if(1 == C[i]){
			ans.emplace_back(root, i);
			continue;
		}
		ans.emplace_back(root, k);
		for(int j=2;j<C[i];++j){
			ans.emplace_back(k, k + 1);
			++k;
		}
		ans.emplace_back(i, k++);
	}
	if(k > N + 1) return (void) printf("NO\n");
	for(int i=k;i<=N;++i){
        ans.emplace_back(root, i);
	} 

	printf("YES\n");
	for(const auto & p : ans) printf("%d %d\n", p.first, p.second);
	return;
}

void proc(){
	B[1][2] = B[2][1] = A[0];
	B[2][3] = B[3][2] = A[1];
	B[3][1] = B[1][3] = A[2];

    T = accumulate(A, A+3, 0);
	if(T & 1) return (void)printf("NO\n"); 

	sort(A, A+3);
	if(A[2] > A[0] + A[1]) return (void)printf("NO\n"); 
 
    T /= 2;
	C[1] = T - B[2][3];
	C[2] = T - B[1][3];
	C[3] = T - B[1][2];

	if(0 == C[1]) return (void)proc(1);
	if(0 == C[2]) return (void)proc(2);
	if(0 == C[3]) return (void)proc(3);
	return (void)proc(4);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int & i : A) i = getInt();
		proc();
	}
    return 0;
}


