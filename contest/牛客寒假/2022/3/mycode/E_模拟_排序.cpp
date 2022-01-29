/**
 * ����һ�����У�ÿ��������(����Ϊ0-9֮��)������ɫ
 * ���ڸ��ӣ������ɫ��ͬ�����Խ������򣬽�����������
 * �ٸ���K���޸�(K������10)��ÿ�ΰ�old��ɫ��Ϊnew��ɫ
 * ��ÿ���ܹ��õ���������Ƕ���
 * ��ΪK�����ֶ���һ�£�Ȼ�����򼴿�
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

int N, M, K;

struct _t{
    int val;
    int col;
}A[SIZE];

bool cmp(const _t&a, const _t&b){
    assert(a.col == b.col);
    return a.val > b.val;
}

char T[SIZE];

void proc(){
    for(int k, i=0;i<N;){
        k = 0;
        while(i+k < N && A[i].col == A[i+k].col) ++k;

        sort(A+i, A+i+k, cmp);
        if((i+=k) >= N) break;
    }

    llt ans = 0;
    for(int i=0;i<N;++i){
        ans = (ans * 10 + A[i].val) % MOD;
    }
    printf("%lld\n", ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%d%d%s", &N, &M, &K, T);
    for(int i=0;i<N;++i){
        scanf("%d", &A[i].col);
        A[i].val = T[i] - '0';
    }
    proc();
    for(int old,nn, q=1;q<=K;++q){
        scanf("%d%d", &old, &nn);
        for(int i=0;i<N;++i){
            if(A[i].col == old){
                A[i].col = nn;
            }
        }
        proc();
    }
    return 0;
}