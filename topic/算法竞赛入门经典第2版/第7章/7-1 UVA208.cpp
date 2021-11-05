//标准的图深搜，给定图，求从1到指定点的所有路径，但1和终点有可能不相连

#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int Father[25];
void init(){for(int i=1;i<25;++i)Father[i]=i;}
int find(int k){return k==Father[k]?k:Father[k]=find(Father[k]);}
void unite(int x,int y){Father[find(x)]=find(y);}

bool A[25][25];

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    init();
    memset(A,0,sizeof(A));

    int a,b;
    while( scanf("%d%d",&a,&b),a,b ){
        A[a][b] = A[b][a] = true;
        unite(a,b);
    }

    return true;
}

bool F[25];
vector<int> V;
int Ans;
void dfs(int node){
    if ( N == node ){
        putchar('1');
        for(vector<int>::iterator it=++V.begin();it!=V.end();++it)printf(" %d",*it);
        putchar('\n');
        ++Ans;
        return;
    }

    for(int i=2;i<21;++i)if(!F[i]&&A[node][i]){
        V.push_back(i);
        F[i] = true;
        dfs(i);
        F[i] = false;
        V.erase(V.end()-1);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("CASE %d:\n",kase);
        Ans = 0;

        if ( find(1) != find(N) ) goto L;

        memset(F,0,sizeof(F));
        V.clear();V.push_back(1);
        F[1] = true;
        dfs(1);

        L:
        printf("There are %d routes from the firestation to streetcorner %d.\n",Ans,N);
    }
    return 0;
}