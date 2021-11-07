/**
    n个player，m个fans，fans对player有一个喜爱关系
    然后有q行操作，每行操作为(x,y)
    其含义是：翻转fan x对player y的喜爱关系
    fan x会去看player y的比赛，如果满足以下任何一个条件：
    1 fan x喜爱player y
    2 fan x和fan x'喜爱同一个球员y'，且x'喜爱y
    现在要求选出若干个player参加全明星赛，使得所有的fan都会去看比赛
    对每一个q操作，输出全明星赛所需的最少球员数量

    显然是一个二分图，任意两个fan只要处在同一个连通分量中，只选其中一个player即可
    而q操作显然是加边与删边操作
    因此是动态维护连通块的问题
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

//SIZE要是点加边的总数
int const SIZE = 1250000;
int const INF = 1000000000;

struct cmd_t{
    int op,x,y;
    int eidx;//该边对应的编号
}Cmds[SIZE];

struct edge_t{
    int from,to;
    int time;
}Edge[SIZE];
int ECnt;

//边(x,y)到时间的映射
map<pair<int,int>,int> Map;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int early; //最早的节点编号
    unsigned char flip;//第0位表示翻转延迟
}Node[SIZE];
int toUsed = 0;

//Timei表示i的时间线
int Time[SIZE];
int N,M,Q;

inline void _pushUp(int t){//主要维护early
    Node[t].early = t;

    int son = Node[t].son[LEFT];
    if(son){
        if(Time[Node[son].early] < Time[Node[t].early]) Node[t].early = Node[son].early;
    }

    if(son = Node[t].son[RIGHT]){
        if(Time[Node[son].early] < Time[Node[t].early]) Node[t].early = Node[son].early;
    }
}

inline void _pushDown(int t){
    if ( t && (Node[t].flip & 1) ){//处理翻转
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1;

        Node[t].flip ^= 1;
    }
}
//判断t是否为本splay的根
inline bool _isRoot(int t){
    int p = Node[t].parent;
    return 0==p || (Node[p].son[LEFT]!=t&&Node[p].son[RIGHT]!=t);
}
//获取排行，不能用于树根
inline int _getSN(int t){
    return Node[Node[t].parent].son[RIGHT] == t;
}
//伸展树的link操作，将p的sn儿子设置为t
inline void _link(int p,int sn,int t){
    Node[Node[t].parent=p].son[sn] = t;
}
//旋转操作，t不能是根
inline void _rotate(int t){
    int p = Node[t].parent;//父节点
    int g = Node[p].parent;//祖父节点
    int sn = _getSN(t);
    int osn = sn^1;
    //不需要pushDown，在splay中pushDown

    _link(p,sn,Node[t].son[osn]);
    Node[t].parent = g;
    if(!_isRoot(p))Node[g].son[_getSN(p)]=t;
    _link(t,osn,p);

    _pushUp(p);
}
//从根开始逐级下放延迟标记
void _maintain(int t){
    if(!_isRoot(t)) _maintain(Node[t].parent);
    _pushDown(t);
}
//伸展操作，必到树根
void _splay(int t){
    _maintain(t);
    while(!_isRoot(t)){
        int p = Node[t].parent;
        if(!_isRoot(p)) _getSN(t)==_getSN(p)?_rotate(p):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);
}
//从根到x形成一条链，返回
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//将链接上
        _pushUp(x);
    }
    return t;
}
//令x成为原树的根
inline void _makeRoot(int x){
    _access(x);
    _splay(x);
    Node[x].flip ^= 1; //打翻转标记
}
//获取x所在树的根节点
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    _splay(x);
    return x;
}
//令child是parent的子节点
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}
//将child从parent树上切下
inline void cut(int parent,int child){
    _makeRoot(parent);
    _access(child);
    _splay(child);

    //普通的LCTcut是保证连接，直接cut即可
    //此处需要判断child和parent是否直连
    //因为只会切除点节点和边节点，则其在LCT上必然紧挨着
    if(Node[child].son[LEFT]==parent){
        Node[child].son[LEFT] = Node[Node[child].son[LEFT]].parent = 0;
        _pushUp(child);
    }

}
inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}

//连边操作，xy是点节点，e是边节点
inline void link(int x,int y,int e){
    //首先检查连通性
    if(!isConnect(x,y)){
        link(x,e);
        link(e,y);
        return;
    }

    //原来就连通，首先形成一条链
    _makeRoot(x);_access(y);_splay(y);
    //取出链上的时间最早节点
    int t = Node[y].early;
    if(Time[e]>Time[t]){
        //取到边的编号
        int tt = t - N - M;//忘记改成N+M了，各种错误
        cut(Edge[tt].from,t);
        cut(t,Edge[tt].to);
        //加新边
        link(x,e);
        link(e,y);
    }
}

int First;
int CmdCnt = 0;

//球员在前，fans在后
set<pair<int,int> > Bian;

void read(){
    //初始化先
    ECnt = 0;Map.clear();
    Bian.clear();

    N = getUnsigned();
    M = getUnsigned();
    Q = getUnsigned();

    //读入fans
    for(int a,i=1;i<=N;++i){
        int n = getUnsigned();
        while(n--){
            a = getUnsigned();
            //i到a+N有一条边
            Edge[++ECnt].time = Q + 1;//所有能够留到最后的边时间线都是Q+1，注意这道题不是M+1
            ++CmdCnt;//从1开始计数
            Cmds[CmdCnt].op = 0;//加边操作
            Cmds[CmdCnt].eidx = Map[make_pair(Edge[ECnt].from=Cmds[CmdCnt].x=i,Edge[ECnt].to=Cmds[CmdCnt].y=a+N)]=ECnt;
            Bian.insert(make_pair(i,a));
        }
    }

    First = CmdCnt;

    //读入所有的指令
    for(int y,x,i=1;i<=Q;++i){
        ++CmdCnt;
        Cmds[CmdCnt].y = ( y = getUnsigned() ) + N;//fans的编号要加N
        Cmds[CmdCnt].x = x = getUnsigned();

        if(Bian.find(make_pair(x,y))!=Bian.end()){//如果原来就有边，这是删边操作
            Bian.erase(make_pair(x,y));
            Cmds[CmdCnt].op = 1;
            int time = Map[make_pair(Cmds[CmdCnt].x,Cmds[CmdCnt].y)];
            Edge[Cmds[CmdCnt].eidx = time].time = i;//表明该边在i时间消失
        }else{//加边操作
            Bian.insert(make_pair(x,y));
            Cmds[CmdCnt].op = 0;
            Edge[++ECnt].time = Q+1;//所有能够留到最后的边时间线都是Q+1
            Cmds[CmdCnt].eidx = Map[make_pair(Edge[ECnt].from = Cmds[CmdCnt].x,Edge[ECnt].to = Cmds[CmdCnt].y)] = ECnt;
        }
    }
    //将所有点节点的时间线设置为无穷大
    fill(Time+1,Time+N+M+1,INF);//N+M!!!
    //所有节点的early初始为自己
    //for(int i=1;i<=N;++i)Node[i].early = i;

    //将所有边设定为各自的时间线
    //边节点在LCT中的编号就是i+N+M
    for(int i=1;i<=ECnt;++i){
        Time[i+N+M] = Edge[i].time;//注意此题是N+M
    }
    /*调试
    printf("cmd:\n");
    for(int i=1;i<=CmdCnt;++i){
    	printf("cmd %d:%d %d %d, pos:%d\n",i,Cmds[i].op,Cmds[i].x,Cmds[i].y,Cmds[i].eidx);
	}

	printf("edge:\n");
	for(int i=1;i<=ECnt;++i){
		printf("(%d,%d,%d)\n",Edge[i].from,Edge[i].to,Edge[i].time);
	}//*/
}

void dispNode(int n){
    for(int i=1;i<=n;++i){
        printf("%d: parent=%d, sons:(%d, %d) %d\n",i,Node[i].parent,Node[i].son[LEFT],Node[i].son[RIGHT],Node[i].flip&1);
    }
}

int Deg[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("3.txt","w",stdout);
    read();

    fill(Deg,Deg+N+M+1,0);
    int c0 = M;//记录度数为0的Fans的数量
    int d0 = N;//记录度数为0的player的数量
    int ans = N+M;//连通块的数量

    for(int i=1;i<=First;++i){//加边操作，不用回答
        int x = Cmds[i].x;
        int y = Cmds[i].y;
        int e = Cmds[i].eidx + N + M;
        if(!isConnect(x,y)){//如果xy原来不连通
            --ans;
        }
        link(x,y,e);

        if(0==Deg[x]++) --d0;
        if(0==Deg[y]++) --c0;
    }

    //printf("cc：%d\n",ans);
    for(int i=First+1;i<=CmdCnt;++i){//答问题
        int cmd = Cmds[i].op;
        int x = Cmds[i].x;
        int y = Cmds[i].y;
        int e = Cmds[i].eidx + N + M;//边节点编号

        if(0==cmd){//加边
            if(!isConnect(x,y)) --ans;
            link(x,y,e);

            if(0==Deg[x]++) --d0;
            if(0==Deg[y]++) --c0;
        }else if(1==cmd){//删边
            cut(x,e);
            cut(e,y);

            if(!isConnect(x,y)) ++ans;

            if(0==--Deg[y]) ++c0;
            if(0==--Deg[x]) ++d0;
        }else{
            throw runtime_error("XXXXXXXXX");
        }

        if(c0){//如果有fans度为0，则没有答案
            puts("-1");
        }else{
            printf("%d\n",ans-d0);
        }
        //printf("after q: %d %d\n",i-First,ans);
        //dispNode(N+M+ECnt);
    }
    return 0;
}
