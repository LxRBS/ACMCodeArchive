/**
 * 给定两个有序数组A和B，且所有元素互异，假设C是A和B合并后的有序数组
 * 求A和B的每个元素在C中的位置。
 * 归并一下即可。
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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;


int N, M;
vi A, B;
vi U, V;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    A.assign(N = getInt(), 0);
	B.assign(M = getInt(), 0);
	for(auto & i : A) i = getInt();
	for(auto & i : B) i = getInt();

	U.assign(N, 0);
	V.assign(M, 0);

	int k = 0;
	int a = 0, b = 0;
	while(a < N and b < M){
		if(A[a] < B[b]){
            U[a++] = ++k;
		}else if(A[a] > B[b]){
			V[b++] = ++k;
		}else{
			assert(0);
		}
	}
    while(a < N){
		U[a++] = ++k;
	}
	while(b < M) V[b++] = ++k;


	for(int i : U) printf("%d ", i); printf("\n");
	for(int i : V) printf("%d ", i); printf("\n");
    return 0; 
}
