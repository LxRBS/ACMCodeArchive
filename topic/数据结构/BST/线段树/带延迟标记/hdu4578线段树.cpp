/*
    ����A[1...N]��һ����4�ֲ���
    1 x y c��A[x...y]����c
    2 x y c��A[x...y]����c
    3 x y c��A[x...y]ȫ�����c
    4 x y p����SIGMA(Ai^p) x<=i<=y,1<=p<=3

    ��3���߶������ֱ𱣴�͡�ƽ���͡�������
    �ӳٱ�ǲ��ܼ򵥵ļ�¼+c���ߡ�c�����ʹ������������¼�ӳٲ�����
    k/b/x
    �����+c�Ļ����ӳٲ����ͱ�Ϊkx+(b+c)������xΪ0����Ϊ��ֵ������c������Ϊ0
    ����ǡ�c�Ļ����ӳٲ����ͱ�Ϊkcx+bc������xΪ0
    ����Ǹ�ֵΪc�Ļ����ӳٲ����ͱ�Ϊ1��x+0

    һ��Ҫע����ȷ�����ú��´��ӳٱ�ǣ�����
    Ϊ���գ����ʹ��longlong����Ȼintʵ����Ҳ�ǿ��Ե�
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int llt;

llt const SIZE = 100010;
llt const MOD = 10007;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

//0��ʾ����ͣ�1��ʾƽ���ͣ�2��ʾ������
llt ST[3][SIZE<<2];
//�ֱ���k/b/x
llt Lazy[3][SIZE<<2];

inline void _pushUp(int t){
    int ls = lson(t), rs = rson(t);
    ST[0][t] = ( ST[0][ls] + ST[0][rs] ) % MOD;
    ST[1][t] = ( ST[1][ls] + ST[1][rs] ) % MOD;
    ST[2][t] = ( ST[2][ls] + ST[2][rs] ) % MOD;
}

void _f(int t,int len,llt k,llt b){
    llt k2 = k * k % MOD;
    llt k3 = k2 * k % MOD;
    llt b2 = b * b % MOD;
    llt b3 = b2 * b % MOD;

    //������
    ST[2][t] = k3 * ST[2][t] % MOD + 3 * k2 % MOD * b % MOD * ST[1][t] % MOD + 3 * k % MOD * b2 % MOD * ST[0][t] % MOD + len * b3 % MOD;
    //ƽ����
    ST[1][t] = k2 * ST[1][t] % MOD + 2 * k % MOD * b % MOD * ST[0][t] % MOD + len * b2 % MOD;
    //�����
    ST[0][t] = k * ST[0][t] % MOD + len * b % MOD;

    ST[0][t] %= MOD;
    ST[1][t] %= MOD;
    ST[2][t] %= MOD;
}

inline void _pushDown(int t,int s,int e){
    if ( 1 == Lazy[0][t] && 0 == Lazy[1][t] && 0 == Lazy[2][t] ) return;

    int mid = ( s + e ) >> 1;
    int llen = ( mid - s + 1 ) % MOD;
    int rlen = ( e - mid ) % MOD;
    int ls = lson(t), rs = rson(t);

    llt &k = Lazy[0][t], &b = Lazy[1][t], &x = Lazy[2][t];

    if ( x ){//���ڸ�ֵ����
        llt tmp = ( k * x % MOD + b ) % MOD;
        //�����
        ST[0][ls] = llen * tmp % MOD;
        ST[0][rs] = rlen * tmp % MOD;
        //ƽ����
        ST[1][ls] = ST[0][ls] * tmp % MOD;
        ST[1][rs] = ST[0][rs] * tmp % MOD;
        //������
        ST[2][ls] = ST[1][ls] * tmp % MOD;
        ST[2][rs] = ST[1][rs] * tmp % MOD;

        Lazy[0][ls] = Lazy[0][rs] = k;
        Lazy[1][ls] = Lazy[1][rs] = b;
        Lazy[2][ls] = Lazy[2][rs] = x;
    }else{//�����ڸ�ֵ����
        _f(lson(t),llen,k,b);
        _f(rson(t),rlen,k,b);

        Lazy[0][ls] = Lazy[0][ls] * k % MOD;
        Lazy[1][ls] = ( Lazy[1][ls] * k % MOD + b ) % MOD;
        Lazy[0][rs] = Lazy[0][rs] * k % MOD;
        Lazy[1][rs] = ( Lazy[1][rs] * k % MOD + b ) % MOD;
    }

    k = 1;
    b = 0;
    x = 0;
}

//��ѯԴ����������[a,b]��p�η��ͣ�pȡֵΪ[0,2]����ʾ1~3�η�
llt query(int t,int s,int e,int a,int b,int p){
    if ( a <= s && e <= b ){
        return ST[p][t];
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    llt ans = 0;
    if ( a <= mid ) ans = ( ans + query(lson(t),s,mid,a,b,p) ) % MOD;
    if ( mid < b ) ans = ( ans + query(rson(t),mid+1,e,a,b,p) ) % MOD;
    return ans;
}

//��Դ��������[a,b]ʵʩop������opΪ1~3
void modify(int t,int s,int e,int a,int b,int op,int para){
    if ( a <= s && e <= b ){
        int len = ( e - s + 1 ) % MOD;

        if ( 1 == op ){//+para
            _f(t,len,1,para);
            Lazy[1][t] = ( Lazy[1][t] + para ) % MOD;
        }else if ( 2 == op ){//*para
            _f(t,len,para,0);
            Lazy[0][t] = Lazy[0][t] * para % MOD;
            Lazy[1][t] = Lazy[1][t] * para % MOD;
        }else{
            ST[0][t] = len * para % MOD;
            ST[1][t] = ST[0][t] * para % MOD;
            ST[2][t] = ST[1][t] * para % MOD;
            Lazy[0][t] = 1;
            Lazy[1][t] = 0;
            Lazy[2][t] = para;
        }

        return;
    }

    _pushDown(t,s,e);
    int mid = ( s + e ) >> 1;
    if ( a <= mid ) modify(lson(t),s,mid,a,b,op,para);
    if ( mid < b ) modify(rson(t),mid+1,e,a,b,op,para);
    _pushUp(t);
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);

    int n,m,x,y,para,cmd;
    while( scanf("%d%d",&n,&m) ){
        if ( 0 == n && 0 == m ) break;

        fill(ST[0],ST[0]+n*4+1,(llt)0);
        fill(ST[1],ST[1]+n*4+1,(llt)0);
        fill(ST[2],ST[2]+n*4+1,(llt)0);

        fill(Lazy[0],Lazy[0]+n*4+1,(llt)1);
        fill(Lazy[1],Lazy[1]+n*4+1,(llt)0);
        fill(Lazy[2],Lazy[2]+n*4+1,(llt)0);

        while(m--){
            scanf("%d%d%d%d",&cmd,&x,&y,&para);
            if ( 4 == cmd ){
                printf("%I64d\n",query(1,1,n,x,y,para-1));
            }else{
                modify(1,1,n,x,y,cmd,para%MOD);
            }
        }
    }
    return 0;
}
