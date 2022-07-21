/**
    可持久化线段树
    一共4种操作：
    C l r d:A[l...r]都增加一个d，且时间戳加1
    Q l r:求区间和
    H l r t:求历史区间和
    B t:回到过去
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 106;
#else
int const SIZE = 1E5+7;
#endif

using llt = long long;

struct _t{
    using value_t = llt;
    int left;     // 左儿子
    int right;    // 右儿子
    value_t sum;  // 保存和
    value_t lazy; // 延迟标记
}Node[SIZE*50];
int toUsed = 0;

/// 分配新节点
inline int _newNode(){
    memset(Node+(++toUsed), 0, sizeof(_t));
    return toUsed;
}

/// 分配一个新节点，内容是复制old节点
inline int _newNode(int old){
    memcpy(Node+(++toUsed), Node+old, sizeof(_t));
    return toUsed;
}

/// 建树，需要动态分配节点
void build(int &t, int s, int e){
    t = _newNode();
    if(s == e){
        cin >> Node[t].sum;
        return;
    }

    int mid = (s + e) >> 1;
    build(Node[t].left, s, mid);
    build(Node[t].right, mid+1, e);
    Node[t].sum = Node[Node[t].left].sum + Node[Node[t].right].sum;
}

/// 区间修改，保证[a,b]是[s,e]的子区间
void modify(int &t, int old, int s, int e, int a, int b, llt delta){
    /// 复制出新版本，并更新数据域
    Node[t = _newNode(old)].sum += (b - a + 1) * delta;
    
    if(a == s && e == b){ // 到头了
        Node[t].lazy += delta; //  不必更新sum
        return;     
    }        

    int mid = (s + e) >> 1;
    if(a <= mid) modify(Node[t].left, Node[old].left, s, mid, a, min(b, mid), delta);
    if(mid < b) modify(Node[t].right, Node[old].right, mid+1, e, max(a, mid+1), b, delta);
    return;
}

llt query(int t, int s, int e, int a, int b, llt lazy){
    if(a <= s && e <= b){
        return Node[t].sum + lazy * (e - s + 1);
    }

    int mid = (s + e) >> 1;
    llt ans = 0;
    if(a <= mid) ans += query(Node[t].left, s, mid, a, b, lazy+Node[t].lazy);
    if(mid < b) ans += query(Node[t].right, mid+1, e, a, b, lazy+Node[t].lazy);
    return ans;
}

int N, M;
int Time;
int Root[SIZE]; 

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    for(int kase=0;cin>>N>>M;++kase){
        build(Root[toUsed=Time=0], 1, N);
        if(kase) puts("");

        char cmd;
        for(int a,b,t,q=1;q<=M;++q){
            cin >> cmd;
            if('C' == cmd){
                cin >> a >> b >> t;
                modify(Root[Time+1], Root[Time], 1, N, a, b, t);
                ++Time;
            }else if('Q' == cmd){
                cin >> a >> b;
                llt ans = query(Root[Time], 1, N, a, b, 0);
                printf("%lld\n", ans);
            }else if('H' == cmd){
                cin >> a >> b >> t;
                llt ans = query(Root[t], 1, N, a, b, 0);
                printf("%lld\n", ans);
            }else if('B' == cmd){
                cin >> t;
                Time = t;
            }else{
                throw runtime_error("wrong cmd");
            }
        }        
    }

    return 0;
}