/*
    һ��ͼ���ƥ��
    ����Щ���ǽ������κ����ƥ���

    һ����3�ֱߣ�
    1�����ƥ��ر��ߣ�û������û�����ƥ��
    2�����ƥ���ѡ�ߣ�ĳһ�����ƥ���������ֱߣ���û������ߣ���������������һ�����ƥ��
    3���κ����ƥ�䶼����������ֱ�
    ����������ֱ�

    ��ÿһ����ǿ��ƥ�䣬ʵ���Ͼ��ǰѸñߵ������˵�ɾ��
    Ȼ��ʣ�µ��ܷ�ƥ������ƥ���һ
    ������ԣ���֤���ñ߿��԰�����ĳ�����ƥ����
    ��ñ߱�ȻΪ��1/2�ֱ�

    ������˵�����ƥ����С�����ƥ���һ����ñ߱�Ȼ�ǵ����ֱ�
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//���鼯
struct ufs_t{
    enum {SIZE=510};
    int father[SIZE];
    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int const SIZE_OF_VERTICES = 510;
int const SIZE_OF_EDGES = 250000;

bool Graph[SIZE_OF_VERTICES][SIZE_OF_VERTICES];

inline void initGraph(int n){
    for(int i=1;i<=n;++i) fill(Graph[i],Graph[i]+n+1,false);
}

//˫���
inline void mkEdge(int a, int b){
    Graph[a][b] = Graph[b][a] = true;
}

int SType[SIZE_OF_VERTICES];
int Prec[SIZE_OF_VERTICES];//ǰ��
int Succ[SIZE_OF_VERTICES];//���

int _Vis[SIZE_OF_VERTICES];
int getLca(int x,int y){
    static int tim = 0;
    ++tim;

    for(x=UF.find(x),y=UF.find(y);;swap(x,y)){
        if ( x ){
            if ( _Vis[x] == tim ) return x;
            _Vis[x] = tim;
            x = UF.find(Prec[Succ[x]]);
        }
    }
}

//��������
int Queue[SIZE_OF_VERTICES];
int *QHead, *QTail;

void blossom(int x,int y,int lca){
    while( UF.find(x) != lca ){
        Prec[x] = y;
        y = Succ[x];
        if ( 2 == SType[y] ) SType[*QTail++ = y] = 1;
        UF.father[x] = UF.father[y] = lca;
        x = Prec[y];
    }
}

int bfs(int node,int vn){
    //��ʼ��
    UF.init(vn);
    fill(SType,SType+vn+1,0);

    QHead = QTail = Queue;
    SType[*QTail++ = node] = 1;

    int u,v;
    while( QHead < QTail ){
        u = *QHead++;
        for(int v=1;v<=vn;++v)if(Graph[u][v]){
            if ( 0 == SType[v] ){
                Prec[v] = u;
                SType[v] = 2;
                if ( !Succ[v] ){
                    for(int uu=v,vv=u,last;vv;uu=last,vv=Prec[uu])
						last=Succ[vv],Succ[vv]=uu,Succ[uu]=vv;
					return 1;
                }
                SType[*QTail++ = Succ[v]] = 1;
            }else if ( 1 == SType[v] && UF.find(v) != UF.find(u) ){//�滷���Ҳ���ͬһ����
                int lca = getLca(v,u);
                blossom(u,v,lca);
                blossom(v,u,lca);
            }
        }
    }
    return 0;
}

int Edmonds(int vn){
    fill(Prec,Prec+vn+1,0);
    fill(Succ,Succ+vn+1,0);

    int ret = 0;
    for(int i=1;i<=vn;++i){
        if ( !Succ[i] ) ret += bfs(i,vn);
    }
    return ret;
}

int N,M;
pair<int,int> Edges[SIZE_OF_EDGES];
bool Origin[SIZE_OF_VERTICES][SIZE_OF_VERTICES];

bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N);
    for(int i=1;i<=N;++i)fill(Origin[i],Origin[i]+N+1,false);

    int a,b;
    for(int i=1;i<=M;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
        Origin[a][b] = Origin[b][a] = true;
        Edges[i].first = a, Edges[i].second = b;
    }
    return true;
}

bool Flag[SIZE_OF_EDGES];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int ret = Edmonds(N);
        fill(Flag,Flag+M+1,false);

        vector<int> ans;
        for(int i=1;i<=M;++i){
            int a = Edges[i].first;
            int b = Edges[i].second;

            //ɾ����a��b
            for(int j=1;j<=N;++j){
                Graph[a][j] = Graph[j][a] = Graph[b][j] = Graph[j][b] = false;
            }

            if ( Edmonds(N) < ret - 1 ) ans.push_back(i);

            //��ԭ
            for(int j=1;j<=N;++j){
                Graph[a][j] = Origin[a][j];
                Graph[j][a] = Origin[j][a];
                Graph[b][j] = Origin[b][j];
                Graph[j][b] = Origin[j][b];
            }
        }
        printf("%d\n",ans.size());
        if ( !ans.empty() ) {
            printf("%d",ans[0]);
            for(unsigned i=1;i<ans.size();++i)printf(" %d",ans[i]);            
        }
        printf("\n");
    }
    return 0;
}
