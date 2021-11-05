/*
     东边有1~N个城市，西边有1~M个城市
     每对城市连线，问一共有多少个交点
     东边记作x，西边记作y
     则(x1-x2)*(y1-y2)<0时有交点
     也就是说对每一个点，问它的左上有多少个点

     二维排序
     将y按升序排列，y相同x升序
     对于点i来说，在它左上的点只可能是[i+1,K)之间的点
     在这些点之间，如果x比点i小，那么就确定确为左上，
     这种方法可以统计出严格左上（不包括正左、正上）的点
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

typedef long long llt;

int const SIZE = 1020;
llt C[SIZE];//树状数组

inline int lowbit(int x){return x&-x;}

llt query(int idx){
    llt ans = 0;
    for(int i=idx;i>0;i-=lowbit(i))ans+=C[i];
    return ans;
}

void modify(int idx,int delta,int n){
    for(int i=idx;i<=n;i+=lowbit(i)) C[i] += delta;
}

struct _t{
    int x,y;
};

bool operator < (_t const&lhs,_t const&rhs){
    return lhs.y < rhs.y || (lhs.y==rhs.y&&lhs.x<rhs.x);
}

int N,M,K;
_t B[SIZE*SIZE];

bool read(){
    scanf("%d%d%d",&N,&M,&K);
    for(int i=0;i<K;++i)scanf("%d%d",&B[i].x,&B[i].y);
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        sort(B,B+K);
        fill(C,C+SIZE,0LL);

        llt ans = 0;
        for(int i=K-1;i>=0;--i){
            ans += query(B[i].x-1);
            modify(B[i].x,1,M);
        }
        printf("Test case %d: %lld\n",kase,ans);
    }
    return 0;
}
