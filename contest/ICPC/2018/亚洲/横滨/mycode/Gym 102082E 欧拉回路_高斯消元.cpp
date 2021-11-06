/**
    在图中添加一些边，使得存在欧拉回路
    欧拉回路的充要条件是所有点的度数为偶数
    首先列一个线性方程组，得到初步可添加的边
    此时满足所有点的度数为偶数
    然后检查连通块的数量，对1个、2个以及多个分别处理
    据猜测，如果可以欧拉回路，则必然可以贪心，无需回溯
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

//a是增广矩阵
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入存在多解、一解和零解的情况，输出为自由变元的数量
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[], int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找列主元，此处为1即可
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //该列第row行及以下全为0，则要考虑第row行的下一列
        if ( maxr == cntOfEq ) {
            --row;
            continue;
        }

        //交换
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //将第row行以下的行的第col列清零
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //disp(a,cntOfEq,cntOfUnknown);

    //检查全0行的增广列是否也为0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//无解
    }

    //得到其中一个解
    for(int i=cntOfEq-1;i>=0;--i){
        //对每一行取第一个未知数
        //其他的要么已经求出,要么是自由变元，取0
        int k = i;
        while(k<cntOfUnknown&&a[i][k]==0) ++k;
        if(k==cntOfUnknown) continue;

        x[k] = a[i][cntOfUnknown];
        for(int j=k+1;j<cntOfUnknown;++j){
            x[k] ^= ( x[j] && a[i][j] );
        }
    }

    return cntOfUnknown - row;//返回变元的个数，数量为0即唯一解
}


int A[SIZE][SIZE_OF_COLUMN];
int X[SIZE_OF_COLUMN];

int Graph[SIZE][SIZE];
int Deg[SIZE];
int Cnt = 0;

typedef pair<int,int> pii;
pii Idx2Edge[SIZE*SIZE>>1];

int N,M;

//获取连通块的数量
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


///在已添加的边中随便找一条，拆开连向孤立点即可
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

///在ca中找两个点，互相空余的
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
    ///首先解方程
    int ret = Gauss(A,X,N,Cnt);
    if(-1==ret){//无解
        puts("-1");
        return;
    }

    ///X是其中一个解，将边加上
    for(int a,b,i=0;i<Cnt;++i)if(X[i]){
        Ans.push_back(i+1);
        a = Idx2Edge[i+1].first;
        b = Idx2Edge[i+1].second;
        if(UF.find(a)!=UF.find(b)){
            UF.unite(a,b);
            IsCritical[i] = true;//关建边
        }

    }

    int cc_cnt = getCC(CC);
    if(1==cc_cnt){//直接输出
        output();
        return;
    }

    if(cc_cnt>=3){//连通块比3大比较方便，直接围一圈
        for(vector<int>::const_iterator it=++CC.begin();it!=CC.end();++it){
            int a = *(it-1);
            int b = *it;
            Ans.push_back(Graph[a][b]);
        }
        int a = *--CC.end();
        int b = *CC.begin();
        Ans.push_back(Graph[a][b]);
        ///输出
        output();
        return;
    }

    ///2个连通块是最麻烦的
    vector<int> ca,cb;
    for(int i=1;i<=N;++i){
        if(UF.find(i)==CC[0]) ca.push_back(i);
        else if(UF.find(i)==CC[1]) cb.push_back(i);
        else throw runtime_error("XXXXXXXXXXXX");
    }

    ///有孤立点，根据输入，不可能两个都孤立
    if(ca.size()==1||cb.size()==1){
        if(ca.size()==1) swap(ca, cb);

        ///在已添加的边中找一条非关键边，拆开连向孤立点即可
        int liwai = f1(ca, cb);
        if(liwai){
            ///输出
            printf("%d\n", (int)Ans.size()-1);
            for(auto i: Ans)if(i!=liwai){
                printf("%d %d\n",Idx2Edge[i].first,Idx2Edge[i].second);
            }
            //check();
            return;
        }

        ///在ca中找两个点，互相空余的，即可
        if(f2(ca, cb)){
            output();
        }else{
            puts("-1");
        }
        return;
    }

    ///没有孤立点，则直接在两个连通块里各取两个点，两两连接即可
    Ans.push_back(Graph[ca[0]][cb[0]]);
    Ans.push_back(Graph[ca[0]][cb[1]]);
    Ans.push_back(Graph[ca[1]][cb[0]]);
    Ans.push_back(Graph[ca[1]][cb[1]]);
    ///输出
    output();
}

int main(){
    //freopen("1.txt","r",stdin);
    ///输入
    UF.init(N = getUnsigned());
    M = getUnsigned();
    for(int a,b,i=0;i<M;++i){
        UF.unite(a = getUnsigned(),b = getUnsigned());
        Graph[a][b] = Graph[b][a] = -1;
        Deg[a] ^= 1;
        Deg[b] ^= 1;
    }
    ///为每条目前不存在的边编号，这些边是可能要加的边
    for(int i=1;i<=N;++i)for(int j=i+1;j<=N;++j)if(i!=j&&0==Graph[i][j]){
        Idx2Edge[Graph[i][j] = Graph[j][i] = ++Cnt] = pii({i, j});
    }
    ///建立增广矩阵，注意系数矩阵的序号是从0开始
    for(int i=0;i<N;++i){
        for(int j=0;j<Cnt;++j){
            ///如果第j条边与第i点关联，则系数为1
            if(Idx2Edge[j+1].first==i+1||Idx2Edge[j+1].second==i+1){
                A[i][j] = 1;
            }else{
                A[i][j] = 0;
            }
        }
        A[i][Cnt] = Deg[i+1];
    }
    ///求解
    proc();
    return 0;
}
