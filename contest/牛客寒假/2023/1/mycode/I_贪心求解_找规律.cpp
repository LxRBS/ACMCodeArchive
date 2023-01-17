/**
 * N*N(N<=100)的矩阵，有若干个要求，要求分两类：
 * 1 x y z: A[x][y] = z
 * 2 x y: 要求A[x][y]是第x行的最大值，且是第y列的最小值
 * 给出一个符合条件的矩阵，如果不存在输出全0
 * 首先要证明第2类要求不能超过1个，否则必然全0
 * 假设有两个要求2，分别是Aij和Auv，则根据要求，需要
 * Aij > Aiv 且 Auv < Aiv，所以Aij > Auv，同时又有
 * Auv > Auj 且 Aij < Auj，所以Auv > Aij，矛盾。
 * 考虑有一个要求2的情况且该位置上没有值的情况，使用贪心
 * 先用最小的能用的值填充行的其他位置，然后再用可以用的最小值填充要求2
 * 然后再用能用的最大的值填充列的其他位置，如果有矛盾，表明肯定不行。
 * 否则就得到了一个填充方案，再填充剩下的数即可。
 * 如果没有要求2，直接填充剩下的数即可
 * 如果有一个要求2且要求2上已经有数了，则同样将尽可能小的值填充行，尽可能大的值填充列
 * 如果没有矛盾，填充剩下的即可。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 110;
#endif

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int N, M;
vvi A;
vi Flag;
int Row, Col;

bool procLeft(){
    int k = 1;
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        if(A[i][j]) continue;
        while(Flag[k]) ++k;
        if(k > N * N) return false;
        Flag[A[i][j] = k] = 1;
    }
    // for(int i=1,n=N*N;i<=n;++i)if(Flag[i]!=1)return false;
    // for(const auto & vec : A)for(int i : vec)if(0 == i)return false;
    // if(Row != -1){
    //     assert(-1 != Col);
    //     auto v = A[Row][Col];
    //     for(int c=0;c<N;++c){
    //         if(c == Col) continue;
    //         if(v <= A[Row][c]) return false;
    //     }
    //     for(int r=0;r<N;++r){
    //         if(r == Row) continue;
    //         if(v >= A[r][Col]) return false;
    //     }
    // }
    return true;
}

bool proc(){
    if(-1 == Row){
        assert(-1 == Col);        
        return procLeft();
    }

    if(A[Row][Col]){
        const int v = A[Row][Col];
        int k = 1;
        for(int c=0;c<N;++c){
            if(c == Col) continue;
            if(A[Row][c]){
                if(A[Row][c] >= v) return false;
                continue;
            }
            while(Flag[k]) ++k;
            if(k >= v) return false;
            Flag[A[Row][c] = k] = 1;
        }    
        int h = N * N;
        for(int r=0;r<N;++r){
            if(r == Row) continue;
            if(A[r][Col]){
                if(A[r][Col] <= v) return false;
                continue;
            }
            while(Flag[h]) --h;
            if(h <= v) return false;
            Flag[A[r][Col] = h] = 1;
        }  
        return procLeft();
    }

    int k = 1;
    int to = 0;
    for(int c=0;c<N;++c){
        if(c == Col) continue;
        if(A[Row][c]){
            to = max(to, A[Row][c] + 1);
            continue;
        }
        while(Flag[k]) ++k;
        if(k > N * N) return false;
        Flag[A[Row][c] = k] = 1;
    }
    to = max(to, k);
    while(Flag[to]) ++to;
    if(to > N * N) return false;
    Flag[A[Row][Col] = to] = 1;

    int h = N * N;
    for(int r=0;r<N;++r){
        if(r == Row) continue;
        if(A[r][Col]){
            if(A[r][Col] <= to) return false;
            continue;
        }
        while(Flag[h]) --h;
        if(h <= to) return false;
        Flag[A[r][Col] = h] = 1;
    }

    return procLeft();
}

void output0(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j)printf("0 ");
        printf("\n");
    }
}

void output(){
    for(const auto & vec : A){
        for(int i : vec)printf("%d ", i);
        printf("\n");
    }        
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        A.assign(N, vi(N, 0));
        Flag.assign(N*N+2, 0);
        Row = Col = -1;
        int cc = 0;
        for(int c,x,y,i=0;i<M;++i){
            c = getInt(); x = getInt() - 1; y = getInt() - 1;
            if(2 == c){
                Row = x, Col = y;
                ++cc;
            }else{
                if(++Flag[A[x][y] = getInt()] >= 2) cc = 9;
            }
        }
        if(cc >= 2 || !proc()) output0();
        else output();
    }
    return 0;
}


