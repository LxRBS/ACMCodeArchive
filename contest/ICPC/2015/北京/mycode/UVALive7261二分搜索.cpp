/**
  有N个矩形在一个大矩形内，
  画一条竖线将整个区域分成两半，使得：
  1 左边的小矩形面积之和大于等于右边，且差别尽可能小
  2 左边的面积尽可能大
  N在1万以内，坐标在100万以内
  小矩形可以被切分为两半
  设总面积为S，左边的面积根据竖线位置变化设为f(x)
  则两边之差为2f(x)-S，这是一个增函数
  现在要找满足2f(x)-S>=0的最大整数，可以用二分
  复杂度应该是1万×log(100万)，大概是20万
*/

#include <stdio.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef unsigned long long int ull;

ull Area;
int N,R;
ull L[10010],T[10010],W[10010],H[10010],B[10010];
ull S[10010];

//给定x，计算x左边的面积和是否大于右边
bool check(int x){
    ull s = 0ULL;
    for(int i=0;i<N;++i){
        if(B[i]<=x){
            s += S[i];
        }else if(L[i]<x){
            s += H[i] * ( x - L[i] );
        }
    }
    return ( s << 1 ) >= Area;
}

//返回最靠左的使得左边大于等于右边的x
int binary_search(){
    int left = 0, right = R, mid;
    do{
        mid = ( left + right ) >> 1;
        if( check(mid) ) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    return left;
}

//x是否将左边面积分为area
bool check(ull area,int x){
    ull s = 0ULL;
    for(int i=0;i<N;++i){
        if(B[i]<=x){
            s += S[i];
        }else if(L[i]<x){
            s += H[i] * ( x - L[i] );
        }
    }
    return s == area;
}
//已知x是最靠左的使得左边大于等于右边，现在要求最靠右的
int binary_search(int x){
    //首先计算x分得左边的面积差是多少
    ull s = 0ULL;
    for(int i=0;i<N;++i){
        if(B[i]<=x){
            s += S[i];
        }else if(L[i]<x){
            s += H[i] * ( x - L[i] );
        }
    }

    int left = x, right = R, mid;
    do{
        mid = ( left + right ) >> 1;
        if( check(s,mid) ) left = mid + 1;
        else right = mid - 1;
    }while(left<=right);
    return right;
}

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        Area = 0ULL;
        R = getUnsigned();
        N = getUnsigned();
        for(int i=0;i<N;++i){
            L[i] = getUnsigned();
            T[i] = getUnsigned();
            W[i] = getUnsigned();
            H[i] = getUnsigned();
            B[i] = L[i] + W[i];
            Area += ( S[i] = W[i] * H[i] );
        }

        //这是最靠左的x，答案应该是最靠右的x
        int x = binary_search();
        //在做一次二分搜索
        printf("%d\n",binary_search(x));
    }
    return 0;
}
