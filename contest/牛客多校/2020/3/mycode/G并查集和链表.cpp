/**
  一个图n个点m条边，都在80万
  然后有q个操作，规模80万
  每次操作给定一个数o，
  将颜色为o的子图，与其相邻的节点也变为颜色o
  如果没有颜色为o的子图，则不操作
  每个点只用一次，每个边也只会用一次
  使用并查集和链表
*/
#include <bits/stdc++.h>
using namespace std;
int getUnsigned(){
    char ch = getchar();
    while( ch < '0' || ch > '9' ) ch = getchar();

    int ret = (int)(ch-'0');
    while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 800010;

struct ufs_t{
    enum{UF_SIZE=800010};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int N,M,Q;
list<int> G[SIZE_OF_VERTICES];
list<int> TmpSet;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        //initGraph(N);
        UF.init(N=getUnsigned());
        M=getUnsigned();

        for_each(G,G+N+1,mem_fun_ref(&list<int>::clear));
        //for(int i=1;i<=N;++i){G[i].clear();

        for(int i=0;i<M;++i){
            int u = getUnsigned() + 1;
            int v = getUnsigned() + 1;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        Q = getUnsigned();
        for(int iq=0;iq<Q;++iq){
            int q = getUnsigned() + 1;
            int node = UF.find(q);
            if(node != q) continue;

            TmpSet.clear();
            //对node相邻的每一个节点
            list<int>& ss = G[node];
            list<int>::iterator it = ss.begin();
            while(it!=ss.end()){
                //printf("pass: %d %d\n",node, *it);
                int u = UF.find(*it);
                if(u==node){/*do nothing*/}
                else{TmpSet.splice(TmpSet.begin(),G[u]);UF.unite(node,u);}
                it = ss.erase(it);
            }
            ss.splice(ss.begin(),TmpSet);
            //cout<<node<<": ";disp(G[node]);
        }
        for(int i=1;i<=N;++i){
            printf("%d ",UF.find(i)-1);
        }
        puts("");
    }
    return 0;
}
