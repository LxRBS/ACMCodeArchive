/**
    围棋，初始局面只有黑棋。问只走白棋，最多能吃掉多少黑棋
    首先求出黑棋连通块与边界，然后将其填满
*/
#include <bits/stdc++.h>
using namespace std;

string int2string(int n){
    stringstream ss;
    ss<<n;
    return ss.str();
}

typedef pair<int, int> pii;
typedef vector<pii> vpii;
struct pair_hash{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};
typedef unordered_set<pii, pair_hash> hashpii;

#define mp make_pair
#define pb push_back
#define fi first
#define se second

int const DR[] = {0, 0, 1, -1};
int const DC[] = {1, -1, 0, 0};

int F[1010][1010];  // Fij表示ij位置上的黑棋的连通块序号
char A[1010][1010];
vector<int> Qi2Hei[1010][1010]; // 首先ij是气，然后Qi2Hei[i][j]表示该气影响哪几块黑棋，最多4块
int N, HCnt;

vector<vpii> Heiqi; // Heiqi[i]表示第i个黑棋的连通块
vector<hashpii> Qi; // Qi[i]表示第个黑棋连通块周围的气的位置

/// 从r、c位置搜索黑棋的连通块，记录在heiqi里面
void dfs(int r, int c, vpii&heiqi, hashpii&qi, const int index){
    /// 该位置肯定是黑棋
    //cout<<r<<" "<<c<<endl;
    heiqi.pb(mp(r, c));
    F[r][c] = index;
    for(int nr,nc,i=0;i<4;++i){
        nr = r + DR[i];
        nc = c + DC[i];
        if(1<=nr&&nr<=N&&1<=nc&&nc<=N){
            if('O'==A[nr][nc]){
                if(0==F[nr][nc]){
                    dfs(nr, nc, heiqi, qi, index);
                }
            }else if('.'==A[nr][nc]){
                qi.insert(mp(nr, nc));
            }else{
                throw runtime_error("wrong XXOO "+int2string(nr)+" "+int2string(nc)+" "+int2string((int)A[nr][nc]));
            }
        }
    }
}

bool Flag[1010][1010];
/// Bai[i]表示第i个黑棋连通块的气块
/// Bai[i][j]表示第i个黑棋连通块的第j个气块
/// Bai[i][i][k]表示第i个黑棋连通块的第j个气块中的第k个位置
vector<vector<vpii> >Bai;

/// 深搜与rc位置连通的同属于index黑块的气
void dfsQi(int r, int c, vpii&bai, hashpii&flag){
    for(int nr, nc, i=0;i<4;++i){
        nr = r + DR[i];
        nc = c + DC[i];
        pii pp(nr, nc);
        hashpii::iterator it;
        if(1<=nr&&nr<=N&&1<=nc&&nc<=N&&'.'==A[nr][nc]&&(it=flag.find(pp))!=flag.end()){
            flag.erase(it);
            bai.pb(pp);
            dfsQi(nr, nc, bai, flag);
        }
    }
}

/// 整理第index块黑棋连通块的气
void zhengli(int index){
    /// 初始化
    const vpii &hei = Heiqi[index];
    const hashpii &qi = Qi[index];
    vector<vpii> &bai = Bai[index];
    hashpii flag(qi);

    for(auto pp: qi){  // 对气里面的每一个位置
        if(flag.find(pp)==flag.end()) continue;

        /// 找到一个新的连通的气
        bai.pb(vpii());
        flag.erase(pp);
        bai[bai.size()-1].pb(pp);
        dfsQi(pp.fi, pp.se, *--bai.end(),flag);
    }

    for(auto vec: bai){
        for(auto pp: vec){
            Qi2Hei[pp.fi][pp.se].pb(index);
        }
    }
}

void disp(){
    int n = Heiqi.size() - 1;
    cout<<"black total: "<<n<<endl;
    for(int i=1;i<=n;++i){
        cout<<"black "<<i<<":";
        for(auto pp: Heiqi[i]){
            cout<<"("<<pp.first<<", "<<pp.se<<")";
        }
        cout<<endl;
        /// 气
        cout<<"qi: "<<endl;
        for(auto pp: Qi[i]){
            cout<<"("<<pp.first<<", "<<pp.se<<")";
        }
        cout<<endl;
        /// 整理完毕的气
        cout<<"after zhengli: "<<Bai[i].size()<<endl;
        int k = 0;
        for(auto vec: Bai[i]){
            cout<<++k<<":";
            //*
            for(auto pp: vec){
                cout<<"("<<pp.first<<", "<<pp.se<<")";
            }//*/
            cout<<endl;
        }
    }
    /// 单独输出气
    cout<<"Qi2Hei:"<<endl;
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)if('.'==A[i][j]&&!Qi2Hei[i][j].empty()){
        cout<<"("<<i<<", "<<j<<"):";
        for(auto index: Qi2Hei[i][j]){
            cout<<" "<<index;
        }
        cout<<endl;
    }
}

/// 判断rc位置是一个相对于index黑块的气是一个活点
inline bool isOKLive(int nr, int nc, int index){
    if(1<=nr&&nr<=N&&1<=nc&&nc<=N&&'.'==A[nr][nc]){
        for(auto id: Qi2Hei[nr][nc]){
            if(id==index){
                return false;
            }
        }
        return true;
    }
    return false;
}

/// 判断整个气块相对于index黑棋是一个活的
inline bool isOKLive(const vpii&qikuai, int index){
    for(auto pp: qikuai){ // 对每一个位置
        for(int nr, nc, i=0;i<4;++i){
            nr = pp.fi + DR[i];
            nc = pp.se + DC[i];
            if(isOKLive(nr, nc, index)){ // 整个气块都是活的
                return true;
            }
        }
    }
    return false;
}

/// 判断第index个黑棋是否被吃掉
/// 如果该黑棋块的所有气块不会被吃掉，该黑棋就能被围杀
bool isOK(int index){
    vector<vpii> const&qikuais = Bai[index];
    int cnt = 0;
    for(auto qikuai: qikuais){ // 对每一个气块检测有没有自己的气
        if(!isOKLive(qikuai, index)){
            if(++cnt>1) return false;
        }
    }
    return true;
}

bool QFlag[700010];
int bfs(){
    queue<int> q;
    for(int i=1;i<=HCnt;++i){
        if(isOK(i)){  // 首先将死定了的黑棋加进去
            q.push(i);
            QFlag[i] = true;
        }
    }

    int ans = 0;
    while(!q.empty()){
        int h = q.front();q.pop();
        ans += Heiqi[h].size();

        /// 首先将第h块黑棋全部变成气
        for(auto pp: Heiqi[h]){
            A[pp.fi][pp.se] = '.';
        }

        /// 再对第h块黑棋的每个气的共同的黑棋块进行判断入队
        for(auto pp: Qi[h]){
            for(auto index: Qi2Hei[pp.fi][pp.se]){
                if(!QFlag[index]&&isOK(index)){
                    q.push(index);
                    QFlag[index] = true;
                }
            }
        }
    }

    return ans;
}

/// 在CFGYM上需要手动扩栈，否则过不了
/// 同时在C++11下有时能过有时不能过，在C++17下可以过
/// 牛客网不需要，可以直接过
#define __STACK__
//#undef __STACK__

int main(){
    //freopen("1.txt","r",stdin);
#ifdef __STACK__  
    long long __ss = 256<<20;
    char *p = (char*)malloc(__ss) + __ss;
#if (defined __WIN64) or (defined _unix)
    __asm__("movq %0, %%rsp\n" :: "r"(p));
#else
    __asm__("movl %0, %%esp\n" :: "r"(p));
#endif
#endif

    scanf("%d", &N);
    for(int i=1;i<=N;++i)scanf("%s", A[i]+1);

    Heiqi.pb(vpii()); // 建一个空的
    Qi.pb(hashpii());

    /// 找出所有的黑棋连通块和气
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        if('.'==A[i][j]||F[i][j]) continue;
        /// 找到一个新的连通块
        Heiqi.pb(vpii());
        Qi.pb(hashpii());
        dfs(i, j, *--Heiqi.end(), *--Qi.end(), Heiqi.size()-1);
    }
    //disp();

    /// 再把每个黑块的棋整理好
    HCnt = Heiqi.size() - 1;
    Bai.assign(HCnt+1, vector<vpii>());
    if(HCnt>=N*N/2){
        printf("0\n");
        return 0;
    }

    for(int i=1;i<=HCnt;++i){
        zhengli(i);
    }
    //disp();

    cout<<bfs()<<endl;
#ifdef __STACK__
    exit(0);
#else
    return 0;
#endif // __STACK__
}
