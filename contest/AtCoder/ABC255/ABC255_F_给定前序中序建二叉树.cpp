/**
  给定前序遍历和中序遍历建二叉树，注意给定的数据有可能无法构建，此时输出-1
  基础问题，O(N)解法
  没有注意到有可能无法建树，RE了好几次
  基本思路是递归。对每一个先序和中序，
  从先序可以知道此时的树根，
  再利用中序中树根的位置可以知道左右子树的长度
  最后递归即可。
  中序中查找树根的位置O(1)就可完成。
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
int const SIZE = 2E6+5;
#endif
 
using llt = long long int;
using pii = pair<int, int>;
using vi = vector<int>; 

int N;
int P[SIZE], I[SIZE];
pii A[SIZE];

int PPos[SIZE], IPos[SIZE];
bool Flag = true;

int dfs(int ps, int pe, int is, int ie){
	if(!Flag) return 0;
    if(ps > pe || is > ie){
		Flag = false;
		return 0;
	}

    int rt = P[ps];
    int rtposi = IPos[rt];

    int leftn = rtposi - is;

	if(0 == leftn){
		A[rt].first = 0;
	}else{
		A[rt].first = dfs(ps+1, ps+leftn, is, rtposi-1);
	}

	if(pe-ps == leftn){
        A[rt].second = 0;
	}else{
		A[rt].second = dfs(ps+leftn+1, pe, rtposi+1, ie);
	}

    return rt;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=1;i<=N;++i) PPos[P[i] = getInt()] = i;
	for(int i=1;i<=N;++i) IPos[I[i] = getInt()] = i;
	if(P[1] != 1) {
		puts("-1");
		return 0;
	}
	
	dfs(1, N, 1, N);
	if(!Flag) {
		puts("-1");
		return 0;
	}

	for(int i=1;i<=N;++i){
		printf("%d %d\n", A[i].first, A[i].second);
	}
    return 0;
}
