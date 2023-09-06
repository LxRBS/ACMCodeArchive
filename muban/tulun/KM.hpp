struct Match_KM{

using weight_t = long long int;

/// 邻接矩阵，但不是一般图的邻接矩阵
/// g[a][b] 表示从a到b有一条边，权值为g[a][b]
/// a和b分属A部和B部，编号从1开始
vector<vector<weight_t>> g;

/// KM要求两边的点数一致，传max(NA, NB)即可
/// 最大权匹配只需要初始化为0即可，相当于添加虚边
/// 完美匹配只需要初始为-INF，相当于该边不存在
void init(int n){
    // g.assign(n + 1, vector<weight_t>(n + 1, 0));
    g.assign(n + 1, vector<weight_t>(n + 1, -inf()));
}

void mkDiEdge(int a, int b, weight_t c=0){
    if(g[a][b] < c) g[a][b] = c;
}

weight_t KM(){
    int n = g.size() - 1;
    linka.assign(n + 1, 0);
    linkb.assign(n + 1, 0);
    labela.assign(n + 1, 0);
    labelb.assign(n + 1, 0);
    flaga.assign(n + 1, 0);
    flagb.assign(n + 1, 0);
    slack.assign(n + 1, 0);
    q.assign(n + 1, 0);
    pre.assign(n + 1, 0);

    for(int i=1;i<=n;++i) labela[i] = *max_element(g[i].begin(), g[i].end());

    for(int i=1;i<=n;++i) bfs(i);

    weight_t ret = 0;
    for(int i=1;i<=n;++i) ret += g[i][linka[i]];
    return ret;
}

void bfs(int s){
    fill(slack.begin(), slack.end(), inf());
    fill(flaga.begin(), flaga.end(), 0);
    fill(flagb.begin(), flagb.end(), 0);

    int n = slack.size() - 1;
    flagb[q[head = 0] = s] = tail = 1;
    while(1){
        weight_t d;
        while(head < tail){
            for(int i=1,j=q[head++];i<=n;++i){
                if(not flaga[i] and (d = labela[i] + labelb[j] - g[i][j]) <= slack[i]){
                    if(pre[i] = j, d) slack[i] = d;
                    else if(not check(i)) return; 
                }
            }
        }

        d = inf();
        for(int i=1;i<=n;++i)if(not flaga[i] and slack[i] < d) d = slack[i];
        for(int i=1;i<=n;++i){
            if(flaga[i]) labela[i] += d;
            else slack[i] -= d;
            if(flagb[i]) labelb[i] -= d;
        }
        for(int i=1;i<=n;++i)if(not flaga[i] and not slack[i] and not check(i)) return;
    }
    return;
}

bool check(int u){
    if(flaga[u] = 1, linka[u]) return flagb[q[tail++] = linka[u]] = 1;
    while(u) swap(u, linkb[linka[u] = pre[u]]);
    return false;
}

static weight_t inf(){
    static const weight_t INF = 0x7F8F9FAFBFCFDFEF;
    return INF;
}

/// 如果g[i][linka[i]] == 0则该点其实没有匹配
vi linka; // linka[i]就是与Ai匹配的点，即B部中的编号
vi linkb; // linkb[i]就是与Bi匹配的点，即A部中的编号
vector<weight_t> labela; // A部的可行订标
vector<weight_t> labelb; // B的可行订标
vector<weight_t> slack;
vi flaga, flagb;
vi pre;
vi q;
int head, tail;

};

