#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
int T,n;
const int N=50000;
vector<pair<int,int> > vec;
int main(){
    for(int i=1;i<=N;i++){
        vec.push_back({1,i});
        if(i>1) vec.push_back({i,1});
    }
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        long long ans;
        if(n&1) ans=1ll*n*(n/2)*(n/2-1)/2;
        else ans=1ll*n*(1ll*(n/2)*(n/2-1)/2+1ll*(n/2-1)*(n/2-2)/2)/2;
        ans=1ll*n*(n-1)*(n-2)/6-ans;
        printf("%lld\n",ans);
        for(int i=0;i<vec.size();i++){
            if(n>0){n--;
                if(i%4==0||i%4==3) printf("%d %d\n",vec[i].first,vec[i].second);
                else printf("%d %d\n",-vec[i].first,-vec[i].second);
            }
        }
        for(int i=0;i<vec.size();i++){
            if(n>0){n--;
                if(i%4==0||i%4==3){
                    if(!i) printf("%d %d\n",vec[i].first,-vec[i].second);
                    else if(i%4==3) printf("%d %d\n",vec[i+1].first,-vec[i+1].second);
                    else printf("%d %d\n",vec[i-1].first,-vec[i-1].second);
                }
                else printf("%d %d\n",-vec[i].first,vec[i].second);
            }
        }
        if(n>0){n--;printf("%d %d\n",N,0);}
        if(n>0){n--;puts("2 3");}
        assert(n==0);
    }
    return 0;
}