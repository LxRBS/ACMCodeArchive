/**
    ����һ��10��10�ĵ�ͼ����ʪ�أ��пյأ����ϰ�
    �����������ڵ�ͼ�ϰڷ��������Ҫ��
    1 �������������
    2 �����������ʪ������
    3 ��ͬһ��ʪ�����ڵ��������������
    ��Ŀ��֤����ʪ��֮��ľ�������Ϊ3���������ܰڷ�һ�������ͬʱ��������ͬ��ʪ������
    ��һ��ʪ�ص��ܿ������ᳬ��2N
    ���ܰڷ��߸渺��������ʤ��
    ע�⵽ʪ�صļ�࣬���Խ�������Ϸ����Ϊ���ɸ�С��Ϸ
    ��С��Ϸ�ĵ�ͼ�������ᳬ��2N
    ���ǿ�����2^20�������ÿ��С��Ϸ��SGֵ�������һ�¼���
*/
#include <bits/stdc++.h>
using namespace std;

char const Output[][100] = {
    "Second player will win",
    "First player will win"
};
int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M;
char A[22][22];

int WetIdx = 0;
int Wet[22][22];

typedef pair<int,int> pii;
vector<vector<pii> > Vec;
bool Flag[22][22];

void dfs(int r,int c,int idx){
    Wet[r][c] = idx;
    for(int i=0;i<4;++i){
        int nr = r + DR[i];
        int nc = c + DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&'*'==A[nr][nc]&&0==Wet[nr][nc]){
            Wet[nr][nc] = idx;
            dfs(nr,nc,idx);
        }
    }
}

void getWet(int r,int c,vector<int>&v){
    v.clear();
    for(int i=0;i<4;++i){
        int nr = r+DR[i];
        int nc = c+DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&Wet[nr][nc]){
            v.push_back(Wet[nr][nc]);
        }
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

///�ж�����λ���Ƿ�����ͬһ��wet
bool judge(int r1,int c1,int r2,int c2){
    vector<int> v1,v2;
    getWet(r1,c1,v1);
    getWet(r2,c2,v2);
    if(v1.size()>1) throw runtime_error("xx1");
    if(v2.size()>1) throw runtime_error("xx2222");

    if(v1.empty()) return false;
    if(v2.empty()) return false;
    return v1[0] == v2[0];
}

void dfs2(int r, int c,vector<pii>&v){
    Flag[r][c] = true;
    v.push_back(pii({r,c}));
    for(int i=0;i<4;++i){
        int nr = r+DR[i];
        int nc = c+DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&'.'==A[nr][nc]&&!Flag[nr][nc]&&judge(r,c,nr,nc)){
            dfs2(nr,nc,v);
        }
    }
}

bool isOK(int r,int c){
    for(int i=0;i<4;++i){
        int nr = r+DR[i];
        int nc = c+DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&Flag[nr][nc]){
            return false;
        }
    }
    return true;
}

int SG[1<<21];
int dfs3(int state,vector<pii>const&v){
    if(SG[state]!=-1) return SG[state];

    bool mex[1000] = {false};
    for(int i=0,n=v.size();i<n;++i){
        if((1<<i)&state) continue;

        int r = v[i].first;
        int c = v[i].second;
        ///���rc�Ƿ�ɷ�
        if(isOK(r,c)){
            Flag[r][c]=true;//��
            int t = dfs3(state|(1<<i),v);//��
            if(t<1000)mex[t] = true;
            Flag[r][c]=false;//��ԭ
        }
    }

    ///���ش�
    for(int i=0;i<1000;++i)if(!mex[i])return SG[state]=i;
    throw runtime_error("XXXX333333");//��Ӧ�õ���
}

///���㵱ǰ�ɰڷ�λ�õ�sgֵ
int sg(vector<pii>const&v){
    memset(Flag,0,sizeof(Flag));
    fill(SG,SG+(1<<v.size()),-1);
    return dfs3(0, v);
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%s",A[i]);
    M = strlen(A[0]);

    ///���ʪ��
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if(0==Wet[i][j]&&'*'==A[i][j]){
            dfs(i, j, ++WetIdx);
        }
    }

    ///�����������ڷŵ�λ��
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if('.'==A[i][j]&&!Flag[i][j]){
            vector<int> v;
            getWet(i,j,v);
            if(v.empty()) continue;

            Vec.push_back(vector<pii>());
            dfs2(i, j, *--Vec.end());
        }
    }

    /*///debug
    for(unsigned i=0,n=Vec.size();i<n;++i){
        for(auto p: Vec[i]){
            A[p.first][p.second] = i + '1';
        }
    }
    for(int i=0;i<N;++i)puts(A[i]);//*/

    ///����ÿһ����λ�õ�sgֵ
    int ans = 0;
    for(auto v: Vec){
        int tmp = sg(v);
        ans = ans ^ tmp;
    }
    puts(Output[ans?1:0]);
    return 0;
}
