/**
    ��123...nΪ���S
    �ٸ���һ�����г���Target����T
    �ٸ���һ����K��
    ��һ���û�x��ʹ�ô�S��Tǡ�þ�����K��x�任
    ��cΪһ���û�����S��T���൱���󷽳�x^K=c�Ľ�
    ��c���Է�Ϊm���ֻ���ÿ���ֻ��ĳ���ΪLi��
    �������ݷ�ΧLi��K��Ȼ���ʣ���ΪK��������K>Li
    ���Կ������qi����qiK=rLi+1��Ҳ����qi��KģLi����
    ��������ֻ��е�x=c^qi���ɡ�
    ��ÿһ���ֻ���һ�Σ��������x����������
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

llt A[100010];
bool Flag[100010];
llt Tmp[100010];
llt Tmp2[100010];
llt Result[100010];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int n = getUnsigned();
    llt k = getUnsigned();
    for(int i=1;i<=n;++i)A[i]=getUnsigned();
    //��ѭ����
    for(int i=1;i<=n;++i){
        if(Flag[i]) continue;

        llt cnt = 0;
        int t = i;
        do{
            Flag[t] = true;
            Tmp[t] = A[t]; //�û�:At���t
            t = A[t];
            ++cnt;
        }while(!Flag[t]);
        //�����һ���ֻ����ҳ���Ϊcnt������
        if(cnt==1) continue;
        llt qi = inv(k%cnt, cnt);
        //�ѱ任д����������ʽ�Է���ѭ����λ
        t = i;
        for(int j=0;j<cnt;++j){
            Tmp2[j] = Tmp[t];
            t = A[t];
        }
        //Tmp�м��û�ci��������ci^qi��Ҳ������һ��ѭ����λ
        if(--qi) rotate(Tmp2,Tmp2+qi,Tmp2+cnt);
        //������
        t = i;
        for(int j=0;j<cnt;++j){
            Tmp[t] = Tmp2[j];
            t = A[t];
        }
    }
    //���
    for(int i=1;i<=n;++i)printf("%lld ",Tmp[i]);
    printf("\n");
    return 0;
}
