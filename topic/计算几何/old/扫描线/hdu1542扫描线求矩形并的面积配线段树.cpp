/**
    给定若干个矩形，求这些矩形的并的面积
    典型的扫描线方法
    坐标区间在10w，但是是实数，所以要做离散化
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

int const SIZE = 1100;


double X[SIZE];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

struct{
    double len;//覆盖长度
    int cnt;//覆盖段数，这道题目不需要
    bool lflag;//左端点是否被覆盖
    bool rflag;//右端点是否被覆盖
    int maxcover;//当前区间覆盖的最大数
}ST[SIZE<<2];

//t表示节点，[s,e]表示当前节点对应的坐标区间
void _pushUp(int t,int s,int e){
    if(ST[t].maxcover){ //整个区间被覆盖
        ST[t].len = X[e]-X[s-1];//计算长度，需要由源数组计算，不能用本身的下标
        ST[t].cnt = ST[t].lflag = ST[t].rflag = 1;
        return;
    }
    if(s==e){ //这是一个叶子
        ST[t].len = ST[t].cnt = ST[t].lflag = ST[t].rflag = 0;
        return;
    }

    int son = lson(t);
    ST[t].cnt = ST[son].cnt;
    ST[t].len = ST[son].len;
    ST[t].lflag = ST[son].lflag;

    son = rson(t);
    ST[t].cnt += ST[son].cnt - ((ST[lson(t)].rflag&&ST[son].lflag)?1:0);
    ST[t].len += ST[son].len;
    ST[t].rflag = ST[son].rflag;
}

//修改节点，t表示节点,[s,e]表示t节点对应的坐标区间
//将[a,b]进行修改，newValue为1表示覆盖，0表示解除覆盖
void modify(int t,int s,int e,int a,int b,int newValue){
    if(a<=s&&e<=b){
        if(newValue) ++ST[t].maxcover;
        else --ST[t].maxcover;

        _pushUp(t,s,e);//如果t区间是一整块，则直接确定；如果t是叶子，则直接确定；否则应该由两个儿子确定
        return;
    }

    int mid = ( s + e ) >> 1;
    if(a<=mid) modify(lson(t),s,mid,a,b,newValue);
    if(mid<b) modify(rson(t),mid+1,e,a,b,newValue);
    _pushUp(t,s,e);
}

struct edge_t{
    double xleft,xright,y;//坐标
    int flag;//1表示下边，0表示上边
}Edge[SIZE];

bool operator < (edge_t const&lhs,edge_t const&rhs){
    return lhs.y < rhs.y;
}

int N,STN;

bool read(){
    scanf("%d",&N);
    if(0==N) return false;

    for(int i=0,k=0;i<N;++i,k+=2){
        scanf("%lf%lf%lf%lf",X+k,&Edge[k].y,X+k+1,&Edge[k+1].y);
        Edge[k].xleft = Edge[k+1].xleft = X[k];
        Edge[k].xright = Edge[k+1].xright = X[k+1];
        Edge[k].flag = 1;
        Edge[k+1].flag = 0;
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        N<<=1;
        sort(X,X+N);
        STN = unique(X,X+N) - X;
        sort(Edge,Edge+N);

        memset(ST,0,sizeof(ST));

        double ans = 0.0;
        double len = 0.0;
        double h = Edge[0].y;
        for(int i=0;i<N;++i){
            ans += len * ( Edge[i].y - h );
            //离散化，左闭右开
            int a = lower_bound(X,X+STN,Edge[i].xleft) - X + 1;
            int b = lower_bound(X,X+STN,Edge[i].xright) - X;
            modify(1,1,STN,a,b,Edge[i].flag);
            len = ST[1].len;
            h = Edge[i].y;
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n",kase,ans);
    }
    return 0;
}
