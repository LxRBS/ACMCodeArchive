/*
    5×5的迷宫，从左上到右下的最短路径
*/

#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

struct _t{
    int pos;
    vector<int> v;
    _t(int aa=0,vector<int>const&cc=vector<int>()):pos(aa),v(cc){}
};

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int A[5][5];
vector<int> Ans;
int bfs(){
    if ( 1 == A[0][0] || 1 == A[4][4] ) return 0;

    queue<_t> q;
    q.push(_t(0));
    A[0][0] = 1;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        int r = u.pos / 5;
        int c = u.pos % 5;

        for(int i=0;i<4;++i){
            int dr = r + DR[i];
            int dc = c + DC[i];

            if ( 4 == dr && 4 == dc ){
                Ans = u.v;
                return 1;
            }

            if ( 0 <= dr && dr < 5 && 0 <= dc && dc < 5 && 0 == A[dr][dc] ){
                A[dr][dc] = 1;
                u.v.push_back(dr*5+dc);
                q.push(_t(dr*5+dc,u.v));
                u.v.pop_back();
            }
        }
    }

    return 0;
}

int main(){
    for(int i=0;i<5;++i)for(int j=0;j<5;++j)scanf("%d",A[i]+j);
    int r = bfs();
    printf("(0, 0)\n");
    for(vector<int>::const_iterator it=Ans.begin();it!=Ans.end();++it) printf("(%d, %d)\n",*it/5,*it%5);
    printf("(4, 4)\n");
    return 0;
}
