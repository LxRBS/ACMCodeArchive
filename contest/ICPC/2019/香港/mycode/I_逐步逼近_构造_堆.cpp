/**
    2�ֲ�����
    1����������y�����3��λ�ã�Ŀ����ai1+ai2+ai3==y
    2������λ��x������y���ò����󣬿�����Щ1���������Ŀ��
    ǿ������
    ��ÿһ���ڵ㣬����һ����С�ѣ����ڱ���(Ŀ��, ���)
    ��ĳ��1������������Ŀ����t��һ��3��λ�ã�����ֱ���p1,p2,p3
    ��(t/3, idx)����3������
    ��ĳ��2���������������ӵ�����Ϊy�������Ӧ�ѣ����ǴﵽĿ��ľ�ȡ��
    ����ȡ��������Ϊ(t, idx)��Ȼ�����idx��Ŀ�꣬�ٽ�ʣ�µķֳ�3�ݣ���������Ӧ�Ķ���
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

bool Finished[SIZE];//��i�������Ƿ��Ѿ����
llt Level[SIZE];//ÿ��λ�õ���ֵ
int Goal[SIZE];
vector<int> Pos[SIZE]; //1������Ӧ��3��λ��
vector<llt> Prev[SIZE];//1������Ӧ��3��λ�õĸ���ǰ����ֵ
pliq Q[SIZE];
vector<int> Ans;

//����1
void f1(int idx,int goal, int cnt, int const pos[]){
    Goal[idx] = goal;
    Pos[idx].assign(pos,pos+cnt);
    //���cnt�ݣ�����������
    int left = (goal + cnt - 1) / cnt;
    for(int p,i=0;i<cnt;++i){
        p = pos[i];
        Q[p].push(pli({Level[p]+left, idx}));
        Prev[idx].push_back(Level[p]);
    }
}

//����2��posλ������value
void f2(int pos,int value){
    //��Ӧλ������value
    Level[pos] += value;

    pliq& q = Q[pos];
    pli u;
    while(!q.empty()){
        u = q.top();
        if(u.fi>Level[pos]) break;

        q.pop();
        if(Finished[u.se]) continue;

        //���3��λ��
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

        //�����Ȼδ���,��ʣ�µ�Ŀ������������
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

            //ִ�в���1
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
