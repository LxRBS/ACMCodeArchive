/**
 * �齫�ƣ��Ѿ��õ�13�����ƣ��ұ�֤û��һ���ƻᳬ��3��
 * �����Ų������γ��߶Ե���������
 * ��DijΪ������i�ŵ��ƻ�ʣj���ƿ��������γ��߶Ե�����
 * Dij = (D[i][j-1]+1) * (j-3i) / j + (D[i-2][j-1]+1) * 3i / j
 * Ҳ������һ���ɶԺͲ��ɶԵĸ���
 * ע��߽�����
 * D[i][3i]�϶�ֻ���ߺ�������, D[1][j]��ֻ����ǰ������
 * D0j��ȻΪ0
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
int const SIZE = 106;
#else
int const SIZE = 1E3+100;
#endif

using llt = long long;
llt const MOD = 1E9+7;

inline void addAss(llt&a, llt b){(a+=b)%=MOD;}
inline llt mul(llt a, llt b){return a*b%MOD;}
inline llt mul(llt a, llt b, llt c){return mul(a, mul(b, c));}

llt Inv[130];
llt D[14][130];

llt dfs(int a, int b){
    if(-1 != D[a][b]) return D[a][b];
    if(0 == a) return D[a][b] = 0;

    llt ans = 1;
    if(a >= 2){ // Ҫ�ӱ߽��ж�
        addAss(ans, mul(dfs(a-2, b-1), a+a+a, Inv[b]));        
    }
    if(b >= 3*a){ // Ҫ�ӱ߽��жϣ������wa
        addAss(ans, mul(dfs(a, b-1), b-a-a-a, Inv[b]));
    }    
    return D[a][b] = ans;
}

string Input;
map<string, int> Map;

llt proc(){
    Map.clear();
    int t = 13;
    for(int i=0,n=Input.length();i<n;i+=2){
        if(2 == ++Map[Input.substr(i, 2)]) t -= 2;
    }
    llt ans = dfs(t, 123);
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    memset(D, -1, sizeof(D));
    Inv[1] = 1;
    for(int i=2;i<=123;++i){
        Inv[i] = mul(MOD/i, Inv[MOD%i]);
        Inv[i] = MOD - Inv[i];
    } 

    int nofkase; cin >> nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        cin >> Input;
        cout << "Case #" << kase << ": " << proc() << endl;
    }
    return 0;
}