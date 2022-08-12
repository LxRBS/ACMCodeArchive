/**
    �������ɸ����Σ�����Щ���εĲ������
    ���͵�ɨ���߷���
    ����������10w��������ʵ��������Ҫ����ɢ��
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
    double len;//���ǳ���
    int cnt;//���Ƕ����������Ŀ����Ҫ
    bool lflag;//��˵��Ƿ񱻸���
    bool rflag;//�Ҷ˵��Ƿ񱻸���
    int maxcover;//��ǰ���串�ǵ������
}ST[SIZE<<2];

//t��ʾ�ڵ㣬[s,e]��ʾ��ǰ�ڵ��Ӧ����������
void _pushUp(int t,int s,int e){
    if(ST[t].maxcover){ //�������䱻����
        ST[t].len = X[e]-X[s-1];//���㳤�ȣ���Ҫ��Դ������㣬�����ñ�����±�
        ST[t].cnt = ST[t].lflag = ST[t].rflag = 1;
        return;
    }
    if(s==e){ //����һ��Ҷ��
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

//�޸Ľڵ㣬t��ʾ�ڵ�,[s,e]��ʾt�ڵ��Ӧ����������
//��[a,b]�����޸ģ�newValueΪ1��ʾ���ǣ�0��ʾ�������
void modify(int t,int s,int e,int a,int b,int newValue){
    if(a<=s&&e<=b){
        if(newValue) ++ST[t].maxcover;
        else --ST[t].maxcover;

        _pushUp(t,s,e);//���t������һ���飬��ֱ��ȷ�������t��Ҷ�ӣ���ֱ��ȷ��������Ӧ������������ȷ��
        return;
    }

    int mid = ( s + e ) >> 1;
    if(a<=mid) modify(lson(t),s,mid,a,b,newValue);
    if(mid<b) modify(rson(t),mid+1,e,a,b,newValue);
    _pushUp(t,s,e);
}

struct edge_t{
    double xleft,xright,y;//����
    int flag;//1��ʾ�±ߣ�0��ʾ�ϱ�
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
            //��ɢ��������ҿ�
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
