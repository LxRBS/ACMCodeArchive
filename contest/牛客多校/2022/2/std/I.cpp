#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define SZ(v) ((int)v.size())
#define fs first
#define sc second
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
ll n,k,d;
db X[10010][55],Y[10010][55],Mkd[55][55],Mnd[10010][55];
int main(){
	cin>>n>>k>>d;
	assert(1<=n&&n<=10000);
	assert(1<=k&&k<=50);
	assert(1<=d&&d<=50);
	rep(i,1,n){
		db sum=0;
		rep(j,1,k){
			scanf("%lf",&X[i][j]);
			assert(1<=X[i][j]&&X[i][j]<=1000);
			sum=sum+X[i][j]*X[i][j];
		}
		sum=1.0/sqrt(sum);
		rep(j,1,k){
			X[i][j]=X[i][j]*sum;
		}
	}
	rep(i,1,n){
		rep(j,1,d){
			scanf("%lf",&Y[i][j]);
			assert(1<=Y[i][j]&&Y[i][j]<=1000);
		}
	}
	rep(i,1,k){
		rep(j,1,d){
			db sum=0;
			rep(p,1,n){
				sum=sum+X[p][i]*Y[p][j];
			}
			Mkd[i][j]=sum;
		}
	}
	rep(i,1,n){
		rep(j,1,d){
			db sum=0;
			rep(p,1,k){
				sum=sum+X[i][p]*Mkd[p][j];
			}
			Mnd[i][j]=sum;
		}
	}
	rep(i,1,n){
		rep(j,1,d){
			printf("%.8lf%c",Mnd[i][j],(j==d)?'\n':' ');
		}
	}
	return 0;
}
/*
3 2 3
3 4
6 8
3 4
1 2 3
2 5 3
5 3 1
*/
