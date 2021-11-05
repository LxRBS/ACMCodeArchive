/*
    ╫соз╠Щ
*/
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE = 100100;
int B[SIZE][11];
int N,M;
bool read(){
    N = getUnsigned();
    if ( 0 == N ) return false;

    memset(B,0,sizeof(B));
    int x,t;
    M = 0;
    for(int i=0;i<N;++i){
        x = getUnsigned();
        t = getUnsigned();
        if ( M < t ) M = t;
        ++B[t][x];
    }
    return true;
}
int D[SIZE][11];
inline bool isValid(int t,int x){
    return 0 <= x && x < 11 && D[t][x] != -1;
}
void dp(){
    memset(D,-1,sizeof(D));
    D[0][5] = 0;
    for(int t=1;t<=M;++t)for(int x=0;x<11;++x){
        if ( isValid(t-1,x-1) ) D[t][x] = max(D[t][x],D[t-1][x-1]);
        if ( isValid(t-1,x) ) D[t][x] = max(D[t][x],D[t-1][x]);
        if ( isValid(t-1,x+1) ) D[t][x] = max(D[t][x],D[t-1][x+1]);
        if ( D[t][x] != -1 ) D[t][x] += B[t][x];
    }
}

int main(){
    while( read() ){
        dp();
        printf("%d\n",*max_element(D[M],D[M]+11));
    }
    return 0;
}

