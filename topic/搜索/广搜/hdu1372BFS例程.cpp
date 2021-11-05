#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct _t{
	int r,c;
	int t;
	_t(int rr,int cc,int tt=0):r(rr),c(cc),t(tt){}
};
_t Dest(0,0);

inline int tr(char ch){
	return ( ch <= '8' ) ? ( ch - '1' ) : ( ch - 'a' );
}
inline bool isNotValid(int r,int c){
    return r < 0 || r >= 8 || c < 0 || c >= 8;
}

char Input[10];
bool B[8][8];
int DR[] = {-1,-2,-2,-1,1,2,+2,+1};
int DC[] = {-2,-1,+1,+2,2,1,-1,-2};

int bfs(){
    memset(B,0,sizeof(B));
    //头节点入队
    queue<_t> q;
    int r = tr(Input[0]);
    int c = tr(Input[1]);
    B[r][c] = true;
    q.push(_t(r,c,0));

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        for(int i=0;i<8;++i){
        	int nr = u.r + DR[i];
        	int nc = u.c + DC[i];
        	if ( Dest.r == nr && Dest.c == nc ) return u.t + 1;
        	if ( isNotValid(nr,nc) || B[nr][nc] ) continue;
        	q.push(_t(nr,nc,u.t+1));
        	B[nr][nc] = true;
        }
    }
	return 0;
}
int main() {
    while ( gets(Input) ){
    	Input[2] = '\0';
    	if ( Input[0] == Input[3] && Input[1] == Input[4] ){
    		printf("To get from %s to %s takes 0 knight moves.\n",Input,Input+3);
    		continue;
    	}
    	Dest.r = tr(Input[3]);
    	Dest.c = tr(Input[4]);
    	printf("To get from %s to %s takes %d knight moves.\n",Input,Input+3,bfs());
    }
	return 0;
}
