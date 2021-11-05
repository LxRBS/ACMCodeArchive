#include <iostream>
#include <algorithm>
using namespace std;
int P[101] = {0};

//Dp[i][j]表示经过i跳，跳到j位置上的最大值
//Dp[i][j] = MAX(Dp[i-1][j-A~j-B])
int Dp[101][102];
int main(){
    int nofkase;
    cin >> nofkase;
    while(nofkase--){
        int n,a,b,k;
        cin >> n >> a >> b >> k;
        for(int i=0;i<n;++i)cin>>P[i];
        for(int i=0;i<n;++i)fill(Dp[i],Dp[i]+102,0);
        Dp[0][0] = P[0];
        int ans = 0;

        //i表示第i跳
        for(int i=1;i<=k;++i){
            //pos代表第i跳能够跳到的位置
            for(int pos=i*a;pos<=i*b;++pos){
                if ( pos >= n ) break;

                Dp[i][pos] = 0;
                //第i跳到pos位置的可能性
                for(int z=a;z<=b;++z){
                    if ( pos - z < 0 || 0 == Dp[i-1][pos-z] ) continue;

                    int t = Dp[i-1][pos-z] + P[pos];
                    if ( t > Dp[i][pos] ) Dp[i][pos] = t;
                }
                if ( ans < Dp[i][pos] )
                    ans = Dp[i][pos];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
