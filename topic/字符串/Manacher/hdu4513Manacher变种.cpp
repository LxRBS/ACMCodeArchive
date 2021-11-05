/*
    求最长回文子串
    其左到中要升序
    对Manacher要有一定了解，光套模板不行
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int const SIZE = 2000010;

//Manacher算法
//src是源字符串，tmp是临时字符串，r是半径数组，n是源字符串的长度
//tmp和r长度至少是2n
//start为最长回文开始的地方
//返回值为源中的最长回文子串的长度
int Manacher(int const src[],int t[],int r[],int const n,int&start){
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

        //半径至少是1
        r[x+k] = k == r[x] ? 1 : r[x-k];
        //将下标移到x+k
        x += k;
        //原始方法求半径
        while( t[x+r[x]] == t[x-r[x]] && t[x-r[x]] <= t[x-r[x]+2] ) ++r[x];
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

int N;
int A[SIZE],Tmp[SIZE],R[SIZE];

void read(){
    scanf("%d",&N);
    for(int i=0;i<N;++i) scanf("%d",A+i);
}
int main(){
    int start,nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%d\n",Manacher(A,Tmp,R,N,start));
    }
    return 0;
}
