/**
    n��player��m��fans��fans��player��һ��ϲ����ϵ
    Ȼ����q�в�����ÿ�в���Ϊ(x,y)
    �京���ǣ���תfan x��player y��ϲ����ϵ
    fan x��ȥ��player y�ı�����������������κ�һ��������
    1 fan xϲ��player y
    2 fan x��fan x'ϲ��ͬһ����Աy'����x'ϲ��y
    ����Ҫ��ѡ�����ɸ�player�μ�ȫ��������ʹ�����е�fan����ȥ������
    ��ÿһ��q���������ȫ�����������������Ա����

    ��Ȼ��һ������ͼ����������fanֻҪ����ͬһ����ͨ�����У�ֻѡ����һ��player����
    ��q������Ȼ�Ǽӱ���ɾ�߲���
    ����Ƕ�̬ά����ͨ�������
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

//SIZEҪ�ǵ�ӱߵ�����
int const SIZE = 1250000;
int const INF = 1000000000;

struct cmd_t{
    int op,x,y;
    int eidx;//�ñ߶�Ӧ�ı��
}Cmds[SIZE];

struct edge_t{
    int from,to;
    int time;
}Edge[SIZE];
int ECnt;

//��(x,y)��ʱ���ӳ��
map<pair<int,int>,int> Map;

int const LEFT = 0;
int const RIGHT = 1;

struct node_t{
    int parent;
    int son[2];
    int early; //����Ľڵ���
    unsigned char flip;//��0λ��ʾ��ת�ӳ�
}Node[SIZE];
int toUsed = 0;

//Timei��ʾi��ʱ����
int Time[SIZE];
int N,M,Q;

inline void _pushUp(int t){//��Ҫά��early
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
    if ( t && (Node[t].flip & 1) ){//����ת
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if(son) Node[son].flip ^= 1;

        son = Node[t].son[RIGHT];
        if(son) Node[son].flip ^= 1;

        Node[t].flip ^= 1;
    }
}
//�ж�t�Ƿ�Ϊ��splay�ĸ�
inline bool _isRoot(int t){
    int p = Node[t].parent;
    return 0==p || (Node[p].son[LEFT]!=t&&Node[p].son[RIGHT]!=t);
}
//��ȡ���У�������������
inline int _getSN(int t){
    return Node[Node[t].parent].son[RIGHT] == t;
}
//��չ����link��������p��sn��������Ϊt
inline void _link(int p,int sn,int t){
    Node[Node[t].parent=p].son[sn] = t;
}
//��ת������t�����Ǹ�
inline void _rotate(int t){
    int p = Node[t].parent;//���ڵ�
    int g = Node[p].parent;//�游�ڵ�
    int sn = _getSN(t);
    int osn = sn^1;
    //����ҪpushDown����splay��pushDown

    _link(p,sn,Node[t].son[osn]);
    Node[t].parent = g;
    if(!_isRoot(p))Node[g].son[_getSN(p)]=t;
    _link(t,osn,p);

    _pushUp(p);
}
//�Ӹ���ʼ���·��ӳٱ��
void _maintain(int t){
    if(!_isRoot(t)) _maintain(Node[t].parent);
    _pushDown(t);
}
//��չ�������ص�����
void _splay(int t){
    _maintain(t);
    while(!_isRoot(t)){
        int p = Node[t].parent;
        if(!_isRoot(p)) _getSN(t)==_getSN(p)?_rotate(p):_rotate(t);
        _rotate(t);
    }
    _pushUp(t);
}
//�Ӹ���x�γ�һ����������
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//��������
        _pushUp(x);
    }
    return t;
}
//��x��Ϊԭ���ĸ�
inline void _makeRoot(int x){
    _access(x);
    _splay(x);
    Node[x].flip ^= 1; //��ת���
}
//��ȡx�������ĸ��ڵ�
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    _splay(x);
    return x;
}
//��child��parent���ӽڵ�
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;
}
//��child��parent��������
inline void cut(int parent,int child){
    _makeRoot(parent);
    _access(child);
    _splay(child);

    //��ͨ��LCTcut�Ǳ�֤���ӣ�ֱ��cut����
    //�˴���Ҫ�ж�child��parent�Ƿ�ֱ��
    //��Ϊֻ���г���ڵ�ͱ߽ڵ㣬������LCT�ϱ�Ȼ������
    if(Node[child].son[LEFT]==parent){
        Node[child].son[LEFT] = Node[Node[child].son[LEFT]].parent = 0;
        _pushUp(child);
    }

}
inline bool isConnect(int x,int y){
    return x == y || _getRoot(x) == _getRoot(y);
}

//���߲�����xy�ǵ�ڵ㣬e�Ǳ߽ڵ�
inline void link(int x,int y,int e){
    //���ȼ����ͨ��
    if(!isConnect(x,y)){
        link(x,e);
        link(e,y);
        return;
    }

    //ԭ������ͨ�������γ�һ����
    _makeRoot(x);_access(y);_splay(y);
    //ȡ�����ϵ�ʱ������ڵ�
    int t = Node[y].early;
    if(Time[e]>Time[t]){
        //ȡ���ߵı��
        int tt = t - N - M;//���Ǹĳ�N+M�ˣ����ִ���
        cut(Edge[tt].from,t);
        cut(t,Edge[tt].to);
        //���±�
        link(x,e);
        link(e,y);
    }
}

int First;
int CmdCnt = 0;

//��Ա��ǰ��fans�ں�
set<pair<int,int> > Bian;

void read(){
    //��ʼ����
    ECnt = 0;Map.clear();
    Bian.clear();

    N = getUnsigned();
    M = getUnsigned();
    Q = getUnsigned();

    //����fans
    for(int a,i=1;i<=N;++i){
        int n = getUnsigned();
        while(n--){
            a = getUnsigned();
            //i��a+N��һ����
            Edge[++ECnt].time = Q + 1;//�����ܹ��������ı�ʱ���߶���Q+1��ע������ⲻ��M+1
            ++CmdCnt;//��1��ʼ����
            Cmds[CmdCnt].op = 0;//�ӱ߲���
            Cmds[CmdCnt].eidx = Map[make_pair(Edge[ECnt].from=Cmds[CmdCnt].x=i,Edge[ECnt].to=Cmds[CmdCnt].y=a+N)]=ECnt;
            Bian.insert(make_pair(i,a));
        }
    }

    First = CmdCnt;

    //�������е�ָ��
    for(int y,x,i=1;i<=Q;++i){
        ++CmdCnt;
        Cmds[CmdCnt].y = ( y = getUnsigned() ) + N;//fans�ı��Ҫ��N
        Cmds[CmdCnt].x = x = getUnsigned();

        if(Bian.find(make_pair(x,y))!=Bian.end()){//���ԭ�����бߣ�����ɾ�߲���
            Bian.erase(make_pair(x,y));
            Cmds[CmdCnt].op = 1;
            int time = Map[make_pair(Cmds[CmdCnt].x,Cmds[CmdCnt].y)];
            Edge[Cmds[CmdCnt].eidx = time].time = i;//�����ñ���iʱ����ʧ
        }else{//�ӱ߲���
            Bian.insert(make_pair(x,y));
            Cmds[CmdCnt].op = 0;
            Edge[++ECnt].time = Q+1;//�����ܹ��������ı�ʱ���߶���Q+1
            Cmds[CmdCnt].eidx = Map[make_pair(Edge[ECnt].from = Cmds[CmdCnt].x,Edge[ECnt].to = Cmds[CmdCnt].y)] = ECnt;
        }
    }
    //�����е�ڵ��ʱ��������Ϊ�����
    fill(Time+1,Time+N+M+1,INF);//N+M!!!
    //���нڵ��early��ʼΪ�Լ�
    //for(int i=1;i<=N;++i)Node[i].early = i;

    //�����б��趨Ϊ���Ե�ʱ����
    //�߽ڵ���LCT�еı�ž���i+N+M
    for(int i=1;i<=ECnt;++i){
        Time[i+N+M] = Edge[i].time;//ע�������N+M
    }
    /*����
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
    int c0 = M;//��¼����Ϊ0��Fans������
    int d0 = N;//��¼����Ϊ0��player������
    int ans = N+M;//��ͨ�������

    for(int i=1;i<=First;++i){//�ӱ߲��������ûش�
        int x = Cmds[i].x;
        int y = Cmds[i].y;
        int e = Cmds[i].eidx + N + M;
        if(!isConnect(x,y)){//���xyԭ������ͨ
            --ans;
        }
        link(x,y,e);

        if(0==Deg[x]++) --d0;
        if(0==Deg[y]++) --c0;
    }

    //printf("cc��%d\n",ans);
    for(int i=First+1;i<=CmdCnt;++i){//������
        int cmd = Cmds[i].op;
        int x = Cmds[i].x;
        int y = Cmds[i].y;
        int e = Cmds[i].eidx + N + M;//�߽ڵ���

        if(0==cmd){//�ӱ�
            if(!isConnect(x,y)) --ans;
            link(x,y,e);

            if(0==Deg[x]++) --d0;
            if(0==Deg[y]++) --c0;
        }else if(1==cmd){//ɾ��
            cut(x,e);
            cut(e,y);

            if(!isConnect(x,y)) ++ans;

            if(0==--Deg[y]) ++c0;
            if(0==--Deg[x]) ++d0;
        }else{
            throw runtime_error("XXXXXXXXX");
        }

        if(c0){//�����fans��Ϊ0����û�д�
            puts("-1");
        }else{
            printf("%d\n",ans-d0);
        }
        //printf("after q: %d %d\n",i-First,ans);
        //dispNode(N+M+ECnt);
    }
    return 0;
}
