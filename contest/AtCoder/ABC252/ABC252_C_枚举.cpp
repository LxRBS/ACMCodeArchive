/**
 * ����N���ַ�����ÿ���ַ���ǡ�ð�����0-9��10������
 * ÿһ����ѡ��һ���ַ����������t��ѡ���i���ַ��������ѡ������S[i][t%10]
 * ������Ҫѡ��N����ͬ�����֣�������Ҫ����
 * �ĳ��ж������⼴�ɡ�����ĳ����ֵv����i�����ܹ�ѡ����ʱ�̾���pos+10k��
 * ���д���ͬһ��v�����ظ�ʱ�̣���̰�ļ��� 
 */
#include <bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 105;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;

int N;
string S[SIZE];

int proc(int value, int idx){
	const string & s = S[idx];
	int k = 0;
	while(s[k] - '0' != value) ++k;
	return k;
}

int proc(int value){
	int flag[1010] = {0};
	int ans = 0;
	for(int i=0;i<N;++i){
		int tmp = proc(value, i);
		while(flag[tmp]) tmp += 10;
		flag[tmp] = 1;
		ans = max(ans, tmp);
	}
	return ans;
}

int proc(){
	int ans = 1E9;
	for(int i=0;i<10;++i){
		ans = min(proc(i), ans);
	}
	return  ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while(cin>>N){
		for(int i=0;i<N;++i) cin>>S[i];
		cout<<proc()<<endl;		
	}
    return 0;
}
