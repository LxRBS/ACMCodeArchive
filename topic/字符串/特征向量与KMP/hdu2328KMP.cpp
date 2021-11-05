//求多个字符串的最长、最小字典序公共子串
//共有4000个串，不方便使用后缀数组
//使用KMP，配合暴力
#include <cstdio>
#include <cstring>

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

//在T中搜索P，返回第一个找到的位置，均从0开始，找不到返回-1
int KMPSearch(char const T[],int tn,char const P[],int pn,int const next[]){
    if ( pn > tn ) return -1;
    int tp = 0, pp = 0;
    while( tp < tn ){
        if ( -1 == pp || T[tp] == P[pp] ) ++tp, ++pp;
        else pp = next[pp];
        if ( pp == pn ) return tp - pn;
    }
    return -1;
}

char A[4000][210];
int L[4000];
int N;
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    for(int i=0;i<N;++i){
        scanf("%s",A[i]);
        L[i] = strlen(A[i]);
    }
    return true;
}

int Next[300];

//比较A[0]子串的大小
bool cmp(int lhs,int rhs,int length){
    for(int i=0;i<length;++i){
        if ( A[0][lhs+i] < A[0][rhs+i] ) return true;
        if ( A[0][lhs+i] > A[0][rhs+i] ) return false;
    }
    return false;
}

//检测是否具有从start开头、长度为length的公共子串
bool check(int start,int length){
    char ch = A[0][start+length];
    A[0][start+length] = '\0';
    getKMPNext(A[0]+start,length,Next);

    for(int i=1;i<N;++i)if( -1 == KMPSearch(A[i],L[i],A[0]+start,length,Next) ){
        A[0][start+length] = ch;
        return false;
    }
    A[0][start+length] = ch;
    return true;
}

//检测是否具有长度为length的公共子串
//如存在，返回开头，返回-1表示无
int check(int length){
    int ret = -1;
    for(int i=0;i<L[0]-length+1;++i){
        if ( check(i,length) ){
            if ( -1 == ret || cmp(i,ret,length) ) ret = i;
        }
    }
    return ret;
}

struct _t{
    int len,start;
}Ans;

void proc(){
    Ans.len = 0;

    //二分法
    int left = 1;
    int right = L[0];
    int start;
    do{
        int mid = ( left + right ) >> 1;
        if ( ( start = check(mid) ) != -1 ){
            if ( Ans.len < mid ) Ans.len = mid, Ans.start = start;
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }while( left <= right );
}

int main(){
    while ( read() ){
        proc();

        if ( 0 == Ans.len ){
            printf("IDENTITY LOST\n");
        }else{
            A[0][Ans.start+Ans.len] = '\0';
            printf("%s\n",A[0]+Ans.start);
        }
    }
    return 0;
}
