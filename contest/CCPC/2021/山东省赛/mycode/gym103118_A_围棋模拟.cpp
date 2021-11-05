/**
    Χ�壬��ʼ����ֻ�к��塣��ֻ�߰��壬����ܳԵ����ٺ���
    �������������ͨ����߽磬Ȼ��������
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

int F[1010][1010];  // Fij��ʾijλ���ϵĺ������ͨ�����
char A[1010][1010];
vector<int> Qi2Hei[1010][1010]; // ����ij������Ȼ��Qi2Hei[i][j]��ʾ����Ӱ���ļ�����壬���4��
int N, HCnt;

vector<vpii> Heiqi; // Heiqi[i]��ʾ��i���������ͨ��
vector<hashpii> Qi; // Qi[i]��ʾ�ڸ�������ͨ����Χ������λ��

/// ��r��cλ�������������ͨ�飬��¼��heiqi����
void dfs(int r, int c, vpii&heiqi, hashpii&qi, const int index){
    /// ��λ�ÿ϶��Ǻ���
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
/// Bai[i]��ʾ��i��������ͨ�������
/// Bai[i][j]��ʾ��i��������ͨ��ĵ�j������
/// Bai[i][i][k]��ʾ��i��������ͨ��ĵ�j�������еĵ�k��λ��
vector<vector<vpii> >Bai;

/// ������rcλ����ͨ��ͬ����index�ڿ����
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

/// �����index�������ͨ�����
void zhengli(int index){
    /// ��ʼ��
    const vpii &hei = Heiqi[index];
    const hashpii &qi = Qi[index];
    vector<vpii> &bai = Bai[index];
    hashpii flag(qi);

    for(auto pp: qi){  // ���������ÿһ��λ��
        if(flag.find(pp)==flag.end()) continue;

        /// �ҵ�һ���µ���ͨ����
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
        /// ��
        cout<<"qi: "<<endl;
        for(auto pp: Qi[i]){
            cout<<"("<<pp.first<<", "<<pp.se<<")";
        }
        cout<<endl;
        /// ������ϵ���
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
    /// ���������
    cout<<"Qi2Hei:"<<endl;
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)if('.'==A[i][j]&&!Qi2Hei[i][j].empty()){
        cout<<"("<<i<<", "<<j<<"):";
        for(auto index: Qi2Hei[i][j]){
            cout<<" "<<index;
        }
        cout<<endl;
    }
}

/// �ж�rcλ����һ�������index�ڿ������һ�����
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

/// �ж��������������index������һ�����
inline bool isOKLive(const vpii&qikuai, int index){
    for(auto pp: qikuai){ // ��ÿһ��λ��
        for(int nr, nc, i=0;i<4;++i){
            nr = pp.fi + DR[i];
            nc = pp.se + DC[i];
            if(isOKLive(nr, nc, index)){ // �������鶼�ǻ��
                return true;
            }
        }
    }
    return false;
}

/// �жϵ�index�������Ƿ񱻳Ե�
/// ����ú������������鲻�ᱻ�Ե����ú�����ܱ�Χɱ
bool isOK(int index){
    vector<vpii> const&qikuais = Bai[index];
    int cnt = 0;
    for(auto qikuai: qikuais){ // ��ÿһ����������û���Լ�����
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
        if(isOK(i)){  // ���Ƚ������˵ĺ���ӽ�ȥ
            q.push(i);
            QFlag[i] = true;
        }
    }

    int ans = 0;
    while(!q.empty()){
        int h = q.front();q.pop();
        ans += Heiqi[h].size();

        /// ���Ƚ���h�����ȫ�������
        for(auto pp: Heiqi[h]){
            A[pp.fi][pp.se] = '.';
        }

        /// �ٶԵ�h������ÿ�����Ĺ�ͬ�ĺ��������ж����
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

/// ��CFGYM����Ҫ�ֶ���ջ�����������
/// ͬʱ��C++11����ʱ�ܹ���ʱ���ܹ�����C++17�¿��Թ�
/// ţ��������Ҫ������ֱ�ӹ�
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

    Heiqi.pb(vpii()); // ��һ���յ�
    Qi.pb(hashpii());

    /// �ҳ����еĺ�����ͨ�����
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        if('.'==A[i][j]||F[i][j]) continue;
        /// �ҵ�һ���µ���ͨ��
        Heiqi.pb(vpii());
        Qi.pb(hashpii());
        dfs(i, j, *--Heiqi.end(), *--Qi.end(), Heiqi.size()-1);
    }
    //disp();

    /// �ٰ�ÿ���ڿ���������
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
