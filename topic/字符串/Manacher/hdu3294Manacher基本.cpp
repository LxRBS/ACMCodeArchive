/*
    将字符串做一个字母到字母的映射
    然后求最长回文子串 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//Manacher算法
//src是源字符串，tmp是临时字符串，r是半径数组，n是源字符串的长度
//tmp和r长度至少是2n
//start为最长回文开始的地方
//返回值为源中的最长回文子串的长度
int Manacher(char const src[],char t[],int r[],int const n,int&start){
    //预处理，s中加入特殊字符，头前加入不一样的字符确保判断不会越界
    t[0] = -1;
    t[1] = -2;
    int total = 2;
    for(int i=0;i<n;++i) t[total++] = src[i], t[total++] = -2;
    t[total] = 0;//结尾

    //初始化
    r[0] = r[1] = 1;

    //x用来记录已求出的r的下标界限
    int x = 1,k;
    while( x < total ){
        for(k=1;k<r[x];++k){
            if ( k + r[x-k] == r[x] ) break;
            r[x+k] = min(r[x-k],r[x]-k);
        }

        //半径至少是1或者r[x-k]
        r[x+k] = k == r[x] ? 1 : r[x-k];
        //将下标移到x+k
        x += k;
        //原始方法求半径
        while( t[x+r[x]] == t[x-r[x]] ) ++r[x];
    }

    //求最长回文的长度以及开始位置
    int ret = 0;
    start = 0;
    for(int i=0;i<total;++i){
        int tt = r[i] - 1;
        if ( ret < tt ) ret = tt, start = ( i - ret ) >> 1;
    }
    return ret;
}

char Dic[128];
void f(char ch){
    for(int i=0;i<26;++i){
        int idx = i + ch;
        if ( idx > 'z' ) idx = idx - 'z' - 1 + 'a';
        Dic[idx] = 'a' + i;
    }
}
int const SIZE = 200010;
int N;
char C[3];
char A[SIZE],T[SIZE<<1];
int R[SIZE<<1];
int main(){
    while( EOF != scanf("%s%s",C,A) ){
        f(*C);
        N = strlen(A);

        int start;
        int n = Manacher(A,T,R,N,start);

        if ( 1 == n ){
            printf("No solution!\n");
        }else{
            printf("%d %d\n",start,n+=start-1);
            for(int i=start;i<=n;++i) putchar(Dic[(int)A[i]]);
            printf("\n");
        }
    }
    return 0;
}
