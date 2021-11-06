/**
  ����һ�����ף��ٸ������ɲ�ѯ��ÿ�β�ѯ����������˵Ĺ�ϵ��������ĿҪ��������
  ��Ҫ��Ҫ�ҳ������˵�LCA��ֻ��100���ڵ㣬����ҡ�
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE_OF_VERTICES = 110;
//Pij��ʾ��i���ڵ��2^j���������
//����Pi0����i�ĸ��ڵ�
int Parent[SIZE_OF_VERTICES][22];
int Depth[SIZE_OF_VERTICES];//���ڵ�������1
//Log2[i]������2Ϊ��i�Ķ�����1��ȡ������ҪԤ�������
int Log2[SIZE_OF_VERTICES];

unordered_map<string, int> Name2Idx;

vector<int> Sons[110];
int Father[110];

string A[1010], B[1010];
int AI[1010], BI[1010];

int Root;

void dfs(int u,int parent){
    Parent[u][0] = parent;
    Depth[u] = Depth[parent] + 1;
    //ȷ��u�ĸ�������
    for(int i=1,n=Log2[Depth[u]];i<=n;++i){
        Parent[u][i] = Parent[Parent[u][i-1]][i-1];
    }
    for(auto v: Sons[u]){
        dfs(v,u);
    }
}

int lca(int x,int y){
    if(Depth[x]<Depth[y]) swap(x,y);
    //��x��y������һ�����������
    while(Depth[x]>Depth[y]) x = Parent[x][Log2[Depth[x]-Depth[y]]-1];
    if(x==y) return x;
    //һ��������
    for(int k=Log2[Depth[x]]-1;k>=0;--k){
        if(Parent[x][k]!=Parent[y][k]){
            x = Parent[x][k];
            y = Parent[y][k];
        }
    }
    return Parent[x][0];
}

inline int get(const string&s){
    auto it = Name2Idx.find(s);
    if(it!=Name2Idx.end()) return it->second;
    return Name2Idx[s] = Name2Idx.size() + 1;
}

void outputChild(const string&fathername, const string&sonname, int n){
    if(1==n){
        printf("%s is the child of %s\n", sonname.c_str(), fathername.c_str());
        return;
    }
    if(2==n){
        printf("%s is the grandchild of %s\n", sonname.c_str(), fathername.c_str());
        return;
    }
    printf("%s is the", sonname.c_str());
    for(int i=0;i<n-2;++i)printf(" great");
    printf(" grandchild of %s\n", fathername.c_str());
}

/// �����index������
void proc(int index){
    int a = AI[index], b = BI[index];
    int ancestor = lca(a, b);
    int m = Depth[a] - Depth[ancestor];
    int n = Depth[b] - Depth[ancestor];

    if(0==m){
        outputChild(A[index], B[index], n);
        return;
    }
    if(0==n){
        outputChild(B[index], A[index], m);
        return;
    }
    if(n==m){
        if(1==n){
            printf("%s and %s are siblings\n", A[index].c_str(), B[index].c_str());
            return;
        }
        --n;
        printf("%s and %s are %d", A[index].c_str(), B[index].c_str(), n);
        if(n%10==1&&n!=11) printf("st");
        else if(n%10==2&&n!=12)printf("nd");
        else if(n%10==3&&n!=13)printf("rd");
        else printf("th");
        printf(" cousins\n");
        return;
    }

    int th = min(n, m);
    --th;
    int cha = m - n;
    if(cha<0) cha = -cha;
    printf("%s and %s are %d", A[index].c_str(), B[index].c_str(), th);
    if(th%10==1&&th!=11) printf("st");
    else if(th%10==2&&th!=12)printf("nd");
    else if(th%10==3&&th!=13)printf("rd");
    else printf("th");
    printf(" cousins, %d time", cha);
    if(cha>1) printf("s");
    printf(" removed\n");
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    memset(Parent, 0, sizeof(Parent));
    memset(Depth, 0, sizeof(Depth));
    Name2Idx.clear();
    for(int i=0;i<110;++i)Sons[i].clear();
    memset(Father, 0, sizeof(Father));
    int t, p, m;
    char a[15];
    scanf("%d%d",&t,&p);
    assert(t<=100);
    while(t--){
        scanf("%s%d", a, &m);
        if(strlen(a)>10) while(1);
        int fidx = get(string(a));
        while(m--){
            scanf("%s", a);
            if(strlen(a)>10) while(1);
            int sidx = get(string(a));
            Father[sidx] = fidx;
            Sons[fidx].push_back(sidx);
        }
    }
    for(int i=1;i<=p;++i){
        scanf("%s", a);
        if(strlen(a)>10) while(1);
        AI[i] = get(A[i] = string(a));
        scanf("%s", a);
        if(strlen(a)>10) while(1);
        BI[i] = get(B[i] = string(a));
    }

    /// �Ҹ�
    for(int i=1,n=Name2Idx.size();i<=n;++i){
        if(!Father[i]){
            Root = i;
            break;
        }
    }

    ///��ʼ��
    for(int i=1,N=Name2Idx.size();i<=N;++i){
        Log2[i] = Log2[i-1] + ( (1 << Log2[i-1])==i?1:0 );
    }
    dfs(Root,0);

    for(int i=1;i<=p;++i){
        proc(i);
    }

    return 0;
}


