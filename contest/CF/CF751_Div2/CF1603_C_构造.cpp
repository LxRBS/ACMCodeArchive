/**
 * ����һ������a����ѡ��һ��������k�������²�����
 * ÿһ�δ�a��ѡ��k��Ԫ�أ���x������k��Ԫ�ص���
 * Ȼ���ٴ���k��Ԫ���м�ȥx��
 * �����ѡ��k��ʹ���ܹ��������ɴβ���������������
 * x��Ȼ��k��Ԫ�صĹ���λ��Ȼ�������
 * �����Ҫ�������飬ֻҪÿ��ѡ��1������λ�������㼴��
 * Ҫ�뽫����������Ԫ���ض�λ���㣬����ѡȡ��k�����Ǹ�λΪ1��������Լ��
 * ����k����������λΪ1�������Ĺ�Լ����Լ��
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef int llt;

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

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
int const SIZE = 201000;
#endif

int N;
int A[SIZE];
int Cnt[33];

void proc(){
	int g = 0;
	for(int i=0;i<30;++i)if(Cnt[i]){
        if(0 == g){
            g = Cnt[i];
		}else{
			g = gcd(g, Cnt[i]);
		}
	}

    if(0 == g){
		for(int i=1;i<=N;++i)printf("%d ", i);
		puts("");
		return;
	}

	vector<int> ans;
	for(llt i=1;i*i<=g;++i){
		if(g%i==0){
			ans.push_back(i);
			if(i*i!=g) ans.push_back(g/i);
		}
	}
	sort(ans.begin(), ans.end());
	for(auto i: ans){
		printf("%d ", i);
	}
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		memset(Cnt, 0, sizeof(Cnt));
		N = getInt();
		for(int m, i=1;i<=N;++i){
			if(m = A[i] = getInt()){
				for(int i=0;i<30;++i){
					if(m&(1<<i)){
						++Cnt[i];
					}
				}				
			}
		} 

		proc();
	}
	return 0;
}