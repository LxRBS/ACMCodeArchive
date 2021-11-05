/*
    ��������ͼ����ȷ����������С����ͼ
    �����ж���ڵ�����������ѡȡ��С��һ���ڵ���Ϊ��
*/

#include <stdio.h>
#include <utility>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef long long weight_t;

//just as its names
int const SIZE_OF_VERTICES = 2000;
int const SIZE_OF_EDGES = 100000;
weight_t const INF = 1LL << 60;

struct edge_t{
    int from,to;
    weight_t weight;
}Edge[SIZE_OF_EDGES];
int ECnt;

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
}

inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt++].weight = w;
}

//����ͼ�Ĳ�������С����ͼ������(Ȩֵ,��)
//vnΪԭͼ�����������1��ʼ
//enΪԭͼ�ߵ���������1��ʼ
//edgeΪԭͼ�߱���1��ʼ���ں����лᱻ�ı�
//sumԭͼ�еı�Ȩ�ͣ�����ʹ��INF�����棬����INF��ÿ����Ŀ�ж����������仯
//in�Ǹ������飬������¼���ڵ����С���
//pre�Ǹ������飬�����͸��ڵ���С��ߵĳ���
//flag��idx���Ǹ�������
pair<weight_t,int> ChuLiu(int vn,int en,edge_t edge[],weight_t sum,weight_t in[],int pre[],int flag[],int idx[]){
    //�������Դ��������
    int u,v,s = vn+1;
    ++sum;
    for(int i=1;i<=vn;++i){
        edge[u=en+i].from = s;
        edge[u].to = i;
        edge[u].weight = sum;
    }

    int een = en;
    weight_t ans = 0;
    int ret = ( en += vn++ ) + 1;


    while(1){
        //ȷ����С���
        fill(in+1,in+vn+1,INF);
        for(int i=1;i<=en;++i)if((u=edge[i].from)!=(v=edge[i].to)&&edge[i].weight<in[v]){
            if ( ( pre[v] = u ) == s ) ret = i;
            in[v] = edge[i].weight;
        }

        //û������ͼ�����ǲ����ܵ�
        //for(int i=1;i<=vn;++i)if(i!=s&&INF==in[i])return make_pair(-1,0);

        in[s] = 0;
        fill(idx+1,idx+vn+1,-1);
        fill(flag+1,flag+vn+1,-1);

        //�һ�
        int cnt = 1;
        for(int i=1;i<=vn;++i){
            ans += in[v=i];
            while( flag[v] != i && -1 == idx[v] && v != s ){
                flag[v] = i;
                v = pre[v];
            }

            if ( v != s && -1 == idx[v] ){
                for(u=pre[v];u!=v;u=pre[u]){
                    idx[u] = cnt;
                }
                idx[v] = cnt++;
            }
        }

        //û�л�
        if ( 1 == cnt ) break;

        for(int i=1;i<=vn;++i)if(-1==idx[i])idx[i]=cnt++;

        //���㣬�ر��
        for(int i=1;i<=en;++i){
            edge[i].from = idx[edge[i].from];
            edge[i].to = idx[v = edge[i].to];
            if ( edge[i].from != edge[i].to ){
                edge[i].weight -= in[v];
            }
            /*
            if ( edge[i].from != edge[i].to ){
                edge[i++].weight -= in[v];
            }else{
                swap(edge[i],edge[en--]);//���ﲻ�ܽ����ߣ���Ϊ�ߵ���������õ�
            }
            //*/
        }

        vn = cnt - 1;
        s = idx[s];
    }

    if ( ans >= ( sum << 1 ) ) return make_pair(-1,0);
    return make_pair(ans-sum,ret-een);
}

int N,M;
weight_t Sum;
bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    initGraph(N+1);

    int a,b;
    weight_t w;
    Sum = 0LL;
    for(int i=0;i<M;++i){
        scanf("%d%d%I64d",&a,&b,&w);
        mkEdge(a+1,b+1,w);
        Sum += w;
    }

    return true;
}

weight_t In[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
int Flag[SIZE_OF_VERTICES];
int Idx[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    for(;read();){
        pair<weight_t,int> ans = ChuLiu(N,M,Edge,Sum,In,Pre,Flag,Idx);

        if ( ans.second ) printf("%I64d %d\n",ans.first,ans.second-1);
        else puts("impossible");
        putchar('\n');
    }
    return 0;
}