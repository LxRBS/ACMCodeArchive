#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1005;
typedef long long LL;
const LL MOD = 1e9 + 7;

int n,s;
LL dp[2][N][3][3];
LL ans = 0;
int a[N];

void init()
{
    scanf("%d %d",&n,&s);
    for(int i = 1;i <= n;i++)
      scanf("%d",&a[i]);
}

void update(LL &_x,LL _y)
{
    _x = _x + _y;
    _x = _x > MOD ? _x - MOD : _x;
}

void work()
{
    memset(dp, 0, sizeof(dp));

    dp[0][0][0][0] = 1;
    bool sign = false;

    for(int i = 1;i <= n;i++)
    {
        sign = !sign;
        for(int j = s;j >= 0;j--)
        {
            for(int s1 = 0;s1 < 3;s1++)
              for(int s2 = 0;s2 < 3;s2++)
              {
                  dp[sign][j][s1][s2] = dp[!sign][j][s1][s2] ;
                  if(j >= a[i]) update(dp[sign][j][s1][s2] , dp[!sign][j - a[i]][s1][s2]);

                  if(s1 > 0 && j >= a[i])
                  {
                      update(dp[sign][j][s1][s2] , dp[!sign][j - a[i]][s1 - 1][s2]);
                  }
                  if(s2 > 0)
                  {
                      update(dp[sign][j][s1][s2] , dp[!sign][j][s1][s2 - 1]);
                  }
                //  if(dp[sign][j][s1][s2] > 0)
                //  {
               //       printf("dp[%d][%d][%d][%d] = %I64d\n",i,j,s1,s2,dp[sign][j][s1][s2]);
               //   }
              }
        }
    }

    for(int i = 1;i <= s;i++)
    {
        update(ans , dp[sign][i][2][2]);
    }
    ans = (ans * 2 % MOD ) * 2 % MOD;
    cout<<ans<<endl;
}

int main()
{
    init();
    work();

    return 0;
}

