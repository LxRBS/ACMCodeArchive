/**
 * 01背包，求刚好装满时最大异或和是多少，1024个物品，最大体积1024，异或和最大值也在1024
 * 不能用经典背包，因为无法保证最大值是由子问题的最大值与新物品异或出来的
 * 设Dijk为到物品i，异或为j，用掉的体积为k，为1表示有此方案，为0表示没有
 * 则 Dijk = D[i-1][j^Wi][k-Vi]
 * 空间可以滚动，但是时间要超时，考虑使用bitset
 * 对于每一个Dj(注意Dj是一个01向量)，相当于将D[j^wi]左移Vi位
 * 最终时间复杂度是O(N^3/32)
 * 考虑到j无法确定计算次序，因此实际上使用一个二行的向量来进行滚动
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
    int sgn = 1;
    char ch = __hv007();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
    if ( '-' == ch ) {sgn = 0;ch=__hv007();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 1090;
#else
int const SIZE = 1090;
#endif  

using bt = bitset<SIZE>;

bt D[SIZE], T[SIZE];

int N, M;
int V[SIZE], W[SIZE];

int proc(){
    for(int i=0;i<1024;++i) D[i].reset();
    
    D[0][0] = 1;
    for(int i=0;i<N;++i){
        /// 根据D计算T
        for(int j=0;j<1024;++j){
            T[j] = D[j] << V[i]; 
        }
        /// 更新D
        for(int j=0;j<1024;++j){
            D[j] |= T[j^W[i]];
        }
    }
    int ans = -1;
    for(int i=1023;i>=0;--i){
        if(D[i].test(M)){
            ans = i;
            break;
        }
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        for(int i=0;i<N;++i){
            V[i] = getInt();
            W[i] = getInt();
        }
        cout << proc() << endl;
    }
    return 0;
}