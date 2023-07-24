/**
 * ����һ������ͼ����������Ӷ������ߣ�����ʹ��dfs��ǡ����1~N
 * ģ��һ�����ѣ�ÿһ���޷������������ȻҪ���һ���ߡ�
 * ��ÿ������ھӴ�С��������Ȼ������ջ����
 * ���Ի������رߡ�
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vector<set<int>> G;
vi Flag;

int proc(){
    int ans = 0;
    vi stack(1, 1);
    vi vec;
    while(1){
        int cur = vec.size();
        if(cur == N) break;       

        ++cur;
        while(!stack.empty() and stack.back() < cur) stack.pop_back();

        if(stack.empty() or stack.back() != cur){
            ++ans;
        }else{
            stack.pop_back();
        }
        vec.push_back(cur);
        for(auto it=G[cur].rbegin(),et=G[cur].rend();it!=et;++it){
            stack.emplace_back(*it);
        }        
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M;
        G.assign(N + 1, set<int>());
        for(int a,b,i=0;i<M;++i){
            cin >> a >> b;
            if(a == b) continue;
            G[a].insert(b);
            G[b].insert(a);
        }
        cout << proc() << endl;
    }
    return 0;
}


