/**
    �ɳ־û��߶���
    һ��4�ֲ�����
    C l r d:A[l...r]������һ��d����ʱ�����1
    Q l r:�������
    H l r t:����ʷ�����
    B t:�ص���ȥ
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
    int left;     // �����
    int right;    // �Ҷ���
    value_t sum;  // �����
    value_t lazy; // �ӳٱ��
}Node[SIZE*50];
int toUsed = 0;

/// �����½ڵ�
inline int _newNode(){
    memset(Node+(++toUsed), 0, sizeof(_t));
    return toUsed;
}

/// ����һ���½ڵ㣬�����Ǹ���old�ڵ�
inline int _newNode(int old){
    memcpy(Node+(++toUsed), Node+old, sizeof(_t));
    return toUsed;
}

/// ��������Ҫ��̬����ڵ�
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

/// �����޸ģ���֤[a,b]��[s,e]��������
void modify(int &t, int old, int s, int e, int a, int b, llt delta){
    /// ���Ƴ��°汾��������������
    Node[t = _newNode(old)].sum += (b - a + 1) * delta;
    
    if(a == s && e == b){ // ��ͷ��
        Node[t].lazy += delta; //  ���ظ���sum
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