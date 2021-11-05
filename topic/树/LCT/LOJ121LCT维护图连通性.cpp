/**
    模板题，离线LCT动态维护图连通性
    0: 加入边，保证不存在
    1：删除边，保证存
    2：查询两个点是否连通

    原图的每个点和每条边在LCT中均作为点出现
    LCT上记录每个点的消失时间，其中点节点为无穷大，splay维护每个子树中最早的节点
    边节点则根据指令情况进行记录
    对原题中的每个操作，参数分别记作x、y、e，
    0: 分两种情况
      0.1 如果x和y本来不相连，则link(x,e),link(e,y)即可
      0.2 如果x和y原来就连通，则在xy链上找到最早的一个节点，记作e2
        使用splay来维护，可以直接查到这个值，如果e的时间要早于e2，则do nothing
        否则，将e2切除，将e连接
    1: cut(x,e), cut(e,y)
    2: 直接判断(x,y)是否连通即可
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
int const SIZE = 550000;
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
int N,M;

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
        int tt = t - N;
        cut(Edge[tt].from,t);
        cut(t,Edge[tt].to);
        //加新边
        link(x,e);
        link(e,y);
    }
}

void read(){
    //初始化先
    ECnt = 0;Map.clear();

    N = getUnsigned();
    M = getUnsigned();
    //读入所有的指令
    for(int i=1;i<=M;++i){
        Cmds[i].op = getUnsigned();
        Cmds[i].x = getUnsigned();
        Cmds[i].y = getUnsigned();
        if(Cmds[i].x>Cmds[i].y) swap(Cmds[i].x,Cmds[i].y);
        //处理加边和删边的时间线
        if(0==Cmds[i].op){//加边
            Edge[++ECnt].time = M + 1;//所有能够留到最后的边时间线都是M+1
            Cmds[i].eidx = Map[make_pair(Edge[ECnt].from = Cmds[i].x,Edge[ECnt].to = Cmds[i].y)] = ECnt;
        }else if(1==Cmds[i].op){//删边
            int time = Map[make_pair(Cmds[i].x,Cmds[i].y)];
            Edge[Cmds[i].eidx = time].time = i;//表明该边在i时间消失
        }
    }
    //将所有点节点的时间线设置为无穷大
    fill(Time+1,Time+N+1,INF);
    //所有节点的early初始为自己
    //for(int i=1;i<=N;++i)Node[i].early = i;

    //将所有边设定为各自的时间线
    //边节点在LCT中的编号就是i+N
    for(int i=1;i<=ECnt;++i){
        Time[i+N] = Edge[i].time;
        //Node[i+N].early = i + N;
    }
    /*调试
    printf("cmd:\n");
    for(int i=1;i<=M;++i){
    	printf("cmd:%d %d %d, pos:%d\n",Cmds[i].op,Cmds[i].x,Cmds[i].y,Cmds[i].eidx);
	}

	printf("edge:\n");
	for(int i=1;i<=ECnt;++i){
		printf("(%d,%d,%d)\n",Edge[i].from,Edge[i].to,Edge[i].time);
	}//*/
}

void f(int idx){
    int cmd = Cmds[idx].op;
    int x = Cmds[idx].x;
    int y = Cmds[idx].y;
    int e = Cmds[idx].eidx + N;//边节点编号

    if(0==cmd){//加边
        link(x,y,e);
    }else if(1==cmd){//删边
        cut(x,e);
        cut(e,y);
    }else if(2==cmd){//查询是否连通
        puts(isConnect(x,y)?"Y":"N");
    }else{
        throw runtime_error("XXXXXX");
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    read();
    //操作
    for(int i=1;i<=M;++i){
        f(i);
    }
    return 0;
}
