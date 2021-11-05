/*
    M种长方体，每种N个，问最多堆多高
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N;
struct _t{
    int x,y,z;
}A[100];
bool operator < (_t const&lhs, _t const&rhs){
    int la = lhs.x * lhs.y;
    int ra = rhs.x * rhs.y;
    return la < ra || ( la == ra && lhs.x < rhs.x ) || ( la == ra && lhs.x == rhs.x && lhs.y < rhs.y );
}

inline bool cmp(_t const&lhs,_t const&rhs){
    return ! ( lhs < rhs );
}

void f(int x,int y,int z,_t&a,_t&b,_t&c){
    a.x = x; a.y = y; a.z = z;
    if ( a.x < a.y ) swap(a.x,a.y);

    b.x = y; b.y = z; b.z = x;
    if ( b.x < b.y ) swap(b.x,b.y);

    c.x = z; c.y = x; c.z = y;
    if ( c.x < c.y ) swap(c.x,c.y);
}
bool read(){
    N = getUnsigned();
    if ( 0 == N ) return false;

    int x,y,z;
    for(int i=0;i<N;++i){
        x = getUnsigned();
        y = getUnsigned();
        z = getUnsigned();
        f(x,y,z,A[3*i],A[3*i+1],A[3*i+2]);
    }
    sort(A,A+3*N,cmp);
    return true;
}

inline bool isValid(_t const&bottom,_t const&top){
    return top.x < bottom.x && top.y < bottom.y;
}

int D[100];//Di表示以第i个箱子结束的最大高度
//因为要判断新的箱子是否能往上堆，所以状态必须取以i结尾的，而不能取最多到i的

void dp(){
    for(int i=0;i<3*N;++i){
        D[i] = 0;
        for(int j=0;j<i;++j){
            if ( isValid(A[j],A[i]) ) D[i] = max(D[i],D[j]);
        }
        D[i] += A[i].z;
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        dp();
        printf("Case %d: maximum height = %d\n",kase,*max_element(D,D+3*N));
    }
    return 0;
}
