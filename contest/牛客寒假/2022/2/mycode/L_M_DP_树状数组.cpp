/**
 * ����һ������A���Լ�һ����ʾ��������������B���ʺϷ�������һ���ж��ٸ�
 * ����Ϊ��
 * 1 �����ǲ��ϸ������
 * 2 ��ÿ��Ai��ҪôAi�ǵ�һ����ѡ�еģ�ҪôAi֮ǰ��Bi��Ԫ����������һ��
 * ��Ui����i��β�ķ�����������
 * Ui = SIGMA{Uj, j=i-b,...,i-1, ��Aj<=Ai}
 * ���� Di = I[i-1] + Ui, ��D[N]�Ǵ�
 * �����Ȼ��ʱ
 * ע�⵽Ui���������ͣ����Կ���ʹ����״����
 * ��A��ֵ���򣬶����µ�˳�򣬶��ڵ�ǰҪ�����Ui���������ֵ����û�г���
 * ��˿��Լ�����UiΪ[Ai.idx-b, Ai.idx-1]�������
 * �������Ժ��ٽ�Ui���뼴��
 * �������[1...N]�������Ϊ��
*/
#include<bits/stdc++.h>
namespace GenHelper
{
    int z1,z2,z3,z4,z5,u,res;
    int get()
    {
        z5=((z1<<6)^z1)>>13;
        z1=((int)(z1&4294967)<<18)^z5;
        z5=((z2<<2)^z2)>>27;
        z2=((z2&4294968)<<2)^z5;
        z5=((z3<<13)^z3)>>21;
        z3=((z3&4294967)<<7)^z5;
        z5=((z4<<3)^z4)>>12;
        z4=((z4&4294967)<<13)^z5;
        return (z1^z2^z3^z4);
    }
    int read(int m) {
        u=get();
        u>>=1;
        if(m==0)res=u;
        else res=(u/2345+1000054321)%m;
        return res;
    }
     void srand(int x)
    {
        z1=x;
        z2=(~x)^(0x23333333);
        z3=x^(0x12345798);
        z4=(~x)+51;
      	u = 0;
    }
}

using namespace GenHelper;
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 2000010;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

int N;
llt C[SIZE];

/// ��״����
inline int lowbit(int x){return x & -x;}
void modify(int idx, llt delta){
	for(;idx<=N;idx+=lowbit(idx)){
		(C[idx] += delta) %= MOD;
	}
}
llt query(int idx){
	llt ans = 0;
    for(;idx;idx-=lowbit(idx)){
        (ans += C[idx]) %= MOD;
	}
	return ans;
}
inline llt query(int s, int e){
    return (query(e) - query(s-1) + MOD) % MOD;
}

struct _t{
	int idx;
	int val;
	int b;
}A[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int seed;
    scanf("%d%d", &N, &seed);
	srand(seed);
	for(int i=1;i<=N;i++){
		A[A[i].idx = i].val = read(0);
		A[i].b = read(i);
	}

	sort(A+1, A+N+1, [](const _t&a, const _t&b)->bool{
		if(a.val != b.val) return a.val < b.val;
		if(a.idx != b.idx) return a.idx < b.idx;
		return a.b < b.b;
	});
    
    for(int i=1;i<=N;++i){
		llt t = 1LL + query(A[i].idx-A[i].b, A[i].idx-1);
		modify(A[i].idx, t);
	}
	printf("%lld\n", query(N));
    return 0;
}