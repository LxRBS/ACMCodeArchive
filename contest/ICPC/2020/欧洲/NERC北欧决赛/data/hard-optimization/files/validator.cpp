#include"testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define rep(i,n) rep2(i,0,n)
#define rep2(i,m,n) for(int i=m;i<(n);i++)
#define ALL(c) (c).begin(),(c).end()
#define dump(x) cout << #x << " = " << (x) << endl
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n-1); }

template<class T, class U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
	os<<"("<<p.first<<","<<p.second<<")";
	return os;
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os<<"{";
	rep(i, v.size()) {
		if (i) os<<",";
		os<<v[i];
	}
	os<<"}";
	return os;
}

int main(int argc, char** argv) {
	registerValidation(argc, argv);
	int n = inf.readInt(1, 2000, "n");
	inf.readEoln();
	vector<int> L(n), R(n);
	for (int i = 0; i < n; i++) {
	  L[i] = inf.readInt(0, (int) 1e9 - 1, "L_" + to_string(i + 1));
          inf.readSpace();
	  R[i] = inf.readInt(L[i] + 1, (int) 1e9, "R_" + to_string(i + 1));
	  inf.readEoln();
	}
	
	set<int> s;
	for (int i = 0; i < n; i++) {
	  ensuref(s.find(L[i]) == s.end(), "segment endpoint %d duplicated", L[i]);
	  s.insert(L[i]);
	  ensuref(s.find(R[i]) == s.end(), "segment endpoint %d duplicated", R[i]);
	  s.insert(R[i]);
	}
	
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int i, int j) {
	  return L[i] < L[j];
	});

	vector<int> st;
	for (int i : order) {
	  while (!st.empty() && L[i] > R[st.back()]) {
	    st.pop_back();
	  }
	  if (!st.empty()) {
  	    ensuref(R[i] < R[st.back()], "segments %d [%d; %d] and %d [%d; %d] intersect, but none of them contains the other",
  	        st.back() + 1, L[st.back()], R[st.back()], i + 1, L[i], R[i]);
  	  }
  	  st.push_back(i);
	}

	inf.readEof();

	return 0;
}