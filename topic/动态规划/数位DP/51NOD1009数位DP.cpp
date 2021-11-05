/*
    N����1�������Ƕ��ٸ�
    ���[1,N]�����ڰ���1��1�����ж��ٸ�
    2��1�����ж��ٸ�����
    ����ۼӡ�
    ��λDP
*/
#include <string.h>
#include <iostream>
using namespace std;

typedef long long llt;

llt D[12][11][11];
int Dig[30];
int K;

llt dfs(int pos,int sum,bool limit){
    if ( -1 == pos ) return sum==K;

    if ( !limit && -1 != D[pos][sum][K] ) return D[pos][sum][K];

    llt last = limit ? Dig[pos] : 9;
    llt ans = 0;
    for(int i=0;i<=last;++i){
        ans += dfs(pos-1,sum+(1==i),limit&&i==last);
    }

    return limit ? ans : D[pos][sum][K] = ans;
}

llt proc(llt n){
    int k = 0;
    while( n ){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt ans = 0;
    for(int i=1;i<=k;++i) K=i,ans+=i*dfs(k-1,0,true);
    return ans;
}

int main(){
    memset(D,-1,sizeof(D));

    llt n;
    cin >> n;
    cout<<proc(n)<<endl;
    return 0;
}
