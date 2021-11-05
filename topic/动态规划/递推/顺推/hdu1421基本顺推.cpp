/*
    һ��2K��������ÿ��ѡ2��
    ƣ�Ͷ�Ϊ���ƽ��
    ����Сƣ�Ͷ�
*/
#include <cstdio>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

int N,K;
int A[4000];
int D[2010][1010];//Dij��ʾǰi����Ʒ��j��

int dp(){
    //��ʼ��
    for(int i=0;i<=N;++i){
        //������������޷�ȡ�ģ���ʼ��Ϊ�����
        if ( i < K + K ) fill(D[i]+i/2+1,D[i]+K+1,2000000000);
        D[i][0] = 0;
    }

    //��ÿһ����Ʒ
    for(int i=1;i<=N;++i){
        //ÿһ��
        for(int j=1;j+j<=i&&j<=K;++j){
            int t = A[i] - A[i-1];
            t *= t;
            D[i][j] = min(D[i-1][j],D[i-2][j-1]+t);
        }
    }
    return D[N][K];
}

int main(){
    //freopen("1.txt","r",stdin);
    while( cin >> N >> K ){
        for(int i=1;i<=N;++i) cin>>A[i];
        sort(A+1,A+N+1);

        cout<< dp() << endl;
    }
    return 0;
}
