/**
    N�������˴Ӹ��Ե���ʼλ�������ٶ�Ϊ0���ȼ���ֱ���˶�
    ����ȫ�����У��������ȵ�Robotһ���ж��ٸ�
    ������������Robot�����λ�úͼ��ٶȶ�������ȻС�����迼��
    ����i��j����robot������i��ʼ���ں��棬�򳬹���ʱ��(��ƽ��)��Ҫ����2(pj-pi)/(ai-aj)������tij
    ��������3��robot����Ϊi��j��k��λ��������pi<pj<pk�����ٶ�Ϊai>aj>ak
    ���tij<=tjk����j��û���õ�
    ���������Ȼ����ջ�е�Robot����ջ����3�����ڵ���������i��j��k��
    ���������һģһ���ģ���kһ�����ȹ�����jһ��������k������i����j֮ǰ������jҲһ�����ȹ�
    �Դ����ƣ�ջ���robotȫ�������ȹ�
    ���ȥ��
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

int const SIZE = 50000+10;

struct _t{
    llt p;//��ʼλ��
    llt a;//���ٶ�
}A[SIZE],Stack[SIZE];

bool operator < (const _t&lhs,const _t&rhs){
    return lhs.p < rhs.p || (lhs.p==rhs.p&&lhs.a<rhs.a);
}

bool operator == (const _t&lhs,const _t&rhs){
    return lhs.p==rhs.p&&lhs.a==rhs.a;
}

//�Ƚ�3��robot��ijk�����Ƿ�tij<=tjk
bool f(const _t&i, const _t&j, const _t&k){
    //����tij
    llt pij = j.p - i.p;
    llt aij = i.a - j.a;
    //����tjk
    llt pjk = k.p - j.p;
    llt ajk = j.a - k.a;
    return pij * ajk <= aij * pjk;
}

set<_t> Set;
int main(){
    //freopen("1.txt","r",stdin);
    
    int nofkase = getUnsigned();
    while(nofkase--){
        Set.clear();

        int n = getUnsigned();
        for(int i=0;i<n;++i)A[i].p=getUnsigned(),A[i].a=getUnsigned();
        sort(A,A+n);

        int top = 0;
        Stack[top++] = A[0];
        for(int i=1;i<n;++i){
            //��¼����ȵĻ�����
            if(A[i]==A[i-1]) Set.insert(A[i]);
            //���ջ�ڵļ��ٶ�ҲС��ֱ�ӳ�ջ�����ÿ���
            while(top>0&&Stack[top-1].a<=A[i].a) --top;
            //�м�Ŀ϶�û�ã���ջ
            while(top>1&&f(Stack[top-2],Stack[top-1],A[i])) --top;
            //��ջ
            Stack[top++] = A[i];
        }

        //����
        int ans = 0;
        for(int i=0;i<top;++i)if(Set.end()==Set.find(Stack[i]))++ans;
        printf("%d\n",ans);
    }
    return 0;
}
