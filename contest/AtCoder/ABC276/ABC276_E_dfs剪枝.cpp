/**
 * 一个二维数组，#表示障碍物，点表示通路，S表示起点
 * 问是否存在从S开始且到S结束的简单路径，且长度大于等于4
 * 直接从S开始搜，如果能搜回来就可以了。
 * 注意剪枝
 * 当场少了一个剪枝导致超时，于是直接换成了打边双的模板
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
int const SIZE = 23;
#else
int const SIZE = 1E6+13;
#endif

int H, W, N;
char A[SIZE];
bool Flag[SIZE] = {false};
int SPos;

int const DR[] = {-1, 1, 0, 0};
int const DC[] = {0, 0, -1, 1};

bool dfs(int r, int c, int cur){
    char * ch;
    for(int nx,ny,i=0;i<4;++i){
        nx = r + DR[i];
        ny = c + DC[i];
        if(0 <= nx && nx < H && 0 <= ny && ny < W){
            if('S' == *(ch=A+nx*W+ny)){
                if(cur >= 3) return true;
                continue;
            }
            if('#' == *ch) continue;
            if(Flag[ch-A]) continue;
 
            *ch = '#';
            bool b = dfs(nx, ny, cur+1);
            *ch = '.'; 
            if(b) return true;
        } 
    }
    Flag[r*W+c] = true; // 加这个剪枝，表示该点肯定是不通的
    return false;
}

bool proc(){
    N = H * W;
    for(int i=0;i<N;++i){
        if('S' == A[i]){
            SPos = i;
            break;
        }
    }
    bool b = dfs(SPos/W, SPos%W, 0);
    return b;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    scanf("%d%d", &H, &W);
    char * p = A;
    for(int i=0;i<H;++i) {
        scanf("%s", p);
        p += W;    
    }
    puts(proc()?"Yes":"No");
    return 0;
}