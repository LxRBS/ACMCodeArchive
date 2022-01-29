/**
 * һ���ַ���������Ϊ������Ҫ��������������
 * 1 ������[L, R]֮��
 * 2 ��д��ĸ��Сд��ĸ�����顢������������
 * ����һ���ַ��������ж��ٸ��Ӵ�������Ϊ����
 * ע�⵽����[s...e]�����룬��[s...e...]�϶�Ҳ������
 * ����s������ĸ�����ǲ����ģ���˿���ö������������
 * ʵ���ϣ�����Ҫ���֣���ȡ���ɡ���Ϊ����e��s��������ԣ�
 * ��s+1���������һ����e�����ұߡ�
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