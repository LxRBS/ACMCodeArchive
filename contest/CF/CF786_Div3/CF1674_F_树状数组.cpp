/**
 * N*M的平面，点表示空地，*表示有东西
 * 一个摆布认为是好的，如果*集中在前若干列
 * 每一步可以将一个*移动到任意空位上
 * 给定q个询问，每次询问之前会增加或者减少一个*号
 * 然后问为了将现有局面变成好的，最少要移动几次
 * 假设此时一共有Total个星号，则形成好的局面，需要将Total/N列放满，
 * 需要Total/N*N个星号，然后求出此时的列和，相差的数量就需要用操作去填补
 * 再对于最后一列，for一下即可。
 * 列和处在变化的情况，因此使用树状数组。
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
int const SIZE = 1e3+5;
#endif
 
using llt = long long;
using Real = long double;
 
Real const EPS = 1E-12;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}

struct bit_t{

int n, c[SIZE];
int lowbit(int x){return x&-x;}
void init(int nn){n=nn;fill(c, c+n+1, 0);}
void modify(int pos, int d){
    while(pos<=n) c[pos] += d, pos += lowbit(pos);
}
int query(int pos){
    int ans = 0;
    while(pos) ans += c[pos], pos -= lowbit(pos);
    return ans;
}

}Bt;

int N, M, Q;
char A[SIZE][SIZE];



int Total = 0;
int Col[SIZE] = {0};


int proc(int r, int c){
    if('*' == A[r][c]){
        --Total; --Col[c];
        Bt.modify(c, -1); 
        A[r][c] = '.';
    }else{
        ++Total; ++ Col[c];
        Bt.modify(c, 1);
        A[r][c] = '*';
    }

    int t = Total / N;
    int left = Total % N;
    int ans = t * N - Bt.query(t);
    for(int i=1;i<=left;++i){
        if('.' == A[i][t+1]) ++ans;
    }
    return ans;
}

 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%d", &N, &M, &Q);
    for(int i=1;i<=N;++i){
        scanf("%s", A[i]+1);
        for(int j=1;j<=M;++j)if('*'==A[i][j])++Total,++Col[j];
    }

    Bt.init(M);
    for(int i=1;i<=M;++i) Bt.modify(i, Col[i]);
    
    for(int r,c,q=1;q<=Q;++q){
        scanf("%d%d", &r, &c);
        printf("%d\n", proc(r, c));
    }
    return 0;
}