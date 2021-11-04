/**
   最短路，Dij
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

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

typedef long long llt;
int const SIZE = 510;

int A[SIZE][SIZE];
int B[SIZE][SIZE];
llt D[SIZE][SIZE];
int C[SIZE][SIZE];
int W[SIZE][SIZE];
llt Dis[SIZE][SIZE];

bool Flag[SIZE][SIZE];

int N,M,XS,YS,XT,YT;

struct _t{
    int x, y;
    llt w;
    _t(int a=0,int b=0,llt c=0):x(a),y(b),w(c){}
};

bool operator < (const _t&lhs, const _t&rhs){
    return lhs.w > rhs.w;
}

void disp(){
    cout<<"Dis"<<endl;
    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j){
            cout<<Dis[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    XS = getUnsigned();
    YS = getUnsigned();
    XT = getUnsigned();
    YT = getUnsigned();
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        A[i][j] = getUnsigned();
    }
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        B[i][j] = getUnsigned();
    }
    for(int i=1;i<=N;++i)for(int j=1;j<M;++j){
        C[i][j] = getUnsigned();
    }
    for(int i=1;i<N;++i)for(int j=1;j<=M;++j){
        W[i][j] = getUnsigned();
    }


    if(XS==XT&&YS==YT) {
        printf("0\n");
        return 0;
    }

    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        D[i][j] = A[i][j] + B[i][j];
        Flag[i][j] = false;
        Dis[i][j] = 0x7FFFFFFFFFFFFFFF;
    }

    priority_queue<_t> q;
    q.push(_t(XS,YS,Dis[XS][YS] = 0));

    int x, y;
    while(1){
        while(!q.empty() && Flag[q.top().x][q.top().y]) q.pop();
        if(q.empty()) break;

        _t h(q.top());q.pop();
        Flag[x=h.x][y=h.y] = true;

        /// 判断最近的可以去上下行的时间，w对a+b取余数
        llt left = h.w % D[x][y];
        bool flag = left < A[x][y];
        llt step = flag ? h.w : D[x][y] - left + h.w;
        llt tmp;
        /// step是去上下两行的最早时间
        if(h.x>1){
            if(!Flag[x-1][y]&&(tmp=step+W[x-1][y])<Dis[x-1][y]){
                q.push(_t(x-1,y,Dis[x-1][y]=tmp));
            }
        }
        if(h.x<N){
            if(!Flag[x+1][y]&&(tmp=step+W[x][y])<Dis[x+1][y]){
                q.push(_t(x+1,y,Dis[x+1][y]=tmp));
            }
        }
        /// 判断去左右两列的时间
        step = flag ? A[x][y] - left + h.w : h.w;
        if(h.y>1){
            if(!Flag[x][y-1]&&(tmp=step+C[x][y-1])<Dis[x][y-1]){
                q.push(_t(x,y-1,Dis[x][y-1]=tmp));
            }
        }
        if(h.y<M){
            if(!Flag[x][y+1]&&(tmp=step+C[x][y])<Dis[x][y+1]){
                q.push(_t(x,y+1,Dis[x][y+1]=tmp));
            }
        }
    }
    cout<<Dis[XT][YT]<<endl;
    //disp();
    return 0;
}
