/**
  ��N��������һ��������ڣ�
  ��һ�����߽���������ֳ����룬ʹ�ã�
  1 ��ߵ�С�������֮�ʹ��ڵ����ұߣ��Ҳ�𾡿���С
  2 ��ߵ���������ܴ�
  N��1�����ڣ�������100������
  С���ο��Ա��з�Ϊ����
  �������ΪS����ߵ������������λ�ñ仯��Ϊf(x)
  ������֮��Ϊ2f(x)-S������һ��������
  ����Ҫ������2f(x)-S>=0����������������ö���
  ���Ӷ�Ӧ����1���log(100��)�������20��
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

//����x������x��ߵ�������Ƿ�����ұ�
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

//��������ʹ����ߴ��ڵ����ұߵ�x
int binary_search(){
    int left = 0, right = R, mid;
    do{
        mid = ( left + right ) >> 1;
        if( check(mid) ) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    return left;
}

//x�Ƿ���������Ϊarea
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
//��֪x������ʹ����ߴ��ڵ����ұߣ�����Ҫ����ҵ�
int binary_search(int x){
    //���ȼ���x�ֵ���ߵ�������Ƕ���
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

        //��������x����Ӧ������ҵ�x
        int x = binary_search();
        //����һ�ζ�������
        printf("%d\n",binary_search(x));
    }
    return 0;
}
