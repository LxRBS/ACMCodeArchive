/**
  �ַ�������i<j��sj=1����ij֮����һ���ߣ���sn=1
  ���ǻ�����������aii����ʾ��i����Ķ�����
  ��Ȼ��i�С���i��Ӧ�û���aii��-1����ain=ani=-1
  �annչ���ļ�һ������ʽ����D���������һ�м������������У�
  ���ǵ�һ��ȫ����Ϊ1��������ά�ֲ��䡣
  �ٿ��ǵ�i���е�ai1��aij(����j<i)��
  ��ai1Ϊ0ʱ����ʾ1��i�ޱߣ�˵��si=0�����aijҲ��0
  ��ai1Ϊ-1ʱ��˵��1��i�бߣ�˵��si=1�����aijҲ��-1
  �����������м�ȥ��һ�У��ӵڶ��п�ʼ�����Եõ�һ������������ʽ��
  ֻ��Ҫ����n-2���Խ���Ԫ��֮������
  ��������֮ǰ���Խ�Ԫ�ؼ�ÿ����Ķ�����
  Ȼ���ټ�ȥai1���ɡ�ai1�ļ������ϡ�
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 1000000007LL;

inline llt add(llt a, llt b){return (a+b)%MOD;}
inline llt mul(llt a, llt b){return a*b%MOD;}


int N;
char A[1000010];
int B[1000010] = {0};

llt proc(){
    if(1==N||2==N) return 1LL;

    B[N-2] = 1;
    for(int i=N-3;i>=0;--i)B[i] = B[i+1] + (A[i+1]=='1'?1:0);

    llt ans = 1LL;
    for(int d, i=1,n=N-1;i<n;++i){
        d = B[i];
        if('1'==A[i]) d += i + 1;
        ans = mul(ans, d);
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(2==scanf("%d%s",&N,A)){
        printf("%lld\n",proc());
    }
    return 0;
}
