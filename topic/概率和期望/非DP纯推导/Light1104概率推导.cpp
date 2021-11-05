/*
    ����1�����������������Ҫ�����ˣ�����ʹ������������ͬ���յĸ��ʲ�����0.5
    ��������ΪN��M���ˣ������ղ�ͬ�ĸ���Ϊ
    N * (N-1) * ... * (N-M+1) / N^M
    ��
    (N-1)/N * (N-2)/N * ... (N-M+1)/N < 0.5

    �������Nȡ1��2ʱ���ƺ��е�����
*/

#include <stdio.h>
#include <vector>
#include <numeric>
using namespace std;

int f(int n){
    double x = 1.0, dn = (double)n;
    for(int m=0;;++m){
        x *= (double)( n - m ) / dn;
        if ( x <= 0.5 ) return m;
    }
}

int main(){
    int n,nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&n);
        printf("Case %d: %d\n",kase,f(n));
    }
    return 0;
}

