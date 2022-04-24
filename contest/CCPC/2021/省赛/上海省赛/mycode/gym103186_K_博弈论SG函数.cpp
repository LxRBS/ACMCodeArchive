/**
 * 一个字符串，两个人轮流取
 * 每一步可以取一个字母，也可以取两个不相同的字母。
 * 问先手的胜负。
 * 标准的SG函数，直接记忆化搜索
 * 字母的种类其实没有关系，关键是数量的构成。
*/
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

struct _t{
    vi cnt;
    void read(){
        cnt.assign(26, 0);
        char a[44];
        scanf("%s", a);
        for(char const *p=a;*p;++p){
            ++cnt[*p-'a'];
        }
        this->norm();
    }
    bool operator < (const _t &rhs)const{
        if(cnt.size() != rhs.cnt.size()) return cnt.size() < rhs.cnt.size();
        for(unsigned i=0,n=cnt.size();i<n;++i){
            if(cnt[i] != rhs.cnt[i]) return cnt[i] < rhs.cnt[i];
        }
        return false;
    }    
    void norm(){ // 归一化
        sort(cnt.begin(), cnt.end(), greater<int>());
        while(!cnt.empty() && 0 == cnt.back()) cnt.pop_back();
    }
    void output()const{
        for(auto c: cnt)cout<<c<<" ";
        cout<<endl;
    }
    _t& operator = (const _t &rhs){
        if(this != &rhs){
            cnt.assign(rhs.cnt.begin(), rhs.cnt.end());
        }
        return *this;
    }
}A[12];

map<_t, int> SG;

int sg(const _t &a){    
    if(a.cnt.empty()) return 0;
    auto it = SG.find(a);
    if(it!=SG.end()) return it->second;
    
    bitset<1000000> bit;

    /// 对当前a做第一种变化
    unsigned n = a.cnt.size();
    for(unsigned i=0;i<n;++i){
        _t tmp(a);
        if(0 == --tmp.cnt[i]){
            tmp.cnt.erase(tmp.cnt.begin()+i);
        }else{
            tmp.norm();
        }
        bit.set(sg(tmp));
    }
    /// 对当前a做第二种变化
    for(unsigned i=0;i<n-1;++i)for(unsigned j=i+1;j<n;++j){
        _t tmp(a);  
        --tmp.cnt[i];      
        --tmp.cnt[j];
        tmp.norm();
        bit.set(sg(tmp)); 
    }
    int ans = 0;
    while(bit.test(ans)) ++ans;
    return (SG.insert(it, {a, ans}))->second;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif    
    SG.insert({_t(), 0});
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        int n;
        scanf("%d", &n);
        int ans = 0;
        for(int i=0;i<n;++i){
            A[i].read();
            ans ^= sg(A[i]);
        }
        puts(ans?"Alice":"Bob");
    }
    return 0;
}
