/**
    �������ɸ����Σ�����Щ���εĲ����ܳ�
    ���͵�ɨ���߷���
    ����������2w������Ҫ��ɢ����������Ҫ����������ӳ�䵽��1��ʼ
    �Ѿ��ε�ˮƽ�߲���ϱߺ��±ߣ����ñ��
    Ȼ����y�����򣬴��µ���ɨ��
    ʹ���߶�����¼��ǰ��������״̬��Ϣ
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
    int len;//���ǳ���
    int cnt;//���Ƕ���
    bool lflag;//��˵��Ƿ񱻸���
    bool rflag;//�Ҷ˵��Ƿ񱻸���
    int maxcover;//��ǰ���䱻�������ǵĴ�������Ϊ�����븲������һһ��Ӧ������������Ǳ�����ר��
}ST[SIZE<<2];

//t��ʾ�ڵ㣬[s,e]��ʾ��ǰ�ڵ��Ӧ����������
void _pushUp(int t,int s,int e){
    if(ST[t].maxcover){ //�������䱻����
        ST[t].len = e-s+1;
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
    int xleft,xright,y;
    int flag;//1��ʾ�±ߣ�0��ʾ�ϱ�
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
    //����ߴ�1��ʼ
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
            //ˮƽ��
            ans += abs(ST[1].len - prev);
            prev = ST[1].len;
            //��ֱ��
            ans += c0 * ( Edge[i].y - h0 ) << 1;
            h0 = Edge[i].y;
            c0 = ST[1].cnt;
        }

        printf("%d\n",ans);
    }
    return 0;
}
