/*
  树上博弈，每人走一步，每一步:
  选择一个不为根的节点且到父边权为1，然后将该点到根的路径翻转
  不能走的人输
  40000个点，1s
  给定一棵树，有两种操作：
  0 x:以x为根，谁会获胜，女先男后
  1 xyz：将xy边的权值修改成z
  因为对每一个操作都要博弈一次，所以判断胜负应该是一个相对简单的事
  假设r为根节点，有x条1边和y条0边。
  站在先手的角度，如果操作了某条1边将其变为0，
  则后手只有两种可能：第一种无路可走，第二种操作更下层节点将0再变回1
  后手的每一个第二种操作，先手都必然有路可走。
  所以如果只有1条1边，不管其他下层边如何，先手都必胜
  进一步，x为奇数，先手必胜
  所以根本没有换根操作，只需查询指定节点当前边的权值即可
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

vector<int> Graph[40010];
int N,M;

//以x为根，查询胜负
void f0(int x){
    //奇数女胜，偶数男胜
    printf(Graph[x].size()&1?"Girls win!\n":"Boys win!\n");
}

//v是一行，to是另一个点，w是0或者1
void f(vector<int>&v,int to,int w){
    vector<int>::iterator it = v.begin();
    while(it!=v.end()&&*it!=to)++it;
    if(v.end()==it){
        if(w) v.push_back(to);
    }else{
        if(!w) v.erase(it);
    }
}

void f1(int x,int y,int z){
    f(Graph[x],y,z);
    f(Graph[y],x,z);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        for(int i=1;i<=N;++i)Graph[i].clear();

        for(int i=1;i<N;++i){
            int a=getUnsigned();
            int b=getUnsigned();
            int c=getUnsigned();
            if(c){
                Graph[a].push_back(b);
                Graph[b].push_back(a);
            }
        }

        while(M--){
            int op = getUnsigned();
            int x=getUnsigned();
            if(op){
                int y=getUnsigned();
                int z=getUnsigned();
                f1(x,y,z);
            }else{
                f0(x);
            }
        }
    }
    return 0;
}


