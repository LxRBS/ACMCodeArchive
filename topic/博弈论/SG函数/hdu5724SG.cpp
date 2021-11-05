#include <cstdio>
#include <algorithm>
using namespace std;

int SG[(1<<20)+5];

void initSG(){
    fill(SG,SG+(1<<20),-1);
    int t = 0;
    for(int i=1;i<(1<<20);i=(i<<1)|1){
        SG[i] = 0;
    }
}

int move(int oldStatus,int idx){
    int oldIdx = idx;
    while( idx > 0 && 0 != ( oldStatus & ( 1<<(idx-1) ) ) ) --idx;
    if ( 0 == idx ) return -1;
    return oldStatus ^ (1<<oldIdx) ^ (1<<(idx-1));
}

int sg(int status){
    if ( -1 != SG[status] ) return SG[status];

    bool flag[20] = {false};
    for(int i=0,t=1;i<20;++i,t=t<<1){
        if ( 0 == ( t & status ) ) continue;

        int newStatus = move(status,i);
        if ( -1 == newStatus ) continue;

        flag[sg(newStatus)] = true;
    }
    for(int i=0;i<20;++i) if (!flag[i]) return SG[status] = i;
}

int main()
{
    initSG();

    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        int ret = 0;
        while(n--){
            int m;
            scanf("%d",&m);
            int pos = 0;
            while(m--){
                int p;
                scanf("%d",&p);
                pos = pos | ( 1 << (20-p) );
            }

            if ( SG[pos] != -1 ) ret = ret ^ SG[pos];
            else ret = ret ^ sg(pos);
        }
        printf(ret?"YES\n":"NO\n");
    }
    return 0;
}
