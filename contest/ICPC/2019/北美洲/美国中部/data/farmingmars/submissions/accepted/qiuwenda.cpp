#include <bits/stdc++.h>
using namespace std;
struct val {
	int guess, cnt;
	val(int guess = 0, int cnt = 0) : guess(guess), cnt(cnt) {}
};
val operator + (const val &a, const val &b) {
	int guess = (a.cnt > b.cnt ? a.guess : b.guess), cnt = 0;
	cnt += (a.guess == guess ? 1 : -1) * a.cnt;
	cnt += (b.guess == guess ? 1 : -1) * b.cnt;
	return val(guess, cnt);
}
struct node {
	val guess;
	map<int, int> total;
	node() {
		guess = val();
	}
	node(int x) {
		guess = val(x, 1);
		total[x] = 1;
	}
};
const int N = 1e4 + 5;
int a[N];
node tree[N * 4];
void build(int x, int l, int r) {
	if (l == r) {
		tree[x] = node(a[l]);
		return;
	}
	int mid = (l + r) / 2;
	build(x + x, l, mid);
	build(x + x + 1, mid + 1, r);
	tree[x].guess = tree[x + x].guess + tree[x + x + 1].guess;
	for (auto p : tree[x + x].total) tree[x].total[p.first] += p.second;
	for (auto p : tree[x + x + 1].total) tree[x].total[p.first] += p.second;
}
void modify(int x, int l, int r, int pos, int new_val) {
	if (r < pos || l > pos) return;
	if (l == r) {
		tree[x] = node(new_val);
		a[pos] = new_val;
		return;
	}
	tree[x].total[a[pos]] --;
	tree[x].total[new_val] ++;
	int mid = (l + r) / 2;
	modify(x + x, l, mid, pos, new_val);
	modify(x + x + 1, mid + 1, r, pos, new_val);
	tree[x].guess = tree[x + x].guess + tree[x + x + 1].guess;
}
val query_guess(int x, int l, int r, int ql, int qr) {
	if (l > qr || r < ql) return val();
	if (l >= ql && r <= qr) return tree[x].guess;
	int mid = (l + r) / 2;
	return query_guess(x + x, l, mid, ql, qr) + query_guess(x + x + 1, mid + 1, r, ql, qr);
}
int query_cnt(int x, int l, int r, int ql, int qr, int target) {
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return tree[x].total[target];
	int mid = (l + r) / 2;
	return query_cnt(x + x, l, mid, ql, qr, target) + query_cnt(x + x + 1, mid + 1, r, ql, qr, target);
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		int x, y;
		scanf("%d.%d", &x, &y);
		a[i] = x * (int) 1e6 + y;
	}
	build(1, 1, n);
	for (int i = 0; i < m; ++ i) {
		int l, r;
		scanf("%d%d", &l, &r);
		val guess = query_guess(1, 1, n, l, r);
		int cnt = query_cnt(1, 1, n, l, r, guess.guess);
		//printf("%d %d\n", guess.guess, cnt);
		if (cnt >= ((r - l + 1) / 2 + 1)) {
			printf("usable\n");
		}
		else {
			printf("unusable\n");
		}
	}
}

