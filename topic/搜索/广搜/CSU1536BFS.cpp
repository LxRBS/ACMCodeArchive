#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int BIT[][16] = {
    {0},
    {0,1,3,7,0xF,0x1F,0x3F,0x7F,0xFF,0x1FF,
    0x3FF,0x7FF,0xFFF,0x1FFF,0x3FFF,0x7FFF}    
};
struct _t{
    int status;
    int step;
    _t(int a=0,int b=0):status(a),step(b){}       
};
//把status的第idx位和第idx+1位互换 
inline int f(int status,int idx){
    int a = ( status >> idx ) & 1;
    int b = ( status >> idx + 1 ) & 1;
    if ( a == b ) return status;
    status ^= 1 << idx;
    return status ^= 1 << idx + 1;
}
int N,M;
int start=0,end0=0,end1=0;
bool F[65536] = {false};
int bfs(){
    if ( start == end0 || start == end1 ) return 0;
    queue<_t> q;
    q.push(_t(start));
    F[start] = true;
    
    while( !q.empty() ){
        _t u = q.front();
        q.pop();
        
        for(int i=0;i<N-1;++i){
            int st = f(u.status,i);
            if ( st == end0 || st == end1 ) return u.step + 1;
            if ( !F[st] ){
                q.push(_t(st,u.step+1));
                F[st] = true;     
            }         
        }       
    }
}
int main(){
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;++i){
        int b;
        scanf("%d",&b);
        start = ( start << 1 ) | b;        
    }
    for(int i=0;i<M;++i){
        int c;
        scanf("%d",&c);    
        int x = i & 1;
        end0 = ( end0 << c ) | BIT[x][c];
        end1 = ( end1 << c ) | BIT[x^1][c]; 
    }
    printf("%d\n",bfs());
    return 0;    
}
