/**
 * 一个字符串可以作为密码需要满足如下条件：
 * 1 长度在[L, R]之间
 * 2 大写字母、小写字母、数组、符号至少三种
 * 给定一个字符串，问有多少个子串可以作为密码
 * 注意到假设[s...e]是密码，则[s...e...]肯定也是密码
 * 而从s往后，字母数量是不减的，因此可以枚举起点二分搜索
 * 实际上，不需要二分，尺取即可。因为假设e是s的最左配对，
 * 则s+1的最左配对一定在e及其右边。
*/
#include<bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 100010;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

inline int f(char ch){
    if('A'<=ch&&ch<='Z') return 0;
    if('a'<=ch&&ch<='z') return 1;
    if('0'<=ch&&ch<='9') return 2;
    return 3;
}

int N, L, R;
char A[SIZE];
int C[4][SIZE] = {0};

int check(int start, int mid){
    int t = 0;
    if(C[0][mid] > C[0][start-1]) ++t;
    if(C[1][mid] > C[1][start-1]) ++t;
    if(C[2][mid] > C[2][start-1]) ++t;
    if(C[3][mid] > C[3][start-1]) ++t;
    return t >= 3;
}

llt proc(int idx){
    int left = idx, right = N, mid;
    do{
        mid = (left + right) >> 1;
        if(check(idx, mid)) right = mid - 1;
        else left = mid + 1;
    }while(left <= right);
    
    int s = right + 1;
    if(s - idx + 1 < L) s = idx + L - 1;
    if(s > N) return 0;
    
    int e = idx + R - 1;
    if(e > N) e = N;
    if(e < s) return 0;
    
    return e - s + 1;
}

llt proc(){   
    for(int i=1;i<=N;++i){
        C[0][i] = C[0][i-1];
        C[1][i] = C[1][i-1];
        C[2][i] = C[2][i-1];
        C[3][i] = C[3][i-1];
        ++C[f(A[i])][i]; 
    }     

    llt ans = 0;
    for(int i=1;i<=N-L+1;++i){
        ans += proc(i);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%d%s", &N, &L, &R, A+1);
    printf("%lld\n", proc());
    return 0;
}