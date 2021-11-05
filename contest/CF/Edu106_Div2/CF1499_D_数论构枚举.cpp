/**
    ����c��d��x�����ж��ٶ�������(a, b)����
    clcm(a,b) - dgcd(a,b) = x
    ��gcd(a,b) = g, �� a = ug, b = vg
    ������ uv = (x/g + d) / c����uv����
    ��x��ÿһ�����ӣ������uv��ֵ��������ж��ٶԲ�ͬ��uv
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef long long int llt;
llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (llt)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

int const SIZE = 20000010;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
int FCnt[SIZE];//��ͬ�������ӵĸ���
void sieve(){
    for(llt i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i, FCnt[i] = 1;

        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ){ 
                FCnt[i*P[j]] = FCnt[i];
                break;
            }else{
                FCnt[i*P[j]] = FCnt[i] + 1;
            }
        }
    }
}

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

inline llt f(llt c,llt d,llt x){
    llt g = gcd(c, gcd(d, x));
    c /= g, d /= g, x /= g;

    llt ans = 0;
    /// ��x��ÿһ������
    for(llt uv,i=1;i*i<=x;++i){
        if(x%i) continue;

        if(0==(x/i+d)%c){
            uv = (x/i+d)/c;
            ans += (1LL<<FCnt[uv]);
        }        

        if(i*i==x||(i+d)%c) continue;

        uv = (i+d)/c;
        ans += (1LL<<FCnt[uv]);        
    }
    return ans;
}

int main(){
    // freopen("1.txt","r",stdin);
    // freopen("2.txt","w",stdout);
	sieve();
    // for(int i=12;i<=20;++i)cout<<FCnt[i]<<" ";
    //*
    int nofkase = getULL();
	while(nofkase--){
		llt c = getULL();
		llt d = getULL();
		llt x = getULL();
		printf("%lld\n",f(c,d,x));
	}//*/
    return 0;
}
