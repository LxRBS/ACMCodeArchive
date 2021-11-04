/**
   一个图最多16个节点，初始，所有节点都被感染。然后按如下流程进行，
   选择K个节点进行净化，然后每个感染节点会把其邻居感染，且本身会变好。
   如此进行，问能否在100步内将所有节点净化。
   暴力广搜
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}


int N,M,K;
bool Graph[20][20];

string Step[(1<<16)+10];
int Pre[(1<<16)+10];
int D[(1<<16)+10];

void mkVector(int status,vector<int>&vec,vector<int>&vp){
    vec.clear();
    for(int i=0;i<N;++i){
        if(status&(1<<i)){
            vec.push_back(i);
        }
    }
    /// vp前面都是0，后面有k个1
    int n = vec.size();
    if(K>=n){
        vp.assign(n, 1);
        return;
    }
    vp.assign(n, 1);
    fill(vp.begin(),vp.begin()+n-K,0);
}

/// 传播
int go2step(int oldstatus){
    int status = 0;
    for(int i=0;i<N;++i){
        if((1<<i)&oldstatus){ // 所有邻居
            for(int j=1;j<=N;++j){
                if(Graph[i+1][j]){
                    status |= (1<<(j-1));
                }
            }
        }
    }
    return status;
}

/// 选择vp中的节点进行消毒
int go1step(int oldstatus, vector<int>const&vec,vector<int>const&vp,string&step){
    assert(vec.size()==vp.size());
    step.clear();
    for(int i=0,n=vec.size();i<n;++i){
        if(!vp[i]) continue;
        if(oldstatus&(1<<vec[i])) {
            oldstatus ^= 1<<vec[i];
            //step.append((char)('a'+vec[i]));
            step += (char)('a'+vec[i]);
        }
    }
    return go2step(oldstatus);
}

int Z[17];
void output(int pos){
    //if(pos<0)while(1);
    if(pos==Z[N]||-1==Pre[pos]){
        return;
    }
    output(Pre[pos]);
    cout<<Step[pos]<<endl;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int i=0;i<17;++i)Z[i] = (1<<i) - 1;
    N = getUnsigned();
    M = getUnsigned();
    K = getUnsigned();
    for(int a,b,i=0;i<M;++i){
        a = getUnsigned();
        b = getUnsigned();
        Graph[a][b] = Graph[b][a] = true;
    }

    fill(D,D+(1<<16)+1,10000);
    fill(Pre,Pre+(1<<16)+1,-1);

    queue<int> q;
    q.push(Z[N]);
    D[Z[N]] = 0;

    vector<int> vec, vp;
    string step;
    while(!q.empty()){
        int status,h = q.front();q.pop();
        mkVector(h, vec, vp);
        do{
            if(1+D[h]<D[status = go1step(h, vec,vp,step)]){
                D[status] = 1 + D[h];
                Step[status].assign(step.begin(), step.end());
                Pre[status] = h;
                if(0==status) {
                    break;
                }
                if(D[status]<=100){
                    q.push(status);
                }
            }
        }while(next_permutation(vp.begin(),vp.end()));
    }

    if(10000==D[0]) {
        printf("-1\n");
        return 0;
    }
    cout<<D[0]<<endl;
    output(0);
    return 0;
}
