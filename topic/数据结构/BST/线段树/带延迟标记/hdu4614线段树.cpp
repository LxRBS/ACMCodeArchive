/*
    N个花瓶排成一排
    1 A F：表示从A开始，每个空瓶子放一个花，直到放完，或者瓶子到了尽头
    2 A B：表示把[A,B]区间内的瓶子清空

    对每一个1操作，输出放花的起点和终点
    对每一个2操作，输出丢掉的花的数量

    使用线段树，记录区间和
    对2操作，相当于先求和，再更新
    对1操作，首先要找到操作的起点first
    然后确定终点last
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 50011;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int ST[SIZE<<2];//线段树，区间和
int Lazy[SIZE<<2];

inline void _pushUp(int t){
    ST[t] = ST[lson(t)] + ST[rson(t)];
}

inline void _pushDown(int t,int s,int e){
    if ( Lazy[t] ){
        int mid = ( s + e ) >> 1;
        int tmp = Lazy[t] & 1;

        ST[lson(t)] = ( mid - s + 1 ) * tmp;
        ST[rson(t)] = ( e - mid ) * tmp;
        Lazy[lson(t)] = Lazy[rson(t)] = Lazy[t];

        Lazy[t] = 0;
    }
}

//将[a,b]区间都设置为newValue
void modify(int t,int s,int e,int a,int b,int newValue){
    if ( a <= s && e <= b ){
        ST[t] = ( e - s + 1 ) * ( newValue & 1 );
        Lazy[t] = newValue;
        return;
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(t),s,mid,a,b,newValue);
    if ( mid < b ) modify(rson(t),mid+1,e,a,b,newValue);
    _pushUp(t);
}

int query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return ST[t];
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    int ans = 0;
    if ( a <= mid ) ans += query(lson(t),s,mid,a,b);
    if ( mid < b ) ans += query(rson(t),mid+1,e,a,b);
    return ans;
}

//从a开始放置f朵花
void proc(int n,int a,int f){
    //找到操作的起点first
    //定义函数f(x) = [a,x]的长度 - S(a,x)
    //f(x)实际上就是区间[a,x]中0的数量，当f(x)第一次等于1的位置就是起点
    //二分搜索f(x)>0的最左位置
    int left = a, right = n, mid;
    do{
        mid = ( left + right ) >> 1;
        if ( mid - a + 1 - query(1,1,n,a,mid) > 0 ) right = mid - 1;
        else left = mid + 1;
    }while( left <= right );

    if ( n + 1 == left ){
        puts("Can not put any one.");
        return;
    }

    int first = left;

    //首先检查放置的花朵数量
    int tmp;
    if ( (tmp=query(1,1,n,first,n)) + f > n - first + 1 ){
        f = n - first + 1 - tmp;
    }

    //搜索放置的终点
    //定义函数f(x) = f + S(first,x) - [first,x]的长度
    //f(x)就是区间安排后还剩下的花的数量，找到f(x)第一个为0的位置即可，也就是最后一个为1的位置加1
    right = n;
    do{
        mid = ( left + right ) >> 1;
        if ( f + query(1,1,n,first,mid) - (mid-first+1) > 0 ) left = mid + 1;
        else right = mid - 1;
    }while( left <= right );

    printf("%d %d\n",first-1,right);
    modify(1,1,n,first,right+1,1);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        int m = getUnsigned();
        int k,a,b;

        fill(Lazy,Lazy+n*4+1,0);
        fill(ST,ST+n*4+1,0);

        while(m--){
            k = getUnsigned();
            a = getUnsigned() + 1;
            b = getUnsigned() + (2==k?1:0);

            if ( 2 == k ){//清空
                printf("%d\n",query(1,1,n,a,b));
                modify(1,1,n,a,b,2);
            }else{
                proc(n,a,b);
            }
        }

        putchar('\n');
    }
    return 0;
}
