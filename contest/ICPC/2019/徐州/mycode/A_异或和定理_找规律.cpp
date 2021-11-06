/**
    给定区间[L, R]以及S
    求一个最大子区间，使得子区间的异或和不超过S
    异或和定理
    f(n)表示从1到n的异或和，则
    f(n) = n, 1, n+1, 0, 当n模4分别是0,1,2,3
    当n是偶数时，连续4个数异或和为0
    对于给定区间[L, R]，对于左边找一个偶数，要么是L，要么是L+1，定为a
    再在右边找一个b，使得(b+1)%4==a%4，最多有4个候选，于是找到了一个区间[a, b]
    然后对于剩下的情况，做一个暴力，最多8种情况
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

llt getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (llt)(ch-'0');
	return ret;
}

llt f(llt n){
    switch(n%4){
        case 0:return n;
        case 1:return 1;
        case 2:return n+1;
        case 3:return 0;
    }
    return 0;
}

llt f(llt l,llt r,llt c){
    llt a = l & 1 ? l + 1 : l;
    llt b = r;
    llt m = a % 4;
    while( (b+1)%4 != m ) --b;

    if(b<a){//说明区间很小，直接暴力
        llt ans = r - l + 1;
        for(;ans;--ans){
            bool flag = false;
            for(llt i=l;i<=r-ans+1;++i){
                llt sum = 0;
                sum = f(i-1)^f(i+ans-1);
                if(sum<=c){
                    flag = true;
                    break;
                }
            }
            if(flag) return ans;
        }
        return -1;
    }

    llt ans = b-a+1;
    for(llt i=l;i<=a;++i)for(llt j=b;j<=r;++j){
        //计算从i到j的异或和
        llt sum = 0;
        if(i!=a) sum = i;
        if(j!=b) sum = sum ^ f(j) ^ f(b);
        if(sum<=c) ans = max(ans, j-i+1);
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        llt a = getUnsigned();
        llt b = getUnsigned();
        llt c = getUnsigned();
        printf("%lld\n",f(a,b,c));
    }
    return 0;
}

