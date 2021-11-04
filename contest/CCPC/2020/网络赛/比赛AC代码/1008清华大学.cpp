#include <bits/stdc++.h>

using namespace std;
using ld=long double;

const int N=55;

ld f[N][N*2][N*2][2],g[N][N*2];
int n,x[N],x0;

int main(){
    int t; cin>>t;
    while(t--){
        cin>>n>>x0;
        assert(1<=n&&n<=50&&-n<=x0&&x0<=n);
        for(int i=1;i<=n;++i){
            cin>>x[i];
            assert(x[i]<=i&&x[i]>=1);
        }
        g[1][1]=1;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=2*i-1;j+=2){
                for(int k=2*i-1;k>=j;k-=2){
                    int cnt=i-(k-j)/2;
                    for(int l=0;l<2;++l){
                        if(cnt>x[i]){
                            f[i][j][k][l]=1e4;
                            if(j!=1) f[i][j][k][l]=min(f[i][j][k][l],f[i][j-2][k][0]+2+l*(k-j));
                            if(k!=2*i-1) f[i][j][k][l]=min(f[i][j][k][l],f[i][j][k+2][1]+2+(1-l)*(k-j));
                            f[i][j][k][l]=(f[i][j][k][l]*(cnt-x[i])+g[i][l?k:j]*x[i])/cnt;
                        }else f[i][j][k][l]=g[i][l?k:j];
                    }
                }
            }
            for(int j=1;j<=2*i+1;j++){
                g[i+1][j]=1e4;
                for(int k=1;k<=2*i-1;k+=2){
                    int d=(j-1)-k;
                    g[i+1][j]=min(g[i+1][j],f[i][k][k][0]+sqrtl(d*d+1));
                }
            }
        }
        printf("%.12lf\n",(double)g[n+1][n+1+x0]);
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
    }
}