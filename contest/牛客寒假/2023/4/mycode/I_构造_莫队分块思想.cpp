/**
 * 二维平面第一象限给定M个点，起点在(0, 0)，移动是循环移动机制
 * 要求构造一个移动方案，使得可以遍历这M个点，且次数不超过2E6
 * 坐标范围在[0, 1E4)， M与N同级
 * 同时有一个限制，只能用三个方向，即有一个方向被禁止了。
 * 因为从边界移出，会从另外一边移进，所以肯定禁止一个方向，还是可以有解的
 * 如果将(r, c)按序排好，显然移动次数有可能达到N^2，会超范围。
 * 按照莫队算法构造移动方案，可以做到O(Nsqrt(N))量级。
 * 假设Col方向不能向做移动，将Row方向按分块排序，Col方向从小到大排序
 * 则在每一个块中，Row坐标会在sqrt(N)的方位内来回移动，而Col坐标会一直向右移动
 * 假设坐标是均匀分布的，则一个块中有sqrt(N)个点，则Row坐标最多移动O(N)
 * 如果该块集中了所有N个点，Row坐标会移动O(Nsqrt(N))，但是其他块就都为0了
 * 当然存在严谨的证明，总之这样构造是O(Nsqrt(N))。
 * 每一块结束之后，将Col坐标向右一直移，就可以回到0位置，开始下一个块。
 * 本来想写一个函数，利用输入及参数统一处理4个方向，但是D方向一直不对。
 * 所以单独又写了一个函数。
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();    
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
int const BLOCK_SIZE = 3;
#else
int const SIZE = 2.01E6+10;;
int const BLOCK_SIZE = 100;
#endif

using pii = pair<int, int>;
using vpii = vector<pii>;

int N, M;
char X;
vpii A;
char Output[SIZE];

void proc(char forward, char backward, char another, int s, int e){
    sort(A.begin(), A.end(), [](const pii & a, const pii & b){
        auto an = a.first / BLOCK_SIZE;
        auto bn = b.first / BLOCK_SIZE;
        if(an != bn) return an < bn;
        return a.second < b.second;
    });

    int k = 0, step = 0;
    for(const auto & p : A){
        if(e < p.second){
            step = p.second - e;
            fill(Output+k, Output+k+step, another);
            k += step; e = p.second; 
        }
        if(s > p.first){
            step = s - p.first;
            fill(Output+k, Output+k+step, backward);
            k += step; s = p.first;
        }
        if(e > p.second){
            step = N - e;
            fill(Output+k, Output+k+step, another);
            k += step; e = 0;

            step = p.second - e;
            fill(Output+k, Output+k+step, another);
            k += step; e = p.second; 
        }
        if(s < p.first){
            step = p.first - s;
            fill(Output+k, Output+k+step, forward);
            k += step; s = p.first;
        }
    }
    return;
}

void procD(){
    sort(A.begin(), A.end(), [](const pii & a, const pii & b){
        auto an = a.second / BLOCK_SIZE;
        auto bn = b.second / BLOCK_SIZE;
        if(an != bn) return an < bn;
        return a.first > b.first;
    });

    int s = 0, e = 0;
    int k = 0, step = 0;
    for(const auto & p : A){
        if(e < p.second){
            step = p.second - e;
            fill(Output+k, Output+k+step, 'R');
            k += step; e = p.second; 
        }
        if(s > p.first){
            step = s - p.first;
            fill(Output+k, Output+k+step, 'U');
            k += step; s = p.first;
        }
        if(e > p.second){
            step = e - p.second;
            fill(Output+k, Output+k+step, 'L');
            k += step; e = p.second; 
        }
        if(s < p.first){
            step = s + 1;
            fill(Output+k, Output+k+step, 'U');
            k += step; s = N - 1;

            step = s - p.first;
            fill(Output+k, Output+k+step, 'U');
            k += step; s = p.first;
        }
    }
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt(); X = getChar();
    A.assign(M, {0, 0});
    
    switch(X){
        case 'U':for(auto & p : A) p.second = getInt(), p.first = getInt();proc('R', 'L', 'D', 0, 0);break;
        case 'D':for(auto & p : A) p.first = getInt(), p.second = getInt();procD();break;
        case 'L':for(auto & p : A) p.first = getInt(), p.second = getInt();proc('D', 'U', 'R', 0, 0);break;
        case 'R':for(auto & p : A) p.first = getInt(), p.second = N - 1 - getInt();proc('D', 'U', 'L', 0, N - 1);break;
    }
    puts(Output);
    return 0;
}