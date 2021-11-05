#include <bits/stdc++.h>
using namespace std;

string A,B;
multimap<string,string> Rules;

struct _t{
    string s;
    int step;
    _t(string const&a,int b):s(a),step(b){}
};
int bfs(){
    if(A==B) return 0;

    queue<_t> q;
    q.push(_t(A,0));
    while(1){
        _t u = q.front();
        q.pop();
        if(u.step>10) return -1;

        for(map<string,string>::iterator it=Rules.begin();it!=Rules.end();++it){
            //检查该规则是否为子串，注意可能匹配多次
            string::iterator start = u.s.begin();
            while(1){
                start = search(start,u.s.end(),it->first.begin(),it->first.end());
                if(start!=u.s.end()){//替换
                    _t v(u.s,u.step+1);
                    string::iterator t = start-u.s.begin()+v.s.begin();
                    t = v.s.erase(t,t+it->first.length());
                    v.s.insert(t,it->second.begin(),it->second.end());
                    if(v.s==B) return v.step;
                    q.push(v);
                    ++start;
                }else{
                    break;
                }
            }
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    cin>>A>>B;
    string a,b;
    while(cin>>a>>b){
        Rules.insert(make_pair(a,b));
    }
    int ans = bfs();
    if(-1==ans)printf("NO ANSWER!\n");
    else printf("%d\n",ans);
    return 0;
}
