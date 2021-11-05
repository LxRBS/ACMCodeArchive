/*
    N����ƿ�ų�һ��
    1 A F����ʾ��A��ʼ��ÿ����ƿ�ӷ�һ������ֱ�����꣬����ƿ�ӵ��˾�ͷ
    2 A B����ʾ��[A,B]�����ڵ�ƿ�����

    ��ÿһ��1����������Ż��������յ�
    ��ÿһ��2��������������Ļ�������

    ʹ���߶�������¼�����
    ��2�������൱������ͣ��ٸ���
    ��1����������Ҫ�ҵ����������first
    Ȼ��ȷ���յ�last
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 50011;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int ST[SIZE<<2];//�߶����������
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

//��[a,b]���䶼����ΪnewValue
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

//��a��ʼ����f�仨
void proc(int n,int a,int f){
    //�ҵ����������first
    //���庯��f(x) = [a,x]�ĳ��� - S(a,x)
    //f(x)ʵ���Ͼ�������[a,x]��0����������f(x)��һ�ε���1��λ�þ������
    //��������f(x)>0������λ��
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

    //���ȼ����õĻ�������
    int tmp;
    if ( (tmp=query(1,1,n,first,n)) + f > n - first + 1 ){
        f = n - first + 1 - tmp;
    }

    //�������õ��յ�
    //���庯��f(x) = f + S(first,x) - [first,x]�ĳ���
    //f(x)�������䰲�ź�ʣ�µĻ����������ҵ�f(x)��һ��Ϊ0��λ�ü��ɣ�Ҳ�������һ��Ϊ1��λ�ü�1
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

            if ( 2 == k ){//���
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
