/**
    给定若干个矩形，求这些矩形的并的周长
    典型的扫描线方法
    坐标区间在2w，不需要离散化，但是需要把所有坐标映射到从1开始
    把矩形的水平边拆成上边和下边，做好标记
    然后按照y轴排序，从下到上扫描
    使用线段树记录当前区间的相关状态信息
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

inline int abs(int n){
    return n>=0?n:-n;
}

int const SIZE = 20010;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

struct{
    int len;//覆盖长度
    int cnt;//覆盖段数
    bool lflag;//左端点是否被覆盖
    bool rflag;//右端点是否被覆盖
    int maxcover;//当前区间被整个覆盖的次数，因为撤销与覆盖总是一一对应，所以这个域是本区间专用
}ST[SIZE<<2];

//t表示节点，[s,e]表示当前节点对应的坐标区间
void _pushUp(int t,int s,int e){
    if(ST[t].maxcover){ //整个区间被覆盖
        ST[t].len = e-s+1;
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
    int xleft,xright,y;
    int flag;//1表示下边，0表示上边
}Edge[SIZE];

bool operator < (edge_t const&lhs,edge_t const&rhs){
    return lhs.y<rhs.y||(lhs.y==rhs.y&&lhs.xleft<rhs.xleft)||(lhs.y==rhs.y&&lhs.xleft==rhs.xleft&&lhs.xright<rhs.xright);
}

int N,STN;

bool read(){
    if(EOF==scanf("%d",&N)) return false;

    int xmin = 1000000000;
    int xleft,ybottom,xright,ytop;
    for(int i=0,k=0;i<N;++i,k+=2){
        xmin = min(xmin,Edge[k].xleft = getInt());
        Edge[k].y = getInt();
        Edge[k].xright = getInt() - 1;
        Edge[k].flag = 1;

        Edge[k+1] = Edge[k];
        Edge[k+1].flag = 0;
        Edge[k+1].y = getInt();
    }
    //将左边从1开始
    xmin -= 1;
    N <<= 1;
    STN = -1000000000;
    for(int i=0;i<N;++i){
        Edge[i].xleft -= xmin;
        STN = max(STN, Edge[i].xright -= xmin);
    }

    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        memset(ST,0,sizeof(ST));
        sort(Edge,Edge+N);
        int ans = 0, prev = 0, h0 = Edge[0].y, c0 = 0;

        for(int i=0;i<N;++i){
            modify(1,1,STN,Edge[i].xleft,Edge[i].xright,Edge[i].flag);
            //水平边
            ans += abs(ST[1].len - prev);
            prev = ST[1].len;
            //竖直边
            ans += c0 * ( Edge[i].y - h0 ) << 1;
            h0 = Edge[i].y;
            c0 = ST[1].cnt;
        }

        printf("%d\n",ans);
    }
    return 0;
}
