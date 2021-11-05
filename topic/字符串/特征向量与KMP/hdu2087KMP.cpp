//��׼��KMP����
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


//��src������������nΪsrc�ĳ���
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

//��P��T�г��ֵĴ������������ص�
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
