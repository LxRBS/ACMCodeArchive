/*
    N����ͬ���ȵĵ��£�һ���гɵȳ��ȵ�K��
    Ҫ����������
    �������С��0.01�������0.00
*/
#include <stdio.h>
typedef long long llt;

int N,K;
llt Total;
llt A[10010];
bool read(){
    if ( EOF == scanf("%d%d",&N,&K) ) return false;
    int a,b;
    Total = 0;
    for(int i=0;i<N;++i){
        scanf("%d.%d",&a,&b);
        A[i] = a * 100LL + b;
        Total += A[i];
    }
    return true;
}

//���N�������Ƿ��ֳܷ�K�ݣ�ÿ�ݳ�Ϊm
bool check(int m){
    if ( 0 == m ) return true;

    int ans = 0;
    for(int i=0;i<N&&ans<K;++i){
        ans+=A[i]/m;
    }
    return ans >= K;
}

llt proc(){
    //��������0��������Total/K
    llt mid, left = 0, right = Total / K;
    
    //���н��С��������ȡ����
    //���ж�����Ϊ��������Ϊright
    do{
        mid = ( left + right ) >> 1;
        if ( check(mid) ) left = mid + 1;
        else right = mid - 1;
    }while( left <= right );
    return right>=1?right:0;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%.2f\n",proc()/100.0);
    return 0;
}
