#include <cstdio>
#include <algorithm>
using namespace std;

int N;
double P[22];
double NP;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    NP = 0.0;
    for(int i=0;i<N;++i) scanf("%lf",P+i), NP += P[i];
    return true;
}

double D[1<<20];//Di��ʾ״̬i�����յ��������D[(1<<N)-1] = 0
/*
Di = SIGMA{PjDj} + SIGMA{PkDi} + 1
Pk�ǲ��ı���״����Щ���ʣ�Pj�Ƕ���һ���Ƶĸ���
*/
double dp(int status){
    if ( D[status] != -1.0 ) return D[status];
    double ret = 0.0;
    double p = NP;
    for(int i=0;i<N;++i){
        if ( 0 == (status & (1<<i)) ) ret += P[i] * dp(status|(1<<i));
        else p -= P[i];
    }
    return D[status] = ( ret + 1.0 ) / p;
}

int main(){
    while( read() ){
        fill(D,D+(1<<N),-1.0);
        D[(1<<N)-1] = 0.0;
        printf("%.4f\n",dp(0));
    }
    return 0;
}
