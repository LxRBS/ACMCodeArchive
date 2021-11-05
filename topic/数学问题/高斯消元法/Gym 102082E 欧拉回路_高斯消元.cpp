/**
    ��ͼ�����һЩ�ߣ�ʹ�ô���ŷ����·
    ŷ����·�ĳ�Ҫ���������е�Ķ���Ϊż��
    ������һ�����Է����飬�õ���������ӵı�
    ��ʱ�������е�Ķ���Ϊż��
    Ȼ������ͨ�����������1����2���Լ�����ֱ���
    �ݲ²⣬�������ŷ����·�����Ȼ����̰�ģ��������
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

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int const SIZE = 110;
int const SIZE_OF_COLUMN = SIZE*SIZE>>1;

//a���������
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//������ڶ�⡢һ���������������Ϊ���ɱ�Ԫ������
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[], int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ���˴�Ϊ1����
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //���е�row�м�����ȫΪ0����Ҫ���ǵ�row�е���һ��
        if ( maxr == cntOfEq ) {
            --row;
            continue;
        }

        //����
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //����row�����µ��еĵ�col������
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //disp(a,cntOfEq,cntOfUnknown);

    //���ȫ0�е��������Ƿ�ҲΪ0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//�޽�
    }

    //�õ�����һ����
    for(int i=cntOfEq-1;i>=0;--i){
        //��ÿһ��ȡ��һ��δ֪��
        //������Ҫô�Ѿ����,Ҫô�����ɱ�Ԫ��ȡ0
        int k = i;
        while(k<cntOfUnknown&&a[i][k]==0) ++k;
        if(k==cntOfUnknown) continue;

        x[k] = a[i][cntOfUnknown];
        for(int j=k+1;j<cntOfUnknown;++j){
            x[k] ^= ( x[j] && a[i][j] );
        }
    }

    return cntOfUnknown - row;//���ر�Ԫ�ĸ���������Ϊ0��Ψһ��
}


int A[SIZE][SIZE_OF_COLUMN];
int X[SIZE_OF_COLUMN];

int Graph[SIZE][SIZE];
int Deg[SIZE];
int Cnt = 0;

typedef pair<int,int> pii;
pii Idx2Edge[SIZE*SIZE>>1];

int N,M;

//��ȡ��ͨ�������
int getCC(vector<int>&v){
    v.clear();
    bool flag[SIZE] = {false};
    int ans = 0;
    for(int i=1;i<=N;++i){
        if(!flag[UF.find(i)]){
            ++ans;
            flag[UF.find(i)] = true;
            v.push_back(UF.find(i));
        }
    }
    return ans;
}

vector<int> Ans;
vector<int> CC;

bool IsCritical[SIZE];

void check(){
    int deg[110] = {0};
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)if(-1==Graph[i][j]){
        ++deg[i];
    }
    for(int i=1;i<=N;++i)if(deg[i]&1){
        puts("XXXXXXXXXXXXXXXXXXXXX");
        return;
    }
    puts("OK!!!");
}

void output(){
    printf("%d\n",(int)Ans.size());
    for(auto i: Ans){
        printf("%d %d\n",Idx2Edge[i].first,Idx2Edge[i].second);
    }

    //check();
}


///������ӵı��������һ��������������㼴��
int f1(vector<int>const&ca,vector<int>const&cb){
    int liwai = 0;
    for(int i=0;i<Cnt;++i)if(1==X[i]&&!IsCritical[i]){
        int a = Idx2Edge[i+1].first;
        int b = Idx2Edge[i+1].second;
        liwai = Graph[a][b];
        Ans.push_back(Graph[a][cb[0]]);
        Ans.push_back(Graph[b][cb[0]]);
        break;
    }
    return liwai;
}

///��ca���������㣬��������
bool f2(vector<int>const&ca,vector<int>const&cb){
    for(int i=0,n=ca.size();i<n;++i)for(int j=i+1;j<n;++j){
        if(Graph[ca[i]][ca[j]]>0&&0==X[Graph[ca[i]][ca[j]]-1]){
            Ans.push_back(Graph[ca[i]][ca[j]]);
            Ans.push_back(Graph[ca[i]][cb[0]]);
            Ans.push_back(Graph[ca[j]][cb[0]]);
            return true;
        }
    }
    return false;
}

void proc(){
    ///���Ƚⷽ��
    int ret = Gauss(A,X,N,Cnt);
    if(-1==ret){//�޽�
        puts("-1");
        return;
    }

    ///X������һ���⣬���߼���
    for(int a,b,i=0;i<Cnt;++i)if(X[i]){
        Ans.push_back(i+1);
        a = Idx2Edge[i+1].first;
        b = Idx2Edge[i+1].second;
        if(UF.find(a)!=UF.find(b)){
            UF.unite(a,b);
            IsCritical[i] = true;//�ؽ���
        }

    }

    int cc_cnt = getCC(CC);
    if(1==cc_cnt){//ֱ�����
        output();
        return;
    }

    if(cc_cnt>=3){//��ͨ���3��ȽϷ��㣬ֱ��ΧһȦ
        for(vector<int>::const_iterator it=++CC.begin();it!=CC.end();++it){
            int a = *(it-1);
            int b = *it;
            Ans.push_back(Graph[a][b]);
        }
        int a = *--CC.end();
        int b = *CC.begin();
        Ans.push_back(Graph[a][b]);
        ///���
        output();
        return;
    }

    ///2����ͨ�������鷳��
    vector<int> ca,cb;
    for(int i=1;i<=N;++i){
        if(UF.find(i)==CC[0]) ca.push_back(i);
        else if(UF.find(i)==CC[1]) cb.push_back(i);
        else throw runtime_error("XXXXXXXXXXXX");
    }

    ///�й����㣬�������룬����������������
    if(ca.size()==1||cb.size()==1){
        if(ca.size()==1) swap(ca, cb);

        ///������ӵı�����һ���ǹؼ��ߣ�����������㼴��
        int liwai = f1(ca, cb);
        if(liwai){
            ///���
            printf("%d\n", (int)Ans.size()-1);
            for(auto i: Ans)if(i!=liwai){
                printf("%d %d\n",Idx2Edge[i].first,Idx2Edge[i].second);
            }
            //check();
            return;
        }

        ///��ca���������㣬�������ģ�����
        if(f2(ca, cb)){
            output();
        }else{
            puts("-1");
        }
        return;
    }

    ///û�й����㣬��ֱ����������ͨ�����ȡ�����㣬�������Ӽ���
    Ans.push_back(Graph[ca[0]][cb[0]]);
    Ans.push_back(Graph[ca[0]][cb[1]]);
    Ans.push_back(Graph[ca[1]][cb[0]]);
    Ans.push_back(Graph[ca[1]][cb[1]]);
    ///���
    output();
}

int main(){
    //freopen("1.txt","r",stdin);
    ///����
    UF.init(N = getUnsigned());
    M = getUnsigned();
    for(int a,b,i=0;i<M;++i){
        UF.unite(a = getUnsigned(),b = getUnsigned());
        Graph[a][b] = Graph[b][a] = -1;
        Deg[a] ^= 1;
        Deg[b] ^= 1;
    }
    ///Ϊÿ��Ŀǰ�����ڵı߱�ţ���Щ���ǿ���Ҫ�ӵı�
    for(int i=1;i<=N;++i)for(int j=i+1;j<=N;++j)if(i!=j&&0==Graph[i][j]){
        Idx2Edge[Graph[i][j] = Graph[j][i] = ++Cnt] = pii({i, j});
    }
    ///�����������ע��ϵ�����������Ǵ�0��ʼ
    for(int i=0;i<N;++i){
        for(int j=0;j<Cnt;++j){
            ///�����j�������i���������ϵ��Ϊ1
            if(Idx2Edge[j+1].first==i+1||Idx2Edge[j+1].second==i+1){
                A[i][j] = 1;
            }else{
                A[i][j] = 0;
            }
        }
        A[i][Cnt] = Deg[i+1];
    }
    ///���
    proc();
    return 0;
}
