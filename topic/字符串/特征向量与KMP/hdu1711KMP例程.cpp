//标准的KMP搜索
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = -1;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret * sgn;
}

//求src的特征向量，n为src的长度
void getKMPNext(int const src[],int n,int next[]){
    next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
        while( k >= 0 && src[i] != src[k] ) k = next[k];
        ++i, ++k;
        if ( i == n ) return;
        next[i] = src[i] == src[k] ? next[k] : k;
    }
}

//在T中搜索P，返回第一个找到的位置，均从0开始，找不到返回-1
int KMPSearch(int const T[],int tn,int const P[],int pn,int const next[]){
    if ( pn > tn ) return -1;
    int tp = 0, pp = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ) return tp - pn;
    }
    return -1;
}

int N,M;
int T[10000010],P[10010],Next[10010];
void read(){
    N = getInt(), M = getInt();
    for(int i=0;i<N;++i) T[i] = getInt();
    for(int i=0;i<M;++i) P[i] = getInt();
}

int main(){
    int nofkase = getInt();
    while( nofkase-- ){
        read();
        getKMPNext(P,M,Next);
        int r = KMPSearch(T,N,P,M,Next);
        printf("%d\n",-1==r?-1:r+1);
    }
    return 0;
}
