/**
    2种操作：
    1操作：给定y和最多3个位置，目标是ai1+ai2+ai3==y
    2操作：位置x上增加y，该操作后，看有哪些1操作完成了目标
    强制在线
    对每一个节点，建立一个最小堆，用于保存(目标, 序号)
    对某个1操作，假设其目标是t，一共3个位置，假设分别是p1,p2,p3
    则将(t/3, idx)塞入3个堆中
    对某个2操作，假设其增加的数量为y，则检查对应堆，凡是达到目标的均取出
    假设取出的数据为(t, idx)，然后更新idx的目标，再将剩下的分成3份，再塞到相应的堆中
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int const SIZE = 200010;

typedef long long int llt;
typedef pair<int,int> pii;
typedef pair<llt,pii> plp;
typedef pair<llt,int> pli;
typedef priority_queue<pli, vector<pli>, greater<pli> > pliq;

bool Finished[SIZE];//第i个操作是否已经完成
llt Level[SIZE];//每个位置的数值
int Goal[SIZE];
vector<int> Pos[SIZE]; //1操作对应的3个位置
vector<llt> Prev[SIZE];//1操作对应的3个位置的更新前的数值
pliq Q[SIZE];
vector<int> Ans;

//操作1
void f1(int idx,int goal, int cnt, int const pos[]){
    Goal[idx] = goal;
    Pos[idx].assign(pos,pos+cnt);
    //拆成cnt份，塞到队列中
    int left = (goal + cnt - 1) / cnt;
    for(int p,i=0;i<cnt;++i){
        p = pos[i];
        Q[p].push(pli({Level[p]+left, idx}));
        Prev[idx].push_back(Level[p]);
    }
}

//操作2，pos位置增加value
void f2(int pos,int value){
    //相应位置增加value
    Level[pos] += value;

    pliq& q = Q[pos];
    pli u;
    while(!q.empty()){
        u = q.top();
        if(u.fi>Level[pos]) break;

        q.pop();
        if(Finished[u.se]) continue;

        //检查3个位置
        bool b = false;
        vector<int>const& vec = Pos[u.se];
        for(unsigned i=0,n=vec.size();i<n;++i){
            Goal[u.se] -= Level[vec[i]] - Prev[u.se][i];
            if(Goal[u.se]<=0){
                b = Finished[u.se] = true;
                Ans.push_back(u.se);
                break;
            }
            Prev[u.se][i] = Level[vec[i]];
        }
        if(b) continue;

        //如果仍然未完成,将剩下的目标塞到队列中
        int n = vec.size();
        int left = (Goal[u.se] + n - 1) / n;
        for(auto p: vec){
            Q[p].push(pli({Level[p]+left, u.se}));
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();

    int cnt = 0;
    int last = 0;
    int a[3];
    for(int x,y,k,cmd,qi=1;qi<=m;++qi){
        if(3==qi){
            int x=55;
        }
        if(1==(cmd = getUnsigned())){
            y = getUnsigned() ^ last;
            k = getUnsigned();
            for(int i=0;i<k;++i){
                a[i]=getUnsigned()^last;
            }

            //执行操作1
            f1(++cnt, y, k, a);

        }else{
            x = getUnsigned() ^ last;
            y = getUnsigned() ^ last;

            Ans.clear();
            f2(x, y);
            printf("%d", last = (int)Ans.size());
            sort(Ans.begin(),Ans.end());
            for(auto i: Ans)printf(" %d", i);
            printf("\n");
        }
    }
    return 0;
}
