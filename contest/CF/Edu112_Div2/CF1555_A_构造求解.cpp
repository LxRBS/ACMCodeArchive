/**
 * С����6��15���ӣ��еȵ�8��20���ӣ����10��25����
 * ������N���ˣ�Ҫ��ÿ����1��������������Ҫ���ٷ���
 * �������۴�С��ÿ��������ʱ����һ���ġ����ֻ���ҵ�
 * ��С��6x+8y+10z�Ҵ��ڵ���N���ɡ�
 * ���켴�ɣ��������N����������N��1��Ϊż��
 * ������ο���0/2/4/6/8�����
 * �������N��x8����ֻ��x����������1������������
 * ���N��x6����ֻ��x����������1��С��������
 * ������������
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt N;

llt proc(){
    if(N&1) ++N;
    llt t = N % 10;
    llt q = N / 10;
    if(0 == t){
        return q * 25;
    }
    if(2 == t){
        return q>=1 ? (q-1) * 25 + 30 : 15;
    }
    if(4 == t){
        return q >= 1 ? (q-1) * 25 + 35 : 15;
    }
    if(6 == t){
        return q >= 1 ? (q-1) * 25 + 40 : 15;
    }
    return q * 25 + 20;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%lld", &N);
        printf("%lld\n", proc());
    }
    return 0;
}