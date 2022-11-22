/**
 * 给一个H*W的二维数组，每个元素是一个正整数
 * 再给一个小长方形h*w，问用小方形依次遮住相应位置，
 * 大数组中剩下的元素的不同取值的数量
 * 暴力法即可。取值范围均为300以内。
 * 首先求出数组每个元素的数量，再依次求出每个小方形的元素数量，即时判断即可
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
int const SIZE = 33;
#else
int const SIZE = 310;
#endif

using si = unordered_set<int>;
using msi = unordered_map<int, si>;
using llt = long long;

int H, W, N;
int A[SIZE][SIZE];
int C[SIZE];
int h, w;
int Total = 0;

int proc(int r, int c){
    int d[SIZE] = {0};
    int tmp = 0;
    for(int i=r;i<r+h;++i){
        for(int j=c;j<c+w;++j){
            if(C[A[i][j]] == ++d[A[i][j]]){
                ++tmp;
            }
        }
    }
    return Total - tmp;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    H = getInt();
    W = getInt();
    N = getInt();
    h = getInt();
    w = getInt();
    for(int i=0;i<H;++i)for(int j=0;j<W;++j){
        if(1 == ++C[A[i][j] = getInt()]){
            ++Total;
        }
    }

    for(int i=0;i<=H-h;++i){
        for(int j=0;j<=W-w;++j){
            int t = proc(i, j);
            printf("%d ", t);
        }
        printf("\n");
    }
    return 0;
}
