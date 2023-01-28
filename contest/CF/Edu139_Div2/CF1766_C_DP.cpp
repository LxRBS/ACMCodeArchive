/**
 * 2行乘N列的格子，BW两色，对每一列，至少有一个B。
 * 问从第一列开始，能否一笔画完所有的B，注意每一个B只能画到一次，不能经过W。
 * 首先检查一下所有的B是否连通,这一步其实可以不用
 * 设D1i与D2i，为1表示可以由前一列合法的到达，为表示不能由前一列到达
 * 当A[c][i] = 'B时，D[c][i] = D[c][i-1]
 * 否则 D[c][i] = 0
 * 查看D[1][N]和D2[N]即可。
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

struct _t{

int n;
vi father;

void init(int nn){
	father.assign((n=nn), 0);
	for(int i=0;i<n;++i) father[i] = i;
}

int find(int x){
	return x == father[x] ? x : father[x] = find(father[x]);
}

void unite(int x, int y){
	father[find(y)] = find(x);
}

}UF;

int N;
char S[2][SIZE];

void proc(int sn, int index){
	int pos = sn * N + index;
	if(index > 0){
		if(S[sn][index-1] == 'B'){
			UF.unite(pos, pos-1);
		}
	}
	if(index + 1 < N){
		if(S[sn][index+1] == 'B'){
			UF.unite(pos, pos+1);
		}
	}
    if(S[sn^1][index] == 'B'){
		UF.unite(pos, (sn^1)*N+index);
	}
}

vvi D;

bool proc(){
	int n = N + N;
	UF.init(n);

	for(int i=0;i<N;++i){
		if(S[0][i] == 'B'){
            proc(0, i);
		}
		if(S[1][i] == 'B'){
            proc(1, i);
		}
	}

	int pos = 0;
	if(S[0][0] != 'B') pos = N;

	for(int i=0;i<N;++i){
		if(S[0][i] == 'B'){
			if(UF.find(pos) != UF.find(i)) return false;
		}
		if(S[1][i] == 'B'){
			if(UF.find(pos) != UF.find(i+N)) return false;
		}
	}

    D.assign(2, vi(N, 0));
	if(S[0][0] == 'B') D[0][0] = 1;
	if(S[1][0] == 'B') D[1][0] = 1;
	for(int i=1;i<N;++i){
		if(S[0][i] == 'B'){
			if(S[1][i] == 'B'){
                D[0][i] = D[1][i-1];
				D[1][i] = D[0][i-1];
			}else{
                D[0][i] = D[0][i-1];
				D[1][i] = 0;
			}
		}else{
			if(S[1][i] == 'B'){
                D[1][i] = D[1][i-1];
				D[0][i] = 0;
			}else{
                D[0][i] = D[1][i] = 0;
			}			
		}
	}
	return D[0][N-1] || D[1][N-1];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif

    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
	    scanf("%d%s%s", &N, S[0], S[1]);
		puts(proc()?"YES":"NO");
	}

    return 0;
}