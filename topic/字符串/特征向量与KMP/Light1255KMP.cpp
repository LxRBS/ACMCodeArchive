//����T��P����P��T�г��ֵĴ����������ص�
#include <cstring>
#include <cstdio>

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

//��P��T�г��ֵĴ����������ص���next�ĳ���Ҫ����pn+1
int KMPCount(char const T[],int tn,char const P[],int pn,int const next[]){
    if ( pn > tn ) return 0;
    int tp = 0, pp = 0, ret = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ){
            ++ret;
            pp = next[pn];
        }
    }
    return ret;
}

int const SIZE = 1000010;
char P[SIZE],T[SIZE];
int Next[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%s%s",T,P);
        int pn = strlen(P), tn = strlen(T);
        getKMPNext(P,pn+1,Next);
        printf("Case %d: %d\n",kase,KMPCount(T,tn,P,pn,Next));
    }
    return 0;
}
