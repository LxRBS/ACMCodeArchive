/**
    ģ���⣬����LCT��̬ά��ͼ��ͨ��
    0: ����ߣ���֤������
    1��ɾ���ߣ���֤��
    2����ѯ�������Ƿ���ͨ

    ԭͼ��ÿ�����ÿ������LCT�о���Ϊ�����
    LCT�ϼ�¼ÿ�������ʧʱ�䣬���е�ڵ�Ϊ�����splayά��ÿ������������Ľڵ�
    �߽ڵ������ָ��������м�¼
    ��ԭ���е�ÿ�������������ֱ����x��y��e��
    0: ���������
      0.1 ���x��y��������������link(x,e),link(e,y)����
      0.2 ���x��yԭ������ͨ������xy�����ҵ������һ���ڵ㣬����e2
        ʹ��splay��ά��������ֱ�Ӳ鵽���ֵ�����e��ʱ��Ҫ����e2����do nothing
        ���򣬽�e2�г�����e����
    1: cut(x,e), cut(e,y)
    2: ֱ���ж�(x,y)�Ƿ���ͨ����
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
int const SIZE = 550000;
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
int N,M;

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
        int tt = t - N;
        cut(Edge[tt].from,t);
        cut(t,Edge[tt].to);
        //���±�
        link(x,e);
        link(e,y);
    }
}

void read(){
    //��ʼ����
    ECnt = 0;Map.clear();

    N = getUnsigned();
    M = getUnsigned();
    //�������е�ָ��
    for(int i=1;i<=M;++i){
        Cmds[i].op = getUnsigned();
        Cmds[i].x = getUnsigned();
        Cmds[i].y = getUnsigned();
        if(Cmds[i].x>Cmds[i].y) swap(Cmds[i].x,Cmds[i].y);
        //����ӱߺ�ɾ�ߵ�ʱ����
        if(0==Cmds[i].op){//�ӱ�
            Edge[++ECnt].time = M + 1;//�����ܹ��������ı�ʱ���߶���M+1
            Cmds[i].eidx = Map[make_pair(Edge[ECnt].from = Cmds[i].x,Edge[ECnt].to = Cmds[i].y)] = ECnt;
        }else if(1==Cmds[i].op){//ɾ��
            int time = Map[make_pair(Cmds[i].x,Cmds[i].y)];
            Edge[Cmds[i].eidx = time].time = i;//�����ñ���iʱ����ʧ
        }
    }
    //�����е�ڵ��ʱ��������Ϊ�����
    fill(Time+1,Time+N+1,INF);
    //���нڵ��early��ʼΪ�Լ�
    //for(int i=1;i<=N;++i)Node[i].early = i;

    //�����б��趨Ϊ���Ե�ʱ����
    //�߽ڵ���LCT�еı�ž���i+N
    for(int i=1;i<=ECnt;++i){
        Time[i+N] = Edge[i].time;
        //Node[i+N].early = i + N;
    }
    /*����
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
    int e = Cmds[idx].eidx + N;//�߽ڵ���

    if(0==cmd){//�ӱ�
        link(x,y,e);
    }else if(1==cmd){//ɾ��
        cut(x,e);
        cut(e,y);
    }else if(2==cmd){//��ѯ�Ƿ���ͨ
        puts(isConnect(x,y)?"Y":"N");
    }else{
        throw runtime_error("XXXXXX");
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    read();
    //����
    for(int i=1;i<=M;++i){
        f(i);
    }
    return 0;
}
