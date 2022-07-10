/**
 * �������飬�����ѯ�������Ĺ�Լ���Ĵ�����������1
 * ������Ϊ5E4�����Կ���Ī���㷨
 * ����ȷ��ֻ���������Ӽ��ɣ������ֵ��Χ��1E6�����ÿ������ຬ��7��������
 * ��¼��ǰ���������ӵĳ��ֵĴ������Լ���Ӧ�����������ӣ�
 * ��ÿ���䶯��Ԫ��ά�������������ݼ���
 * ��ÿ���䶯��Ԫ����Ҫfor�������������ӣ����Ϊ7��
 * ʱ��ȽϽ�����������ʱ��
 * ���Ȳ���Ҫ��ɸ�����1E6�������ӣ���Ϊ��Ŀ���ֻ��Ҫ5E4���������������ݣ���ǰɸ�������˷�
 * ��ζ���������յ�ʱ��Ҫmemset����Ϊ���������ӽ�1E6��memsetҲ���������
 * ֱ����Ī���㷨�еĲ�����գ�ָ������ƶ�5E4�Σ�ÿ�����7��������������ֻ��3.5E5��
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
int const BLOCK_SIZE = 1;
#else
int const SIZE = 5E4+7;
int const BLOCK_SIZE = 230;
#endif

using llt = long long int;
struct _t{
    int s, e;
    int idx;
    bool operator < (const _t & b) const {
        int ln = this->s / BLOCK_SIZE;
        int rn = b.s / BLOCK_SIZE;
        if(ln != rn) return ln < rn;
        return this->e < b.e;
    }
}Problem[SIZE];

bool isComp[(int)1E6+1] = {false};
int P[1003];
int PCnt = 0;
void sieve(){
    int s = 1003;
    for(llt i=2;i<s;++i){
        if ( !isComp[i] ) P[PCnt++] = i;
 
        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}
 
using vi = vector<int>;
vi Fac[(int)1E6+1];
 
void f(int n){
    vi & vec = Fac[n];
    for(int i=0;i<PCnt&&(llt)P[i]*P[i]<=n;++i){
        if(0 == n % P[i]){
            vec.push_back(P[i]);
            while(0 == n % P[i]) n /= P[i];
        }
    }
    if(n != 1) vec.push_back(n);
}
 
int N, Q;
int A[SIZE];
int Ans[SIZE];
int MoAns = 0;

int Cnt2Prime[SIZE];
int Prime2Cnt[(int)1E6+1];

/// ����n���ӵ�����������
inline void insert(int n){
    for(auto i: Fac[n]){
        int & c = Prime2Cnt[i];
        if(c) --Cnt2Prime[c];
        
        MoAns = max(MoAns, ++c);
        ++Cnt2Prime[c];
    }
}

/// ɾ��n���ٵ�����������
inline void remove(int n){
    for(auto i: Fac[n]){
        int & c = Prime2Cnt[i];
        --Cnt2Prime[c];
        if(MoAns == c && 0 == Cnt2Prime[c]) --MoAns;

        --c;
        if(c) ++Cnt2Prime[c];
    }
}

void proc(){ // Ī���㷨
    sort(Problem+1, Problem+Q+1);

    int curLeft = 1, curRight = 0;
    MoAns = 0;

    for(int i=1;i<=Q;++i){
        while(curRight < Problem[i].e) insert(A[++curRight]);
        while(curLeft > Problem[i].s) insert(A[--curLeft]);
        while(curRight > Problem[i].e) remove(A[curRight--]);
        while(curLeft < Problem[i].s) remove(A[curLeft++]);
        Ans[Problem[i].idx] = MoAns;
    }

    /// �൱���������
    while(curLeft <= curRight) remove(A[curRight--]);

    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    sieve();
    int nofkase = getInt();
    while(nofkase--){
        /// ��ʼ��
        // fill(Prime2Cnt, Prime2Cnt+1000001, MoAns=0);
        // memset(Cnt2Prime, 0, sizeof(Cnt2Prime));

        N = getInt(); Q = getInt();
        for(int i=1;i<=N;++i) {
            if(Fac[A[i] = getInt()].empty()){
                f(A[i]);
            }
        }
        for(int i=1;i<=Q;++i) {
            Problem[Problem[i].idx = i].s = getInt();
            Problem[i].e = getInt();
        }
        proc();
        for(int i=1;i<=Q;++i) printf("%d\n", Ans[i]);
    }
    return 0;
}