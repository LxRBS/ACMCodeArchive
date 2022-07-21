/**
 * ����Ϊ8���ַ�������ʾһ�����̣��м���ͨ���
 * �ʷ��̳������һ���ж�����
 * ֧�ּӼ��˳��͸��ţ�������������������ǰ��0
 * ���Ƚ�С��Ȼ���������ѱ߼��Ƚ��鷳���ر��ǳ������Ѽ�
 * ����ͳһ���������ж�
 * ����ö�ٵ��ں����ڵ�λ�ã�Ȼ��ö��������п��ܵķŷ�
 * ���кϷ�ֵ���뼯��
 * ��ö���ұ����п��ܵķŷ��������еĺϷ�ֵ��û���ڼ����г��ֹ� 
 * �������6��*�ţ�14��6�η����ٳ�2�����1600����
 */
#include <bits/stdc++.h>
using namespace std;

int const N = 8;
int EQIdx = -1;
int Ans;
char A[12];

string const CH = "0123456789+-*/";

bool eval(int s, int e, int &ans){
	using vi = vector<int>;
	vi st;

	auto getValue = [&](int &k)->pair<int, int>{
		int sgn = 1;
		if('-' == A[k]) ++k, sgn = -1;
		if(!(isdigit(A[k]) && k <= e)) return {0, 0};
		int v = 0;
		while(k <= e && isdigit(A[k])){
			v = v * 10 + (A[k] - '0');
			++k;
		}
		return {v * sgn, 1};
	};

	int k = s;
	auto p = getValue(k);
	if(!p.second) return false;
	st.push_back(p.first);

	while(k <= e){	
		int tmp = 1;
        if(A[k] == '+') ;
		else if(A[k] == '-') tmp = -1;
		else if(A[k] == '*') tmp = 2;
		else if(A[k] == '/') tmp = 3;
		else return false;
		++k;

        p = getValue(k);
		if(!p.second) return false;
		if(tmp <= 1){
			st.push_back(p.first * tmp);
		}else if(2 == tmp){
			st.back() *= p.first;
		}else{
			if(0 == p.first || st.back() % p.first) return false;
			st.back() /= p.first;
		}
	}
	ans = accumulate(st.begin(), st.end(), 0);
	return true;
}

unordered_multiset<int> Set;

void f(int const s, int const e){
	function<void(int)> dfs = [&](int pos){
		if(e + 1 == pos){
	        int ans;
			if(eval(s, e, ans)) Set.insert(ans);
			return;
		}

		if(A[pos] != '?'){
			dfs(pos + 1);
			return;
		}

		for(char ch: CH){
			A[pos] = ch;
			dfs(pos + 1);
			A[pos] = '?';
		}

		return;
	};

	dfs(s);
}

void g(int const s, int const e){
	function<void(int)> gdfs = [&](int pos){
		if(e + 1 == pos){
			int ans;
			if(eval(s, e, ans)){
				Ans += Set.count(ans);
			}
			return;
		}

		if(A[pos] != '?'){
			gdfs(pos + 1);
			return;
		}

		for(char ch: CH){
			A[pos] = ch;
			gdfs(pos + 1);
			A[pos] = '?';
		}

		return;		
	};

	gdfs(s);
}

void f(){
    Set.clear();
	f(0, EQIdx-1);
	g(EQIdx+1, 7);
}

int proc(){
	Ans = 0;
	assert(N == strlen(A));
    for(int i=0;i<N;++i){
        if('=' == A[i]){
			EQIdx = i;
			break;
		}
	}
	if(EQIdx != -1){
		f();
		return Ans;
	}
	for(EQIdx=1;EQIdx<7;++EQIdx){
		if(A[EQIdx] == '?')	f();
	}
	return Ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    cin >> A;
	cout << proc() << endl;
    return 0;
}