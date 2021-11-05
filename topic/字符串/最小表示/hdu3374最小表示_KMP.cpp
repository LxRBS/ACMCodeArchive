//最小表示和最大表示出现的位置以及出现的次数
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//求src的用于KMP匹配的特征向量，n为src的长度
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


//求P在T中出现的次数，可以重迭，next的长度要求是pn+1
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

//返回最小表示在s中的序号，s是已经重复二次的字符串
//n为未重复之前的长度
int miniPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//此处可返回i、j任意一个
    	if ( s[i+k] > s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//此处要返回小的
    	if ( i == j ) ++j;//强制j后移一位
    	k = 0;
    }
    return -1;//这里不会到达
}

//返回最大表示在s中的序号，s是已经重复二次的字符串
//n为未重复之前的长度
int maxiPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//此处可返回i、j任意一个
    	if ( s[i+k] < s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//此处要返回小的
    	if ( i == j ) ++j;//强制j后移一位
    	k = 0;
    }
    return -1;//这里不会到达
}

char A[SIZE<<1],B[SIZE];
int Next[SIZE];

int main(){
    while( EOF != scanf("%s",A) ){
        int n = strlen(A);
        copy(A,A+n,A+n);
        A[n+n] = '\0';

        //求最小表示
        int mins = miniPre(A,n);
        //拷贝最小表示
        copy(A+mins,A+mins+n,B);
        B[n] = '\0';
        //搜索最小表示出现的次数，注意A的长度取2n-1
        getKMPNext(B,n+1,Next);
        int minc = KMPCount(A,n+n-1,B,n,Next);

        //求最大表示
        int maxs = maxiPre(A,n);
        //拷贝最大表示
        copy(A+maxs,A+maxs+n,B);
        B[n] = '\0';
        //搜索最大表示出现的次数，注意A的长度取2n-1
        getKMPNext(B,n+1,Next);
        int maxc = KMPCount(A,n+n-1,B,n,Next);

        printf("%d %d %d %d\n",mins+1,minc,maxs+1,maxc);
    }
    return 0;
}

