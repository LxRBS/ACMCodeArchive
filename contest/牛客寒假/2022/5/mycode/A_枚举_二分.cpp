/**
 * ��һ��01�����������ѡ��3��λ�ã�Ҫ��
 * 1 ��ѡλ�ñ���Ϊ0
 * 2 ��ѡλ�ò����غ�
 * 3 ��������λ�ò�Ϊp������÷�Ϊw-|k-p|*q, w,k,qΪ��֪��
 * ���ܹ��õ���������
 * ֻ��ö���м�һ��λ�ü��ɣ�Ȼ��ǰ���ѡһ����������λ��
 * ��������λ����Ȼ�ǲ����ӽ�k�ģ����ּ���
 * Ҳ���Գ�ȡ��
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 1000000+7;
#endif

typedef long long llt;

int N;
llt K, W, Q;
char A[SIZE];
vector<int> Pos;

template<typename T> T ABS(T a){return a>=0?a:-a;}

inline llt f(int p1, int p2){
    if(p1 == p2) return 0;
    return W - ABS(K - ABS(p1-p2)) * Q;
}    

llt proc(){
    for(int i=0;i<N;++i)if('0' == A[i]) Pos.push_back(i);

    llt ans = 0;
    for(int i=1,n=Pos.size();i<n-1;++i){
        int pos = Pos[i] - K;
        if(pos < Pos[0]) pos = Pos[0];
        llt lans = 0;
        auto it = lower_bound(Pos.begin(), Pos.begin()+i, pos);
        lans = max(lans, f(Pos[i], *it));
        if(it!=Pos.begin()) lans = max(lans, f(Pos[i], *(it-1)));

        pos = Pos[i] + K;
        if(pos > Pos.back()) pos = Pos.back();
        llt rans = 0;
        it = lower_bound(Pos.begin()+i+1, Pos.end(), pos);
        rans = max(rans, f(Pos[i], *(it-1)));
        if(it != Pos.end()) rans = max(rans, f(Pos[i], *it));

        ans = max(ans, lans+rans);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%s%lld%lld%lld", &N, A, &K, &W, &Q);
    printf("%lld\n", proc());
    return 0;
}