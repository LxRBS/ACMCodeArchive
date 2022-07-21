/**
 * 2000���㣬Ҫ��ѡ3���㣬�������������پ������λ��������
 * �ʷ��������������ж��٣�10��������O(10*N^3)��ȻҪ��ʱ
 * ��Bi��¼���е�i����С�ڵ���w�Ľڵ�
 * ����������о��룬��ÿһ���������ľ���w������������ab�ڵ��γɵ�
 * ���д�����Ba�ֲ���Bb�еĵ㣬������w��Ϊ��λ��
 * ��Ȼ��Bb���ֲ���Ba�еĵ�Ҳ�Ƿ���������
 * ��bitset����¼B����Ϣ��ʹ��������㼴�ɵõ�������������
 * Bi��Ϣ��for w��ѭ����ʱ��ά������
 * O(T*(N^2log(N^2)+N^3/32))
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

//����ɸ��
int const SZ = 200001;
bool isComp[SZ] = {true, true}; // !isComp[i]Ϊ��˵��i������
int P[SZ]; //P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0; //PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(long long int i=2;i<SZ;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SZ;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

#ifndef ONLINE_JUDGE
int const SIZE = 2013;
#else
int const SIZE = 2E3+100;
#endif

using pii = pair<int, int>;
using llt = long long;
using vpii = vector<pii>;
using bt = bitset<SIZE>;

struct _t{
    int a, b, w;
};

int N, M;
pii A[SIZE];
vector<_t> Vec;
bt B[SIZE];

inline int f(int idx, int jdx){
    int x = A[idx].first - A[jdx].first;
    if(x < 0) x = -x;
    int y = A[idx].second - A[jdx].second;
    if(y < 0) y = -y;
    return x + y;
}


llt proc(){
    Vec.clear();
    Vec.reserve(N*(N-1)/2);

    for(int i=0;i<N;++i){
        B[i].reset();
        for(int j=i+1;j<N;++j){
            Vec.push_back({i, j, f(i, j)});
        }
    }

    sort(Vec.begin(), Vec.end(), [](const _t&u, const _t&v)->bool{
        if(u.w != v.w) return u.w < v.w;
        if(u.a != v.a) return u.a < v.a;
        return u.b < v.b;
    });

    llt ans = 0;
    for(const auto & p: Vec){
        if(!isComp[p.w]){ // ˵����������Ҫ��
            ans += (B[p.a] ^ B[p.b]).count();
        }
        B[p.a].set(p.b);
        B[p.b].set(p.a);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    sieve();

    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); M = getInt();
        for(int i=0;i<N;++i){
            A[i].first = getInt();
            A[i].second = getInt();
        }
        cout << proc() << endl;
    }
    return 0;
}