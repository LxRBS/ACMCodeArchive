/**
 * N�����֣���ʼ��Ϊ0���ӳ�ʼʱ��ÿ���1����9���ֱ�Ϊ0����˷�����
 * ��ѡ��һ��λ�ý���ֹͣ������Ȼ����һ��������λ��Ҳ��ֹͣ����������һ�����ڵ�����ֹͣ���������
 * ���ܹ��õ����������Ƕ���
 * ֹͣ�θ�λ�ܹ��õ����������
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