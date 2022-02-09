/**
 * ����M�����飬ÿ������Ni������Ҫ�����е����ֳ����ѣ�����L��R�����㣺
 * 1 L == R
 * 2 ÿһ�����飬һ�����L��һ�����R
 * ���еĻ��������������������NO
 * ������ȻҪNi��ż������ÿ����ֵ������Ҳ������ż���������ȻNO
 * ����������ʵ���ǣ���ͬ��ֵ����һ�룬��ͬ�������һ��
 * ����ĳ����ֵv���������L��������Ȼ��ĳ����ͬ��vҪ����R�������Ʋ�ͷ������ڵĺ�һ������
 * ����ͬһ�����飬��������Ȼ���Էֿ�
 * ���������Ӧ�ıߣ���һ������Ⱦɫ���ɡ�
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
int const SIZE = 21;
#else
int const SIZE = 200055;
#endif

typedef vector<int> vi;
typedef unordered_map<int, int> mii;

int M;
int Cnt[SIZE];

mii Pre;
int Total;

vi G[SIZE];
char Ans[SIZE] = {0};

void dfs(int u, char ch){
    Ans[u] = ch;
	for(auto v: G[u]){
		if(Ans[v]) continue;
		dfs(v, ch^'L'^'R');
	}
}

void proc(){
	for(int i=1;i<=Total;i+=2){
		G[i].push_back(i+1);
		G[i+1].push_back(i);
	}

    for(int i=1;i<=Total;++i){
        if(Ans[i]) continue;
		dfs(i, 'L');
	}

    puts("YES");
    char const * p = Ans;
	for(int i=1;i<=M;++i){
		for(int j=1;j<=Cnt[i];++j){
            putchar(*++p);
		}
		putchar('\n');
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif   
    M = getInt();
	int k = 0;
    bool flag = false;

	for(int n,a,i=1;i<=M;++i){
        if(1&(n = getInt())) flag = true;
		Cnt[i] = n;

		for(int j=1;j<=n;++j){
			++k;
			auto it = Pre.find(a = getInt());
            if(it == Pre.end()){
				it = Pre.insert(it, {a, 0});
			}
			if(it->second){
                G[k].push_back(it->second);
				G[it->second].push_back(k);
				it->second = 0;
			}else{
                it->second = k;
			}
		}
	}
	if(flag){puts("NO"); return 0;}
	for(auto p: Pre)if(p.second){puts("NO"); return 0;}
	Total = k;
    proc();
    return 0;
}
