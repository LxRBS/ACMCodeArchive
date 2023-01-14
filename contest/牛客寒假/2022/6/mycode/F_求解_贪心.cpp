/**
 * 给定一个只含加减的字符串，可以修改K次
 * 每次修改将某个位置的加减互换，同一个位置可以修改多次
 * 修改完毕后，遍历字符串，要求加减号数量的差的绝对值最小
 * 贪心即可
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 100100;
#endif

char A[SIZE];
int K;

int proc(){
    int n = strlen(A);
    int acnt = 0, bcnt = 0;
    for(char const *p=A;*p;++p){
        if('+'==*p) ++acnt;
        else if('-'==*p) ++bcnt;
        else throw runtime_error("XX");
    }
    if(acnt == bcnt) {
        return (K&1) ? 2 : 0;
    }
    if(acnt < bcnt) swap(acnt, bcnt);
    int cha = acnt - bcnt;
    if(cha >= K + K) return cha - K - K;
    if(cha&1) return 1;
    int left = K - cha / 2;
    return (left & 1) ? 2 : 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%s%d", A, &K);
        printf("%d\n", proc());
    }
    return 0;
}