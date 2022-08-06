#include<bits/stdc++.h>

using namespace std;

const int N=5;
int Num=0;
char ans[N][N][N];
char status[5050][N][N][N];
vector<string>str;

struct DLX{
    #define maxnode 1000010
    #define maxn 5050
    
    int n,m,tot;
    //n行 m列 现在一共有tot个元素
    int U[maxnode],D[maxnode],L[maxnode],R[maxnode];
    //U D L R 表示每个点四个方向所指向的节点编号
    int Row[maxnode],Col[maxnode];
    //Row Col 表示每个点所在的行号和列号
    int H[maxn],num[maxn];
    //H 是每行的开始位置    num 是每一列有多少个元素
    int ansnum,ans[maxn];
    //记录答案，表示我们选择了哪些行
    inline void init(int M){
        m=M;
        for(int i=0; i<=m; i++){
            num[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1;
            R[i]=i+1;
        }
        L[0]=m;
        R[m]=0;
        tot=m;
        for(int i=1; i<maxn; i++)H[i]=-1;
    }
    inline void add(int x,int y){//在x行y列插入一个元素
        tot++;
        Col[tot]=y;
        Row[tot]=x;
        num[y]++;
        D[tot]=D[y];
        U[D[y]]=tot;
        U[tot]=y;
        D[y]=tot;
        //在第y列的列首元素下面插入当前元素
        if(H[x]<0){//如果第x行为空，那么将当前元素设为行首元素
            H[x]=L[tot]=R[tot]=tot;
        }
        else{//否则在第x行的第一个元素后插入当前元素
            R[tot]=R[H[x]];
            L[R[H[x]]]=tot;
            L[tot]=H[x];
            R[H[x]]=tot;
        }
    }
    inline void remove(int y){//将第y列删除，并删除第y列中所有元素所在的行
        L[R[y]]=L[y];
        R[L[y]]=R[y];
        for(int i=D[y]; i!=y; i=D[i]){
            for(int j=R[i]; j!=i; j=R[j]){
                U[D[j]]=U[j];
                D[U[j]]=D[j];
                num[Col[j]]--;
            }
        }
    }
    inline void restore(int y){//反过来，进行恢复
        L[R[y]]=y;
        R[L[y]]=y;
        for(int i=U[y]; i!=y; i=U[i]){
            for(int j=L[i]; j!=i; j=L[j]){
                U[D[j]]=j;
                D[U[j]]=j;
                num[Col[j]]++;
            }
        }
    }
    bool dance(int deep){
        if(R[0]==0){
            Num++;
            ansnum=deep;
            for(int i=0; i<ansnum; i++){
                for(int X=0; X<4; X++){
                    for(int Y=0; Y<4; Y++){
                        for(int Z=0; Z<4; Z++){
                            if(status[ans[i]][X][Y][Z]!='.'){
                                ::ans[X][Y][Z]=status[ans[i]][X][Y][Z];
                            }
                        }
                    }
                }
            }
            string s="";
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    for(int k=0; k<4; k++){
                        s+=::ans[i][j][k];
                    }
                }
            }
            str.push_back(s);
            /* for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    printf("%s\n",::ans[i][j]);
                }
            }
            exit(0); */
            return true;
        }
        int now=R[0];
        for(int i=R[0]; i!=0; i=R[i]){
            if(num[i]<num[now])now=i;
        }
        //找到列中包含1最少的列，因为这样可以减少dfs的分支
        remove(now);
        for(int i=D[now]; i!=now; i=D[i]){
            ans[deep]=Row[i];
            for(int j=R[i]; j!=i; j=R[j])remove(Col[j]);
            dance(deep+1);
            //if(dance(deep+1))return true;
            for(int j=L[i]; j!=i; j=L[j])restore(Col[j]);
        }
        restore(now);
        return false;
    }
    
    #undef maxnode
    #undef maxn
}dlx;

int tot;
int pos[N][N][N];
bool vis[14];
int xspin[14]={1,1,1,1,1,1,1,0,1,1,1,0};
int yspin[14]={1,1,1,1,1,1,1,0,1,1,1,0};
int zspin[14]={1,1,1,1,1,1,1,0,1,1,1,0};

const int x[14][10]={
    {0,1,0,1,0,0,0,-1},
    {0,1,0,0,0,-1},
    {0,1,2,2,0,-1},
    {0,1,2,0,1,0,1,-1},
    {0,1,2,0,1,1,-1},
    {0,1,0,1,-1},
    {0,1,0,-1},
    {0,0,-1},
    {0,1,0,1,0,1,0,1,-1},
    {0,1,0,1,0,1,0,-1},
    {0,1,0,1,0,1,-1},
    {0,0,0,-1},
    {0,-1},
};
const int y[14][10]={
    {0,0,1,1,0,0,0,-1},
    {0,0,1,0,0,-1},
    {0,0,0,1,0,-1},
    {0,0,0,1,1,0,0,-1},
    {0,0,0,1,0,0,-1},
    {0,0,1,0,-1},
    {0,0,0,-1},
    {0,0,-1},
    {0,0,1,1,0,0,1,1,-1},
    {0,0,1,1,0,0,1,-1},
    {0,0,0,0,0,0,-1},
    {0,0,0,-1},
    {0,-1},
};
const int z[14][10]={
    {0,0,0,0,1,2,3,-1},
    {0,0,0,1,2,-1},
    {0,0,0,0,1,-1},
    {0,0,0,0,0,1,1,-1},
    {0,0,0,0,1,2,-1},
    {0,0,0,1,-1},
    {0,0,1,-1},
    {0,1,-1},
    {0,0,0,0,1,1,1,1,-1},
    {0,0,0,0,1,1,1,-1},
    {0,0,1,1,2,2,-1},
    {0,1,2,-1},
    {0,-1},
};

inline void clear(int id){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<4; k++){
                status[id][i][j][k]='.';
            }
        }
    }
}

unordered_map<string,bool>mp;

struct node{
    int x,y,z;
    node(int a=0,int b=0,int c=0){x=a,y=b,z=c;}
    friend bool operator < (node a,node b){
        if(a.x==b.x){
            if(a.y==b.y){
                return a.z<b.z;
            }
            return a.y<b.y;
        }
        return a.x<b.x;
    }
};

inline void init(){
    dlx.init(77);
    memset(vis,0,sizeof vis);
    str.clear();
    tot=0;
    mp.clear();
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            scanf("%s",ans[i][j]);
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<4; k++){
                if(ans[i][j][k]!='.')vis[ans[i][j][k]-'A']=true;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<4; k++){
                pos[i][j][k]=++tot;
            }
        }
    }
    tot=0;
    for(int i=0; i<13; i++){
        int p[3]={0,1,2};
        do{
            for(int x_way=-1; x_way<=xspin[i]; x_way+=2)
            for(int y_way=-1; y_way<=yspin[i]; y_way+=2)
            for(int z_way=-1; z_way<=zspin[i]; z_way+=2){
                for(int X=0; X<4; X++)
                for(int Y=0; Y<4; Y++)
                for(int Z=0; Z<4; Z++){
                    bool f=true;
                    string hsh="";
                    vector<node>v;
                    for(int j=0; x[i][j]!=-1; j++){
                        int now[3]={X,Y,Z};
                        now[p[0]]+=x[i][j]*x_way;
                        now[p[1]]+=y[i][j]*y_way;
                        now[p[2]]+=z[i][j]*z_way;
                        v.push_back(node(now[0],now[1],now[2]));
                        for(int k=0; k<3; k++)if(now[k]<0 || now[k]>=4)f=false;
                        if(vis[i] && ans[now[0]][now[1]][now[2]]!=i+'A')f=false;
                        if(!vis[i] && ans[now[0]][now[1]][now[2]]!='.')f=false;
                        if(!f)break;
                    }
                    if(!f)continue;
                    sort(v.begin(),v.end());
                    for(int j=0; j<v.size(); j++){
                        hsh+='0'+v[j].x;
                        hsh+='0'+v[j].y;
                        hsh+='0'+v[j].z;
                    }
                    if(mp.count(hsh)){
                        f=false;
                    }
                    if(!f)continue;
                    mp[hsh]=true;
                    clear(++tot);
                    for(int j=0; x[i][j]!=-1; j++){
                        int now[3]={X,Y,Z};
                        now[p[0]]+=x[i][j]*x_way;
                        now[p[1]]+=y[i][j]*y_way;
                        now[p[2]]+=z[i][j]*z_way;
                        status[tot][now[0]][now[1]][now[2]]=i+'A';
                        //cerr<<i<<' '<<now[0]<<' '<<now[1]<<' '<<now[2]<<endl;
                        dlx.add(tot,pos[now[0]][now[1]][now[2]]);
                    }
                    //cerr<<i+65<<endl;
                    dlx.add(tot,i+65);
                    //NUM[i]++;
                    //printf("%d %d\n",i,tot);
                }
            }
        }while(next_permutation(p,p+3));
        //cerr<<char(i+'A')<<' '<<NUM[i]<<endl;
    }
}

inline void work(){
    //cerr<<tot<<endl;
    dlx.dance(0);
    //cerr<<Num<<endl;
    if(str.size()==0)puts("No Solution!");
    else{
        printf("%d\n",str.size());
        //cerr<<str.size()<<endl;
        //return;
        sort(str.begin(),str.end());
        bool f=false;
        for(string s:str){
            if(f)puts("");
            for(int i=0; i<64; i++){
                putchar(s[i]);
                if((i+1)%4==0)puts("");
            }
            f=true;
        }
    }
}

int main(){
    #ifdef everlasting
    freopen("./data/hdu.in","r",stdin);
    freopen("./data/std.out","w",stdout);
    #endif
    int T;
    scanf("%d",&T);
    while(T--)
    init(),
    work();
    
    return 0;
}