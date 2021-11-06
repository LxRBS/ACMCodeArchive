#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;

int n , m;
int r[N], l[N];
int dp1[N][N][N],dp2[N][N],dp3[N][N][N];
///dp1[i][j][k]：表示现在做前i行，有的行没填，需要把j~k列都填上
///dp2[i][j]：表示填了前i行，且前j列都填了(就是之后只要填第j列之后的列)
///dp3[i][j][k]：表示填了前i行，下一个没填的行是第k行，现在填了第k行的前j列

void update(int &o, int p) { o = min(o, p); }

void init()
{
    scanf("%d %d",&n, &m);
    for(int i = 1;i <= n;i++)
      scanf("%d %d",&l[i],&r[i]);
}

void work()
{
    memset(dp1, 0x3f, sizeof(dp1));
    memset(dp2, 0x3f, sizeof(dp2));
    memset(dp3, 0x3f, sizeof(dp3));

    int ans = n;

    dp1[1][l[1]][r[1]] = 0;
    dp2[0][0] = 0;
    r[0] = 0;l[0] = -1;

    for (int i = 0; i < n; i++)
    {
        ///dp1
        for(int j = l[i + 1];j <= r[i];j ++)///l[i + 1] <= j
          for(int k = j;k <= r[i];k ++)
          if(dp1[i][j][k] <= n)
          {
              //printf("dp1[%d][%d][%d] = %d\n",i,j,k,dp1[i][j][k]);
              if(j < k)
              {
                  update( dp1[i + 1][j + 1][k] , dp1[i][j][k] + 1);
              }
              if(j == k)
              {
                  update( dp2[i + 1][j] , dp1[i][j][k] + 1);
              }
              update(dp1[i + 1][j][r[i + 1]] , dp1[i][j][k]);
          }

        ///dp2
        for(int j = 0;j <= r[i];j++)
        if(dp2[i][j] <= n)
        {
          //  printf("dp2[%d][%d] = %d\n",i,j,dp2[i][j]);
            for(int k = i + 1;k <= n;k++)
            {
                if( j == r[k])
                  update( dp2[k][r[k]] , dp2[i][j] );
                if( j < r[k] )
                  update( dp3[i][k][max(j,l[k] - 1)] , dp2[i][j]);
            }
        }
        ///dp3
        for(int j = i + 1;j <= n;j++)
        {
            for(int k = l[j] - 1;k <= r[j];k++)
            if(dp3[i][j][k] <= n)
            {
               // printf("dp3[%d][%d][%d] = %d\n",i,j,k,dp3[i][j][k]);
                if(j == i + 1)
                {
                    if(k < r[j])
                    {
                    //    printf("->dp1[%d][%d][%d]\n",i+1,min(k + 1,r[j]),r[j + 1]);
                        update(dp1[i + 1][min(k + 1,r[j])][r[j]] , dp3[i][j][k]);
                    }
                    else
                    {
                   //     printf("->dp2[%d][%d]\n",i+1,r[j]);
                        update(dp2[i + 1][r[j]] , dp3[i][j][k]);
                    }
                }
                else
                {
                    int nxtk = k;
                    if(r[i + 1] > k) nxtk++;
                    update(dp3[i + 1][j][nxtk],dp3[i][j][k] + 1);
                }
            }
        }
    }

    for(int i = 1;i <= n;i++)
    {
        for(int j = 0;j <= 100;j++)
        if(dp2[i][j] <= 100)
        {
         //   cout<<i<<" "<<j<<" "<<dp2[i][j]<<endl;
            update(ans , dp2[i][j] + n - i);
        }
    }

    printf("%d\n",ans);
}

int main()
{
    int Case,Res = 0;

    for (scanf("%d",&Case);Case > 0;Case--)
    {

        init();
        printf("Case #%d: ",++Res);
        work();
    }

    return 0;
}
