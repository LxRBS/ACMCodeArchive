#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
int L,N,M;
int A[505],B[505],C[505];
int S[25005];
int X;
bool read(){
    if ( EOF == scanf("%d%d%d",&L,&N,&M) ) return false;
    for(int i=0;i<L;++i)scanf("%d",A+i);
    for(int i=0;i<N;++i)scanf("%d",B+i);
    for(int i=0;i<M;++i)scanf("%d",C+i);
    return true;
}
bool proc(set<int>const&s){
    for(int i=0;i<M;++i)
        if ( s.end() != s.find(X-C[i]) )
            return true;
    return false;
}
int main(){
    for(int kase=1;read();++kase){
        //int k = 0;
        set<int> s;
        for(int i=0;i<L;++i)for(int j=0;j<N;++j)s.insert( A[i] + B[j] );
        printf("Case %d:\n",kase);

        int q;
        scanf("%d",&q);
        for(int i=0;i<q;++i){
            scanf("%d",&X);
            printf(proc(s)?"YES\n":"NO\n");
        }
    }
    return 0;
}
