/**
 * N个数字，初始均为0。从初始时刻每秒加1，到9后又变为0，如此反复。
 * 现选择一个位置将其停止增长，然后下一秒其相邻位置也会停止增长，在下一秒相邻的相邻停止，如此类推
 * 问能够得到最大的数字是多少
 * 停止次高位能够得到的数字最大。
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE = 200010;
#endif

typedef int llt;

int N;
char A[SIZE];

char* proc(){
    if(1 == N){
        A[0] = '9', A[1] = '\0';
        return A;
    }
    if(2 == N){
        A[0] = '9', A[1] = '8', A[2] = '\0';
        return A;
    }
    if(3 == N){
        A[0] = '9', A[1] = '8', A[2] = '9', A[3] = '\0';
        return A;
    }

    A[0] = '9', A[1] = '8', A[2] = '9';
    for(int i=3;i<N;i+=10){
        A[i+0] = '0';
        A[i+1] = '1';
        A[i+2] = '2';
        A[i+3] = '3';
        A[i+4] = '4';
        A[i+5] = '5';
        A[i+6] = '6';
        A[i+7] = '7';
        A[i+8] = '8';
        A[i+9] = '9';
    }
    int left = (N - 3) % 10;
    for(int i=0;i<left;++i){
        A[N-left+i] = i + '0';
    }
    A[N] = '\0';    
    return A;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &N);
        puts(proc());
    }
    return 0;
}