/**
   就是判断二分图，染色即可。
   根据样例，孤立点应该返回false
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

#define pb push_back

int N,M,X,Y;
vector<int> Graph[1010];
int Good[1010],Bad[1010];
int Flag[1010];

bool f(){
    fill(Flag,Flag+N+1,0);

    queue<int> q;
    for(int i=1;i<=X;++i){
        Flag[Good[i]] = 1;
        q.push(Good[i]);
    }
    for(int i=1;i<=Y;++i){
        Flag[Bad[i]] = 2;
        q.push(Bad[i]);
    }

    while(!q.empty()){
        int h = q.front();q.pop();

        int fh = Flag[h];
        for(auto v: Graph[h]){
            if(Flag[v]){
                if(Flag[v]==fh) return false;
            }else{
                Flag[v] = 1==fh?2:1;
                q.push(v);
            }
        }
    }
    for(int i=1;i<=N;++i)if(!Flag[i]){
        //孤立点返回false，按照样例
        if(Graph[i].empty()) return false;
        //否则随便染一个颜色
        Flag[i] = 1;
        q.push(i);
        while(!q.empty()){
            int h = q.front();q.pop();

            int fh = Flag[h];
            for(auto v: Graph[h]){
                if(Flag[v]){
                    if(Flag[v]==fh) return false;
                }else{
                    Flag[v] = 1==fh?2:1;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while(4==scanf("%d%d%d%d",&N,&M,&X,&Y)){
        for(int i=1;i<=N;++i)Graph[i].clear();

        for(int a,b,i=0;i<M;++i){
            a = getUnsigned();
            b = getUnsigned();
            Graph[a].pb(b);
            Graph[b].pb(a);
        }

        for(int i=1;i<=X;++i)Good[i]=getUnsigned();
        for(int i=1;i<=Y;++i)Bad[i]=getUnsigned();

        puts(f()?"YES":"NO");
    }
    return 0;
}
