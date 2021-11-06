#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__);fflush(stderr);
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const int N = 55;
vector<string> ANS;
int a[N];
int n;

void addToAns(string s) {
	ANS.push_back(s);
	for (int i = 0; i < n; i++)
		a[i] ^= (int)s[i];
}

void addBrackets(vector<string>&res, vector<int>& b, string s) {
	res.push_back(s);
	for (int i = 0; i < n; i++) {
		if (s[i] == '[' || s[i] == ']') b[i] ^= 1;
	}
}

string myReverse(string s) {
	reverse(all(s));
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == '(') s[i] = ')';
		else if (s[i] == ')') s[i] = '(';
		else if (s[i] == '[') s[i] = ']';
		else if (s[i] == ']') s[i] = '[';
		else if (s[i] == '{') s[i] = '}';
		else if (s[i] == '}') s[i] = '{';
	}
	return s;
}

vector<string> solveBig(vector<int> b) {
	vector<string> res;
	if (b[1] == 1) {
		string s = "[[0]]=0*1";
		while((int)s.length() < n) s.push_back('1');
		addBrackets(res, b, s);
	}
	if (b[0] == 1) {
		string s = "[0]=0*1";
		while((int)s.length() < n) s.push_back('1');
		addBrackets(res, b, s);
	}
	if (b[n - 2] == 1) {
		string s = "[[0]]=0*1";
		while((int)s.length() < n) s.push_back('1');
		s = myReverse(s);
		addBrackets(res, b, s);
	}
	if (b[n - 1] == 1) {
		string s = "[0]=0*1";
		while((int)s.length() < n) s.push_back('1');
		s = myReverse(s);
		addBrackets(res, b, s);
	}
	assert(b[0] == 0 && b[1] == 0 && b[n - 2] == 0 && b[n - 1] == 0);
	if (b[n - 4] == 1) {
		string s = "0=[[0]]*1";
		while((int)s.length() < n) s.push_back('1');
		s = myReverse(s);
		addBrackets(res, b, s);
	}
	if (b[n - 3] == 1) {
		string s = "0=[0]*1";
		while((int)s.length() < n) s.push_back('1');
		s = myReverse(s);
		addBrackets(res, b, s);
	}
	for (int i = n - 5; i >= 4; i--) {
		if (b[i] == 0) continue;
		string s = "";
		for (int j = 0; j < i - 3; j++)
			s.push_back('1');
		s += "*[0]=0*1";
		while((int)s.length() < n) s.push_back('1');
		addBrackets(res, b, s);
	}
	for (int i = 0; i < n; i++) {
		assert(i == 2 || i == 3 || b[i] == 0);
	}
	assert(b[2] == b[3]);
	if (b[2] == 0) return res;
	string s = "0*[11]=0*1";
	while((int)s.length() < n) s.push_back('1');
	addBrackets(res, b, s);
	s = "11*[0]=0*1";
	while((int)s.length() < n) s.push_back('1');
	addBrackets(res, b, s);
	return res;
}

void solve(string s) {
	n = s.length();
	int cntBig = 0, cntSmall = 0;
	for (int i = 0; i < n; i++) {
		a[i] = (int)s[i];
		if ('A' <= s[i] && s[i] <= 'Z')
			cntBig++;
		if ('a' <= s[i] && s[i] <= 'z') {
			cntSmall++;
		}
	}
	if ((cntBig + cntSmall) % 2 == 1) {
		cout << "NO\n";
		return;
	}
	ANS.clear();

	// fix 32
	vector<int> b(n, 0);
	int ssum = 0;
	for (int i = 0; i < n; i++) {
		if ('A' <= s[i] && s[i] <= 'Z') {
			ssum++;
			b[i] = 1;
		}
	}
	if (ssum % 2 == 1 && n % 2 == 0) {
		cout << "NO\n";
		return;
	}
	if (ssum % 2 == 1) {
		for (int i = 0; i < n; i++)
			b[i] ^= 1;
	}
	vector<string> res = solveBig(b);
	for (string s : res)
		addToAns(s);

	// remove 64
	b = vector<int>(n, 0);
	for (int i = 0; i < n; i++) {
		if (a[i] & 64)
			b[i] = 1;
	}
	res = solveBig(b);
	for (string s : res) {
		string p = s;
		for (int i = 0; i < n; i++) {
			if (p[i] == '[')
				p[i] = '{';
			if (p[i] == ']')
				p[i] = '}';
		}
		addToAns(p);
	}

	s = "0=0*1";
	while((int)s.length() < n) s.push_back('1');
	if (a[0] & 32) {
		addToAns(s);
	}

	for (int i = 0; i < n; i++)
		assert(a[i] < 32);
//	return;

	string p = myReverse(s);
	string S = s, P = p;

	if (a[0] & 16) {
		p[0] = '(';
		p[n - 5] = ')';
		addToAns(p);
		addToAns(P);
		p = P;
	}
	if (a[n - 1] & 16) {
		s[n - 1] = ')';
		s[4] = '(';
		addToAns(s);
		addToAns(S);
		s = S;
	}
	for (int i = 1; i < n - 1; i++) {
		if ((a[i] & 16) == 0) continue;
		if (i < n / 2) {
			p[i] = '*';
			addToAns(p);
			addToAns(P);
			p = P;
		} else {
			s[i] = '*';
			addToAns(s);
			addToAns(S);
			s = S;
		}
	}

	for (int i = 0; i < n; i++)
		assert(a[i] < 16);

	for (int i = 0; i < n; i++) {
		if ((a[i] & 8) == 0) continue;
		if (i < n / 2) {
			p[i] = '9';
			addToAns(p);
			addToAns(P);
			p = P;
		} else {
			s[i] = '9';
			addToAns(s);
			addToAns(S);
			s = S;
		}
	}

	for (int i = 0; i < n; i++)
		assert(a[i] < 8);

	for (int i = 0; i < n; i++) {
		if (a[i] == 0) continue;
		if (i < n / 2) {
			if (a[i] == 1) {
				p[i] = '2';
				addToAns(p);
				p[i] = '3';
				addToAns(p);
			} else {
				p[i] = '1' ^ a[i];
				addToAns(p);
				addToAns(P);
			}
			p = P;
		} else {
			if (a[i] == 1) {
				s[i] = '2';
				addToAns(s);
				s[i] = '3';
				addToAns(s);
			} else {
				s[i] = '1' ^ a[i];
				addToAns(s);
				addToAns(S);
			}
			s = S;
		}
	}

	for (int i = 0; i < n; i++)
		assert(a[i] == 0);
	cout << "YES\n";
	cout << (int)ANS.size() << "\n";
	for (string s : ANS)
		cout << s << "\n";
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	cin >> t;
	string s;
	while(t--) {
		cin >> s;
		solve(s);
	}

	return 0;
}
