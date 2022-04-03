/**
 * N*N的棋盘，N在2000。给定起点和终点，还有若干障碍物
 * 问国际象棋的象从起点到终点的最少步数
 * 首先利用奇偶性判断肯定不可达
 * 在可能可达的情况下使用广搜即可
 * 因为使用了成批扩展，可能搜索了很多不需要的节点
 * 6s时限，5891ms
 * 标程对前进方向进行了记录，相同前进方向则步数不加，不同前进方向步数加1
 * 一格一格进行扩展，只需1600ms即可
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 20;
#else
int const SIZE = 1500+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int const DR[] = {-1, -1, +1, +1};
int const DC[] = {-1, +1, -1, +1};

int N, Ax, Ay, Bx, By;
char A[SIZE][SIZE];
int Flag[SIZE][SIZE];

pii Q[SIZE*SIZE];

int proc(){
    --Ax; --Ay; --Bx; --By;
	if(((Ax+Ay)&1) != ((Bx+By)&1)) return -1;
	
    int k = 0;
	pii *head = Q, *tail = Q;
	Flag[Ax][Ay] = 1;*tail++ = {Ax, Ay};
	while(head != tail){
		++k;
		int sz = tail - head;
		while(sz--){				
			int x = head->first;
			int y = head->second;
			++head;
			for(int i=0;i<4;++i){
				for(int nx=x,ny=y;0<=nx&&nx<N&&0<=ny&&ny<N&&'.'==A[nx][ny];nx+=DR[i],ny+=DC[i]){
					if(nx == Bx && ny == By) return k;
					if(!Flag[nx][ny]){
						Flag[nx][ny] = 1;
						*tail++ = {nx, ny};
					}
				}
			}
		}
	}
	return -1;
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d%d%d%d%d", &N, &Ax, &Ay, &Bx, &By);
	for(int i=0;i<N;++i)scanf("%s", A[i]);
	printf("%d\n", proc());
    return 0;
}

