/**
 * ����һ�������������ߣ��Լ����ڵ�Ķ�����
 * ����һ�����ߵķ�����ʹ�����õ�һ���Ϸ���������������������������-1
 * ���ȼ�����б��Ƿ�Ͷ���ì�ܣ�Ȼ��������ʣ�����Ҫ�������
 * ��������ͨ���Ϊ�����࣬ʣ�����Ϊ1�ģ��Լ�ʣ���������1��
 * Ȼ��ÿһ�θ���һ���������ӣ�����ע��ɾ��
 * ����Ȼʣ����������Ϊ1�ĵ㣬����Ϊ������
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 17;
#else
int const SIZE = 2e5+5;
#endif

int Father[SIZE];
void init(int n){for(int i=1;i<=n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)]=find(x);}

typedef vector<int> vi;
typedef unordered_set<int> si;
typedef pair<int, int> pii;

int N, M;
vi Deg;
vector<pii> Ans;
vi One; // ���ֶ�Ϊ1�Ľڵ�
unordered_map<int, vi> Two; // ����ʾFather�� si�洢����ͨ������нڵ�

bool isOne(decltype(Two.end())it){
    if(1==it->second.size() && 1 == Deg[it->second.front()]){
        return true;
    }
    return false;
}

void proc(decltype(Two.end())it, decltype(One.end())jt){
    int a = it->second.back();
    assert(Deg[a] >= 1);
    int b = *jt;
    assert(1 == Deg[b]);
    assert(find(a) != find(b));
    
    Ans.emplace_back(a, b);
    unite(a, b); --Deg[a]; --Deg[b];

    One.erase(jt);
    if(0 == Deg[a]) it->second.pop_back();
    if(isOne(it)){
        One.push_back(it->second.front());
        Two.erase(it);
    }
}

void proc(){
    for(int p,i=1;i<=N;++i){
        p = find(i);
        if(Deg[i]){
            Two[p].push_back(i);
        }
    }
    /// �����ж�Ϊ1����ͨ���ӵ�One�У���ʱ����ͨ��϶�ֻʣһ����δ����
    for(auto it=Two.begin();it!=Two.end();){
        if(isOne(it)){
            One.push_back(it->second.front());
            it = Two.erase(it);
        }else{
            ++it;
        }
    }
    /// ÿһ���ҵ�һ��One��һ��Two��������
    while(!Two.empty()){
        if(One.empty()){
            return (void)puts("-1");
        }
        /// ��Two�����ҵ�һ���� One���������һ��
        auto it = Two.begin();
        auto jt = --One.end();
        proc(it, jt);
    }
    /// OneӦ��ֻʣ������
    if(2 != One.size()) return (void)puts("-1");

    int a = One.front(), b = One.back();
    assert(find(a) != find(b));
    --Deg[a]; --Deg[b];
    assert(0 == Deg[a] && 0 == Deg[b]);
    unite(a, b);
    Ans.emplace_back(a, b);

    for(const auto &p: Ans){
        printf("%d %d\n", p.first, p.second);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    Deg.assign((N=getInt())+1, 0);
    M = getInt();
    init(N);

    for(int i=1;i<=N;++i) Deg[i] = getInt();

    bool flag = false;
    for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
        if(find(a) == find(b)) flag = true;
        if(--Deg[a] < 0) flag = true;
        if(--Deg[b] < 0) flag = true;
        unite(a, b);
    }
    if(flag) return puts("-1"), 0;
    proc();
    return 0;
}
