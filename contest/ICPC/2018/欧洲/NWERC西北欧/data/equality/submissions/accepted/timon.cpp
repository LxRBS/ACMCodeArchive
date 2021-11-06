#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

struct node {
	// 0 -> list
	// 1 -> sort
	// 2 -> shuffle
	// 3 -> concat
	int type;
	vi tokens;
	node *lc, *rc;
	void accum(vector<pair<int, vi>> &res) {
		if (type == 0)
			res.emplace_back(pair<int, vi>{type, move(tokens)});
		else if (type == 1 || type == 2) {
			res.push_back({type, vi()});
			lc->append(res.back().second);
		} else if (type == 3) {
			lc->accum(res);
			rc->accum(res);
		}
	}
	void append(vi &v) {
		if (type == 0)
			v.insert(v.end(), tokens.begin(), tokens.end());
		else if (type == 3)
			lc->append(v), rc->append(v);
		else
			lc->append(v);
	}
};

const string kconcat = "concat(";
const string kshuffle = "shuffle(";
const string ksorted = "sorted(";

node *parse(const string &s, int &l) {
	node *r = new node();
	if (s[l] == '[') {
		r->type = 0;
		int val = 0;
		for (++l; s[l] != ']'; ++l)
			if (s[l] == ',')
				r->tokens.push_back(val), val = 0;
			else
				val = 10 * val + (s[l]-'0');
		r->tokens.push_back(val), ++l;
		return r;
	}
	if (s[l] == 'c') {
		l += kconcat.length();
		r->type = 3;
		r->lc = parse(s, l), ++l;
		r->rc = parse(s, l), ++l;
		return r;
	}
	if (s[l] == 's' && s[l+1] == 'h') {
		l += kshuffle.length();
		r->type = 2;
		r->lc = parse(s, l), ++l;
		return r;
	}
	if (s[l] == 's' && s[l+1] == 'o') {
		l += ksorted.length();
		r->type = 1;
		r->lc = parse(s, l), ++l;
		return r;
	}
	return nullptr;
}

vector<pair<int, vi>> simplify(vector<pair<int, vi>> inp) {
	// Break up simple lists. Also constant shuffles/sorts.
	vector<pair<int, vi>> res;
	for (int i = 0; i < (int)inp.size(); ++i) {
		bool eq = true;
		for (int j = 1; j < (int)inp[i].second.size(); ++j)
			eq = eq && inp[i].second[j] == inp[i].second[j-1];
		if (inp[i].first == 0 || eq)
			for (int j = 0; j < (int)inp[i].second.size(); ++j)
				res.emplace_back(0, vi(1, inp[i].second[j]));
		else if (inp[i].first == 1) {
			sort(inp[i].second.begin(), inp[i].second.end());
			for (int j = 0; j < (int)inp[i].second.size(); ++j)
				res.emplace_back(0, vi(1, inp[i].second[j]));
		} else res.push_back(inp[i]);
	}
	return res;
}

vector<pair<int, vi>> takeline() {
	string line;
	cin >> line;
	int l = 0;
	node *t = parse(line, l);
	assert((int)line.length() == l);

	vector<pair<int, vi>> res;
	t->accum(res);
	return simplify(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vector<pair<int, vi>> a = takeline(), b = takeline();

	bool ok = a.size() == b.size();
	for (int i = 0; ok && i < (int)a.size(); ++i) {
		ok = ok && a[i].first == b[i].first;
		sort(a[i].second.begin(), a[i].second.end());
		sort(b[i].second.begin(), b[i].second.end());
		ok = ok && a[i].second.size() == b[i].second.size();
		for (int j = 0; ok && j < (int)a[i].second.size(); ++j)
			ok = ok && a[i].second[j] == b[i].second[j];
	}

	if (!ok) cout << "not ";
	cout << "equal" << endl;
	
	return 0;
}
