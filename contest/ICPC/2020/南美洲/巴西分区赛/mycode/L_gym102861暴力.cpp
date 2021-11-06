/**
    ����һ���ַ������ٸ���һ�����ʱ�
    ��������������ĸ�������ж��ٸ���
    ��ÿ����ĸ�����԰����ĸ�����ֱ�ȡ���Ӵ�
    ������Ӵ�������ĸ˳��ĵ���ĳ�����ʣ�
    ��Ƹ���ĸ�����������
    ���ĳ����ĸ�������ڶ������ʣ������������
    ��������ǣ�ABC
    ������: BCA��CB
    ��������������ĸ�ж�����
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

//Wordi��ʾ��i�����ʵ���ĸ����
vector<vi> Word(22, vi(26, 0));

int MinLen, MaxLen;

//ÿ����ĸ����Щ�ַ����г��ֹ�
vi L2I[256];

//Rij��ʾ��i�е�j����ĸ�ܹ����ֶ��ٸ���ͬ�ĵ���
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
            //�������е���ĸ
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
        p += 50; // ����һ����50
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
        p += 51; // ��һ�У��ټ�1
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
        p += 49; // ��һ�У��ټ�1
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

//����r�У���c��
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
