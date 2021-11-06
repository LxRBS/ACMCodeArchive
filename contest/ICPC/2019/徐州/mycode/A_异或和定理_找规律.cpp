/**
    ��������[L, R]�Լ�S
    ��һ����������䣬ʹ������������Ͳ�����S
    ���Ͷ���
    f(n)��ʾ��1��n�����ͣ���
    f(n) = n, 1, n+1, 0, ��nģ4�ֱ���0,1,2,3
    ��n��ż��ʱ������4��������Ϊ0
    ���ڸ�������[L, R]�����������һ��ż����Ҫô��L��Ҫô��L+1����Ϊa
    �����ұ���һ��b��ʹ��(b+1)%4==a%4�������4����ѡ�������ҵ���һ������[a, b]
    Ȼ�����ʣ�µ��������һ�����������8�����
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

    if(b<a){//˵�������С��ֱ�ӱ���
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
        //�����i��j������
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

