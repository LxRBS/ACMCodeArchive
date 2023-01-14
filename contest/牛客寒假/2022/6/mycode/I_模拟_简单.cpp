/**
 * 模拟K进制加法 
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 200100;
#endif

char A[SIZE], B[SIZE], C[SIZE] = {0};
int K;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d%s%s", &K, A, B);
    int na = strlen(A), nb = strlen(B);
    int nc = SIZE - 1;
    int a = na - 1, b = nb - 1;
    int carry = 0;
    while(a>=0&&b>=0){
        int tmp = (A[a--] - '0') + (B[b--] - '0') + carry;
        C[--nc] = tmp % K + '0';
        carry = tmp / K;  
    }
    while(a >= 0){
        int tmp = (A[a--] - '0') + carry;
        C[--nc] = tmp % K + '0';
        carry = tmp / K;  
    }
    while(b >= 0){
        int tmp = (B[b--] - '0') + carry;
        C[--nc] = tmp % K + '0';
        carry = tmp / K; 
    }
    if(carry) C[--nc] = carry + '0';
    puts(C+nc);
    return 0;
}