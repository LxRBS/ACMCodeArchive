//标准的KMP搜索
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


//求src的特征向量，n为src的长度
void getKMPNext(char const src[],int n,int next[]){
    next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
        while( k >= 0 && src[i] != src[k] ) k = next[k];
        ++i, ++k;
        if ( i == n ) return;
        next[i] = src[i] == src[k] ? next[k] : k;
    }
}

//求P在T中出现的次数，不可以重迭
int KMPCount(char const T[],int tn,char const P[],int pn,int const next[]){
    if ( pn > tn ) return 0;
    int tp = 0, pp = 0, ret = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ){
            ++ret;
            pp = 0;
        }
    }
    return ret;
}


int N,M;
int Next[10010];
char T[10010],P[10010];

int main(){
    //freopen("1.txt","r",stdin);
    while( scanf("%s",T) ){
        if ( '#' == *T && '\0' == T[1] ) return 0;

        scanf("%s",P);
        int pn = strlen(P), tn = strlen(T);
        getKMPNext(P,pn,Next);
        int r = KMPCount(T,tn,P,pn,Next);
        printf("%d\n",r);
    }
    return 0;
}
