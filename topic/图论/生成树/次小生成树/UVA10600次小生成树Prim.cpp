/*
    ����С�������ʹ�С������
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 110;
weight_t const INF = 1000000000;

//���С��������Prim�㷨������ͬʱ���MST
//gΪͼ��1base��vnΪͼ�Ķ�����
//mstΪ���ز�����MST��Ȩֵ��mst2λ���ز�������С��������Ȩֵ
//dΪ�������飬di��¼i���м�������̾��룬��MST��
//flagΪ�������飬�����
//preΪ�������飬prei��iΪMST�е�һ����
//usedΪ�������飬usedij��ʾijΪMST�е�һ����
//maxeΪ�������飬maxeij��¼MST��i��j·���ϵ���ıߣ����С��������
int Prim42ndMST(weight_t const g[][SIZE],int vn,weight_t&mst,weight_t&mst2,weight_t d[],bool flag[],int pre[],bool used[][SIZE],weight_t maxe[][SIZE]){
    //��ʼ��
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    for(int i=1;i<=vn;++i){
        fill(maxe[i],maxe[i]+vn+1,0);
        fill(used[i],used[i]+vn+1,false);
    }
    mst = 0;

    //��һ������
    fill(pre,pre+vn+1,1);
    for(int i=2;i<=vn;++i)if(g[1][i])d[i]=g[1][i];
    d[1] = 0;
    flag[1] = true;
    pre[1] = 0;

    //һ�μ���һ������
    for(int i=2;i<=vn;++i){
        int k = -1;

        //��ÿһ������j
        for(int j=1;j<=vn;++j){
            //���j����MST�У���j����ǰMST�ľ�������̵�
            if ( !flag[j] && ( -1 == k || d[j] < d[k] ) ){
                k = j;
            }
        }

        //����ͨ��û��������
        //if ( INF == d[k] ) return -1;

        //��k����MST
        mst += d[k];
        flag[k] = true;
        used[k][pre[k]] = used[pre[k]][k] = true;

        //����
        for(int j=1;j<=vn;++j)if(j!=k){
            //���j���м����ĵ㣬���Ը���kj·��֮������
            if ( flag[j] ){
                maxe[j][k] = maxe[k][j] = max(maxe[j][pre[k]],d[k]);
            }

            //���j�����м������п��ܸ���dj
            if ( !flag[j] && g[k][j] && g[k][j] < d[j] ){
                d[j] = g[k][j];
                pre[j] = k;
            }
        }
    }

    mst2 = INF;
    //ö��ÿһ������MST�еı�
    for(int i=1;i<vn;++i)for(int j=i+1;j<=vn;++j)if(g[i][j]&&!used[i][j]){
        mst2 = min(mst2,mst-maxe[i][j]+g[i][j]);
    }

    return 1;
}

weight_t Graph[SIZE][SIZE];//1 base
inline void initGraph(int vn){
    for(int i=1;i<=vn;++i)fill(Graph[i],Graph[i]+vn+1,0);
}
inline void mkEdge(int a,int b,weight_t w){
    Graph[a][b] = Graph[b][a] = w;
}

weight_t D[SIZE];
bool Flag[SIZE];
int Pre[SIZE];
bool Used[SIZE][SIZE];
weight_t Maxe[SIZE][SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase,n,m,a,b,c;
    weight_t mst,mst2;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&n,&m);

        initGraph(n);
        for(int i=0;i<m;++i){
            scanf("%d%d%d",&a,&b,&c);
            mkEdge(a,b,c);
        }

        Prim42ndMST(Graph,n,mst,mst2,D,Flag,Pre,Used,Maxe);

        printf("%d %d\n",mst,mst2);
    }
    return 0;
}