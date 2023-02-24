/**
 * multiset，三种操作：插入操作，多次删除操作，查询操作。
 * 直接用multiset即可
 */
#include <bits/stdc++.h>
using namespace std;

using set_t = multiset<int>;

int Q;
set_t Set;

 
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> Q;
    for(int op,x,c,q=1;q<=Q;++q){
        cin>>op;
        if(1 == op){
            cin >> x;
            Set.insert(x);
        }else if(2 == op){ 
            cin >> x >> c;
            auto p = Set.equal_range(x);
            auto e = p.first;
            while(c > 0 && p.second != e) ++e, --c;
            Set.erase(p.first, e);
        }else{
            cout<<(*--Set.end() - *Set.begin())<<endl;
        }
    }
    return 0;
}