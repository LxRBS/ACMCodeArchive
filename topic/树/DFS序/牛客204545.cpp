/**
    子树更新，最后单点查询
*/
class Solution {
public:
    typedef long llt;
    enum {SIZE=100010};
    int InIdx[SIZE];
    int OutIdx[SIZE];
    int NewIdx[SIZE<<1];
    int NCnt;
    int N;

    vector<int> Vertex[SIZE];

    void dfs(int node, int parent){
        NewIdx[NCnt] = node;
        InIdx[node] = NCnt++;
        vector<int> const& vec = Vertex[node];
        int son;
        for(vector<int>::const_iterator it=vec.begin();it!=vec.end();++it){
            if((son=*it)!=parent){
                dfs(son, node);
            }
        }
        NewIdx[NCnt] = node;
        OutIdx[node] = NCnt++;
    }

    llt Peak[SIZE<<3];
    llt Lazy[SIZE<<3];
    int lson(int x){return x<<1;}
    int rson(int x){return lson(x)|1;}

    void _pushUp(int t){Peak[t] = max(Peak[lson(t)],Peak[rson(t)]);}

    void _pushDown(int t){
        if(0==Lazy[t]) return;
        llt& x = Lazy[t];

        int son = lson(t);
        Peak[son] += x;
        Lazy[son] += x;

        son = rson(t);
        Peak[son] += x;
        Lazy[son] += x;

        x = 0;
    }

    void modify(int t,int s,int e,int a,int b,int delta){
        if(a<=s&&e<=b){
            Peak[t] += delta;
            Lazy[t] += delta;
            return;
        }

        _pushDown(t);
        int m = (s+e)>>1;
        if(a<=m) modify(lson(t),s,m,a,b,delta);
        if(m<b) modify(rson(t),m+1,e,a,b,delta);
        _pushUp(t);
    }

    void modifySubTree(int r, int delta){
        modify(1,1,(this->N)<<1,InIdx[r],OutIdx[r],delta);
    }

    vector<long> Result;
    void dfsDown(int t,int s,int e){
        if(s==e){
            if(InIdx[NewIdx[s]]==s){//如果是入点
                Result[NewIdx[s]-1] = Peak[t];
            }
            return;
        }
        _pushDown(t);

        int m = (s+e)>>1;
        dfsDown(lson(t),s,m);
        dfsDown(rson(t),m+1,e);
    }

    /**
     * 从 1 到 n 每个结点的权值。
     * @param n int整型
     * @param Edge Point类vector (u, v) 集合
     * @param q int整型
     * @param Query Point类vector Point.x 为题中 r, Point.y为题中 v
     * @return long长整型vector
     */
    vector<long> solve(int n, vector<Point>& Edge, int q, vector<Point>& Query) {
        this->N = n;
        //首先整理一下边表
        for(vector<Point>::const_iterator it=Edge.begin();it!=Edge.end();++it){

            Vertex[it->x].push_back(it->y);
            Vertex[it->y].push_back(it->x);
        }
        //再求个序
        NCnt = 1;
        dfs(1, 0);

        //初始化线段树
        fill(Peak,Peak+(this->N<<3)+1,0);
        fill(Lazy,Lazy+(this->N<<3)+1,0);

        //对q次询问
        for(int iq=0;iq<q;++iq){
            int r = Query[iq].x;
            int d = Query[iq].y;
            modifySubTree(r, d);
        }

        //答问题之前先pushDown一下
        //顺便答问题
        Result.assign(n,0);
        dfsDown(1,1,N<<1);

        return Result;
    }
};