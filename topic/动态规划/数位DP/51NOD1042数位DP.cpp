/*
    [s,e]������0-9���ֳ��ֵĴ���
    ͳ�ƺ�1��1�����м�����2��1�����м�������
*/
#include <string.h>
#include <iostream>
using namespace std;

typedef long long llt;

//dijkw��i��ʾ��λ��j��ʾ���֣�k��ʾ���е�������w��ʾĿ������
llt D[20][10][20][20];
int Dig[30];
int K,Digit;

llt dfs(int pos,int cnt,bool lead,bool limit){
    if ( -1 == pos ) return cnt==K;

    if ( !lead && !limit && -1 != D[pos][Digit][cnt][K] ) return D[pos][Digit][cnt][K];

    llt last = limit ? Dig[pos] : 9;
    llt ans = 0;
    for(int i=0;i<=last;++i){
        if ( lead && 0==i ) ans += dfs(pos-1,0,true,limit&&i==last);
        else ans += dfs(pos-1,cnt+(Digit==i),false,limit&&i==last);
    }

    return lead || limit ? ans : D[pos][Digit][cnt][K] = ans;
}

llt proc(llt n){
    int k = 0;
    while( n ){
        Dig[k++] = n % 10;
        n /= 10;
    }
    llt ans = 0;
    for(int i=1;i<=k;++i) K=i,ans+=i*dfs(k-1,0,true,true);
    return ans;
}

int main(){
    memset(D,-1,sizeof(D));

    llt a,b;
    cin >> a >> b;
    for(Digit=0;Digit<10;++Digit){
        cout<<proc(b)-proc(a-1)<<endl;
    }
    return 0;
}
