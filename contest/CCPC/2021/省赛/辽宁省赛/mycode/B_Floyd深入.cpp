/**
 * ����ͼ����Ϊ��ͨ�ߣ����ڴ�i��j��·���������Ѷ�=·������Ȩ��������Ȩ
 * ����ij��Ե��Ѷ�Ϊij֮������·������С�Ѷȡ�
 * �����е������Ѷȡ�N��500��
 * �Ƚ����Ե�Floyd��������Ҫ��Щ��
 * ���Ȳ��ֱܷ�ά����Ȩ����Ȩ�ʹ𰸣���Ϊ��Ȩ�ͱ�Ȩ���໥ƥ��� 
 * �������Ȱ���Ȩ����Ȼ�������ѭ����С���������
 * �������Ա�֤ÿ�μ������·��������Ȩ�ܹ�����
 * ����ֻ��ά����Ȩ�ʹ𰸡�
 * ���б�Ȩά����������·��������Ȩ����Сֵ��
 * �ټ���������֦���ɣ����Ӽ�֦�ᳬʱ��
 * ����һ���Ż�����Ϊ������ͼ��Dij=Dji��ֱ�Ӹ����Ժ���ܳ��������
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
int const SIZE = 17;
#else
int const SIZE = 505;
#endif

using llt = long long int;
using Real = long double;
using vi = vector<llt>;
using vvi = vector<vi>;
using pii = pair<llt, llt>;
using vpii = vector<pii>;

template<>struct std::hash<pii>{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

using lltarr = llt [SIZE][SIZE];

int N, M;
pii W[SIZE];
lltarr G, A, B, D;

/// DP�ĸ���
void update(llt & a, llt b){
    if(-1 == a) a = b;
    else if(b != -1) a = min(a, b);
}

void proc(){
    /// ��ʼ������ʼ·������Ȩ���Ǳ߱���
    for(int i=1;i<=N;++i) copy(G[i]+1, G[i]+N+1, A[i]+1);
    /// ��ʼ·������Ȩ���бߵĻ���������֮һ���ޱߵĻ�����-1
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            if(-1 == G[i][j]) D[i][j] = -1;
            else D[i][j] = max(W[i].first, W[j].first) * G[i][j];
        }
    }

    sort(W+1, W+N+1);

    for(int i,j,k,_=1;_<=N;++_){
        llt wi, wj, wk;
        /// �൱�ڸ��ݵ�Ȩ��С����ö�ٵ㣬�������Ծ�ȷ��λ·��������Ȩ
        k = W[_].second;
        wk = W[_].first; 
        for(int __=1;__<=N;++__){
            i = W[__].second;
            wi = W[__].first;
            for(int ___=1;___<=N;++___){
                j = W[___].second;
                wj = W[___].first;
                
                /// ��·����ͨ���Թ�
                if(-1 == A[i][k] || -1 == A[k][j]) continue;

                /// i-k-j·��������Ȩ�϶�������������
                llt dianquan = max(max(wi, wj), wk);
                /// i-k-j·��������Ȩ��Ȼ�������нϴ���Ǹ�
                llt bianquan =  max(A[i][k], A[k][j]); 

                /// ���������Ȩ��ԭ������Ȩ��Ҫ�󣬿���ֱ�Ӻ���
                /// ��Ϊ��Ȩ�ǵ����ģ�������Ϊ��Сֵ
                /// ������continue��Ҫ�У�����ᳬʱ
                if(bianquan > A[i][j] && -1 != A[i][j]) continue;       
              
                /// ��·���Ľ�
                llt ans = bianquan * dianquan;
                /// dp
                update(A[i][j], bianquan);
                update(D[i][j], ans);
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    for(int i=1;i<=N;++i) W[W[i].second = i].first = getInt();

    memset(G, -1, sizeof(G));
    for(int a,b,w,i=1;i<=M;++i){
        a = getInt(); b = getInt(); w = getInt();
        G[a][b] = G[b][a] = w;
    }
    for(int i=1;i<=N;++i){
        assert(-1 == G[i][i]);
        G[i][i] = 0;
    }

    proc();
    for(int i=1;i<=N;++i){
        printf("%lld", D[i][1]);
        for(int j=2;j<=N;++j) printf(" %lld", D[i][j]);
        puts("");
    }
    return 0;
}

