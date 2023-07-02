/**
 * 给定一个数的集合，三种操作：
 * 1. 插入x
 * 2. 删除x
 * 3. 问当前集合中两两异或能得到的最小值
 * 异或和最小有一个性质：某个数x与越近的数异或，得到的结果越小。
 * 考虑01字典树，就可以大致明了这个性质
 * 也就是说假设有升序排列的{a,b,c,d}的4个数，
 * 只需要查看{ab,bc,cd}即能找到两两异或最小
 * 于是对于第3个操作，无需求所有两两之和，只需要求相邻之异或即可
 * 使用两个multiset，一个维护x，一个维护相邻之异或即可
 */
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int Q;

multiset<int> Origin;
multiset<int> Ans;

void insert(int x){
    auto it = Origin.insert(x);
    auto prev = Origin.end();
    auto next = Origin.end();

    if(it != Origin.begin()) --(prev = it);
    if(it != --Origin.end()) ++(next = it);

    if(prev != Origin.end() and next != Origin.end()) {
        auto tt = Ans.find(*prev ^ *next);
        assert(tt != Ans.end());
        Ans.erase(tt);
    }

    if(prev != Origin.end()){
        Ans.insert(*prev ^ x);
    }

    if(next != Origin.end()){
        Ans.insert(*next ^ x);
    }
}

void remove(int x){
    auto it = Origin.find(x);
    assert(it != Origin.end());

    auto prev = Origin.end();
    auto next = Origin.end();   

    if(it != Origin.begin()) --(prev = it);
    if(it != --Origin.end()) ++(next = it);

    if(prev != Origin.end()){
        auto tt = Ans.find(*prev ^ x);
        assert(tt != Ans.end());
        Ans.erase(tt);      
    }

    if(next != Origin.end()){
        auto tt = Ans.find(*next ^ x);
        assert(tt != Ans.end());
        Ans.erase(tt);   
    }         

    if(prev != Origin.end() and next != Origin.end()) {
        Ans.insert(*prev ^ *next);    
    }   

    Origin.erase(it); 
}

int ask(){
    assert(! Ans.empty());
    return *Ans.begin();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Q;
    for(int cmd,x,q=1;q<=Q;++q){
        cin >> cmd;
        switch(cmd){
            case 1:{
                cin >> x;
                insert(x);
            }break;
            case 2:{
                cin >> x;
                remove(x);
            }break;
            case 3:{
                cout << ask() << endl;
            }break;
            default: throw runtime_error("XX");
        }
    }
    return 0;
}