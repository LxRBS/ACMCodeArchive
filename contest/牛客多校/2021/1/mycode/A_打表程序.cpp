#include <bits/stdc++.h>
#define ll long long
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


int const SIZE = 101;
int SG[SIZE][SIZE] = {0};
int N = SIZE - 1;

int dfs(int r, int c){
    if(r>c) swap(r, c);
    if(-1!=SG[r][c]) return SG[r][c];

    int ans = 0;
    for(int i=r;i>=1;--i){
        for(int k=0;k*i<=c;++k){
            int tmp = dfs(r-i, c-k*i);
            if(0==tmp) return SG[r][c] = 1;
        }
    }
    for(int i=c;i>=1;--i){
        for(int k=0;k*i<=r;++k){
            int tmp = dfs(c-i,r-k*i);
            if(0==tmp) return SG[r][c] = 1;
        }
    }
    return SG[r][c] = 0;
}

vector<pair<int, int> > Ans;

int main(){
    //freopen("1.txt","r",stdin);
    freopen("1.txt","w",stdout);

    memset(SG, -1, sizeof(SG));
    for(int i=1;i<=N;++i)SG[0][i] = SG[1][i] = SG[i][i] = 1;

    for(int i=1;i<=N;++i){
        for(int j=1;j<=i;++j){
            if(0==dfs(j, i)){
                Ans.push_back(make_pair(j, i));
            }
        }
    }
    printf("int const G[][2] = {");
    for(auto pp: Ans){
        printf(",{%d,%d}", pp.first, pp.second);
    }
    printf("};\n");
    return 0;
}
