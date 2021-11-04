/*
  将一个完全图拆成两个有向图（无公共边）
  问两个图是否都是传递的。
  所谓传递就是：ab有边、bc有边，则ac必须有边
  如果是传递的，则有ab、bc、ac有边，如果cd还有边，则bd必然有边，则ad必然有边
  也就是说从a开始，到其他相连的点，路径最多为1
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int const SIZE = 2100;

char S[SIZE];
int N;
vector<int> GP[SIZE];
vector<int> GQ[SIZE];

bool Flag[SIZE];
int Q[SIZE];
int D[SIZE];

bool bfs(int s,vector<int> v[]){
    int *head = Q, *tail = Q;
    fill(Flag,Flag+N+1,false);

    //首先将s的下一级节点塞到队列
    for(vector<int>::const_iterator it=v[s].begin();it!=v[s].end();++it){
        Flag[*tail++ = *it] = true;
    }

    //然后挨个检查是否有二级节点存在
    //如果与一级节点相连，又不在队列中，则必然是二级节点，则必然不是传递的
    while(head<tail){
        int u = *head++;
        for(vector<int>::const_iterator it=v[u].begin();it!=v[u].end();++it){
            if(!Flag[*it]) return false;
        }
    }
    return true;
}

bool proc(){
    for(int i=0;i<N;++i){
        if(!bfs(i,GP)) return false;
        if(!bfs(i,GQ)) return false;
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d",&N);
        for(int i=1;i<=N;++i){
            GP[i].clear();
            GQ[i].clear();

            scanf("%s",S);
            int k = 1;
            for(char *p=S;*p;++p,++k){
                if('P'==*p){
                    GP[i].push_back(k);
                }else if('Q'==*p){
                    GQ[i].push_back(k);
                }
            }
        }
        printf(proc()?"T\n":"N\n");
    }
    return 0;
}


