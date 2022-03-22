#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cassert>
#include<set>
#include<complex>
#include<numeric>
#include<functional>
#include<unordered_map>
#include<unordered_set>
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
const int INF=1<<30;
const LL MAX=1e9+7;

void array_show(int *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%d%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(LL *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%lld%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(vector<int> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%d%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
void array_show(vector<LL> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%lld%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
template<typename T> ostream& operator<<(ostream& os,const vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++){
        if(i)os<<" ";
        os<<v1[i];
    }
    return os;
}
template<typename T1,typename T2> ostream& operator<<(ostream& os,const pair<T1,T2>& p){
    os<<p.first<<" "<<p.second;
    return os;
}
template<typename T> istream& operator>>(istream& is,vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++)is>>v1[i];
    return is;
}
template<typename T1,typename T2> istream& operator>>(istream& is,pair<T1,T2>& p){
    is>>p.first>>p.second;
    return is;
}

class Lca{
    // use method
    // 1. (constructer) Lca lca(n) or lca.init(n)
    // 2. lca.connect(a,b) ((a,b) \in path)
    // 3. lca.reload()
    // lca.lca(a,b): lower common ancestor
private:
    const int M=20;
    int nest=0;
    vector<vector<int>> path;
    vector<vector<int>> par;
    vector<int> depth,max_depth;
    
    void init(int n){
        path.assign(n,vector<int>());
        par.assign(n,vector<int>(M,-1));
        depth.assign(n,-1);
    }

    void create_depth(int pos,int bef,int d){
        if(depth.at(pos)!=-1)return;
        depth.at(pos)=d;
        int p=bef;
        for(int i=0;i<M;i++){
            if(p==-1)break;
            par.at(pos).at(i)=p;
            p=par.at(p).at(i);
        }
        for(auto to:path.at(pos)){
            if(bef==to)continue;
            create_depth(to,pos,d+1);
            max_depth[pos]=max(max_depth[pos],max_depth[to]+1);
        }
    }

public:
    
    Lca(int n){
        init(n);
    }
    Lca(int n,int nes){
        nest=nes;
        init(n);
    }

    int get_depth(int pos){
        return depth.at(pos);
    }

    int get_max_depth(int pos){
        return max_depth.at(pos);
    }
    
    void connect(int a,int b){
        path.at(a).push_back(b);
        path.at(b).push_back(a);
    }

    void reload(){
        int n=path.size();
        par.assign(n,vector<int>(M,-1));
        depth.assign(n,-1);
        max_depth.assign(n,0);
        create_depth(nest,-1,0);
    }

    int check_parent(int pos,int dis){
        assert(0<=dis && dis<=depth[pos]);
        if(dis==0)return pos;
        for(int i=M-1;i>=0;i--){
            if(dis<(1<<i))continue;
            dis-=1<<i;
            pos=par.at(pos).at(i);
        }
        return pos;
    }

    int lca(int a,int b){
        if(depth.at(a)<depth.at(b))swap(a,b);
        a=check_parent(a,depth.at(a)-depth.at(b));
        if(a==b)return a;
        for(int i=M-1;i>=0;i--){
            if(par.at(a).at(i)!=par.at(b).at(i)){
                a=par.at(a).at(i);
                b=par.at(b).at(i);
            }
        }
        return par.at(a).at(0);
    }

    int distance(int a,int b){
        return depth.at(a)+depth.at(b)-2*depth.at(lca(a,b));
    }
};



namespace sol{
    int n,m;
    vector<vector<int>> path;
    vector<unordered_set<int>> diss;
    vector<int> va;

    void get_nests_dfs(int pos,int d,int par,int& max_d,int& max_pos){
        if(max_d<d)max_d=d,max_pos=pos;
        for(auto to:path[pos]){
            if(to==par)continue;
            get_nests_dfs(to,d+1,pos,max_d,max_pos);
        }
    }

    P get_nests(){
        int s1,s2;
        int a=-1;
        get_nests_dfs(0,0,-1,a,s1);
        a=-1;
        get_nests_dfs(s1,0,-1,a,s2);
        return {s1,s2};
    }

    void create_map_dfs(int pos,int par){
        for(auto to:path[pos]){
            if(to==par)continue;
            create_map_dfs(to,pos);
            va[pos]=max(va[pos],va[to]+1);
            diss[pos].insert(va[to]+1);
        }
    }

    void create_map_dfs2(int pos,int par,int d){
        if(par!=-1)diss[pos].insert(d);
        int a;
        vector<int> v1={d-1};
        for(auto to:path[pos]){
            if(to==par)continue;
            v1.push_back(va[to]);
        }
        sort(v1.rbegin(),v1.rend());
        int p=v1[0],q=-1;
        if(2<=v1.size())q=v1[1];
        v1.clear();
        for(auto to:path[pos]){
            if(to==par)continue;
            if(va[to]==p)a=q;
            else a=p;
            create_map_dfs2(to,pos,a+2);
        }
    }

    void create_map(){
        int a;
        va.assign(n,0);
        diss.resize(n);
        create_map_dfs(0,-1);
        create_map_dfs2(0,-1,0);
    }

    int calc(Lca& lca,int x,int d){
        int s=d;
        int y;
        if(d>=3){
            y=lca.check_parent(x,(d-3)/2);
            s=max(s,d-(d-3)/2+lca.get_max_depth(y));
        }
        if(d%2==1)return s;
        if(s>=d+1)return s;
        y=lca.check_parent(x,d/2-1);
        if(diss[y].find(d/2)!=diss[y].end())return d+1;
        return d;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        int nest1,nest2;
        int s;
        P pa;
        cin>>n>>m;
        vector<P> vp;
        path.resize(n);
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            vp.push_back({a,b});
            path[a].push_back(b);
            path[b].push_back(a);
        }
        pa=get_nests();
        nest1=pa.first,nest2=pa.second;
        Lca l1(n,nest1),l2(n,nest2);
        for(i=0;i<n-1;i++){
            a=vp[i].first,b=vp[i].second;
            l1.connect(a,b);
            l2.connect(a,b);
        }
        l1.reload(),l2.reload();
        create_map();

        for(i=0;i<m;i++){
            cin>>a>>b;
            a--;
            if(l1.get_depth(a)>l2.get_depth(a))s=calc(l1,a,b);
            else s=calc(l2,a,b);
            cout<<s<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}