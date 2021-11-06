/**
    给定一个字符矩阵，再给定一个单词表
    问满足条件的字母的数量有多少个。
    对每个字母，可以按照四个方向分别取出子串
    如果该子串不计字母顺序的等于某个单词，
    则称该字母属于这个单词
    如果某个字母至少属于二个单词，则称满足条件
    例如矩阵是：ABC
    单词是: BCA和CB
    则满足条件的字母有二个。
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define fi first
#define se second
#define pb push_back
typedef vector<int> vi;

bool operator == (const vi&lhs, const vi&rhs){
    vi::const_iterator it = lhs.begin();
    vi::const_iterator jt = rhs.begin();
    for(;it!=lhs.end();){
        if(*it++!=*jt++) return false;
    }
    return true;
}

int L,C,N;
char A[50][50];
char B[22][50];
int Len[22];

//Wordi表示第i个单词的字母构成
vector<vi> Word(22, vi(26, 0));

int MinLen, MaxLen;

//每个字母在哪些字符串中出现过
vi L2I[256];

//Rij表示第i行第j个字母能够出现多少个不同的单词
vi R[50][50];
bool Flag[50][50][22] = {0};

bool checkRight(int r,int c,int idx){
    vi vtmp(26, 0);
    int n = c+Len[idx];
    char *p = A[r] + c;
    for(int i=c;i<n;++i){
        ++vtmp[*p++ - 'A'];
        //++p;
    }

    /*
    cout<<r<<", "<<c<<": ";
    for(auto v: vtmp)cout<<v<<" ";
    cout<<endl;//*/

    return vtmp == Word[idx];
}

void checkRight(int r, int c){
    int n = C - c;
    if(n<MinLen) return;
    if(n>MaxLen) n = MaxLen;

    for(int i=1;i<=N;++i)if(Len[i]<=n){
        if(checkRight(r, c, i)){
            //设置所有的字母
            int m = c+Len[i];
            for(int j=c;j<m;++j){
                Flag[r][j][i] = true;
                R[r][j].pb(i);
            }
        }
    }
}

bool checkDown(int r,int c,int idx){
    vi vtmp(26, 0);
    int n = r+Len[idx];
    char *p = A[r] + c;
    for(int i=r;i<n;++i){
        ++vtmp[*p - 'A'];
        p += 50; // 数组一行是50
    }

    /*
    cout<<r<<", "<<c<<": ";
    for(auto v: vtmp)cout<<v<<" ";
    cout<<endl;//*/

    return vtmp == Word[idx];
}

void checkDown(int r, int c){
    int n = L - r;
    if(n<MinLen) return;
    if(n>MaxLen) n = MaxLen;

    for(int i=1;i<=N;++i)if(Len[i]<=n){
        if(checkDown(r,c,i)){
            int m = r + Len[i];
            for(int j=r;j<m;++j){
                //Flag[j][c][i] = true;
                R[j][c].pb(i);
            }
        }
    }
}

bool checkDiag(int r,int c,int idx){
    vi vtmp(26, 0);
    int n = r+Len[idx];
    char *p = A[r] + c;
    for(int i=r;i<n;++i){
        ++vtmp[*p - 'A'];
        p += 51; // 加一行，再加1
    }

    /*
    cout<<r<<", "<<c<<": ";
    for(auto v: vtmp)cout<<v<<" ";
    cout<<endl;//*/

    return vtmp == Word[idx];
}

void checkDiag(int r, int c){
    int n = min(L-r, C-c);
    if(n<MinLen) return;
    if(n>MaxLen) n = MaxLen;

    for(int i=1;i<=N;++i)if(Len[i]<=n){
        if(checkDiag(r,c,i)){
            int m = r + Len[i];
            for(int rr=r,cc=c;rr<m;++rr,++cc){
                //Flag[rr][cc][i] = true;
                R[rr][cc].pb(i);
            }
        }
    }
}
bool checkFan(int r,int c,int idx){
    vi vtmp(26, 0);
    int n = r+Len[idx];
    char *p = A[r] + c;
    for(int i=r;i<n;++i){
        ++vtmp[*p - 'A'];
        p += 49; // 加一行，再减1
    }

    /*
    cout<<r<<", "<<c<<": ";
    for(auto v: vtmp)cout<<v<<" ";
    cout<<endl;//*/

    return vtmp == Word[idx];
}
void checkFan(int r,int c){
    int n = min(L-r, c+1);
    if(n<MinLen) return;
    if(n>MaxLen) n = MaxLen;

    for(int i=1;i<=N;++i)if(Len[i]<=n){
        if(checkFan(r,c,i)){
            int m = r + Len[i];
            for(int rr=r,cc=c;rr<m;++rr,--cc){
                //Flag[rr][cc][i] = true;
                R[rr][cc].pb(i);
            }
        }
    }
}

//检查第r行，第c列
inline void check(int r,int c){
    checkRight(r, c);
    checkDown(r, c);
    checkDiag(r, c);
    checkFan(r, c);
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&L,&C);
    for(int i=0;i<L;++i)scanf("%s", A[i]);
    scanf("%d",&N);

    MinLen = 10000, MaxLen = -1;
    for(int i=1;i<=N;++i){
        scanf("%s", B[i]);
        for(char *p=B[i];*p;++p){
            L2I[*p].pb(i);
            ++Word[i][*p-'A'];
        }

        int n = Len[i] = strlen(B[i]);
        MinLen = min(MinLen, n);
        MaxLen = max(MaxLen, n);
    }

    /*
    for(int i=1;i<=N;++i){
        cout<<i<<": ";
        for(auto v:Word[i])cout<<v<<" ";
        cout<<endl;
    }//*/

    int ans = 0;
    for(int i=0;i<L;++i)for(int j=0;j<C;++j){
        check(i, j);
        sort(R[i][j].begin(),R[i][j].end());
        R[i][j].erase(unique(R[i][j].begin(),R[i][j].end()),R[i][j].end());
        if(R[i][j].size()>1) ++ans;
    }
    printf("%d\n", ans);

    /*
    for(int i=0;i<L;++i)for(int j=0;j<C;++j){
        cout<<i<<", "<<j<<": ";
        for(auto v:R[i][j]) cout<<v<<" ";
        cout<<endl;
    }//*/
    return 0;
}
