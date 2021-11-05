#include <cstdio>
#include <set>

using namespace std;
typedef long long ll;
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

int main(void) {
	int N, P, R;
	scanf("%d%d%d", &N, &P, &R);
	multiset<int> X;
	for (int i = 0, x; i < N; ++i)
		scanf("%d", &x), X.insert(x);
	ll prev = *--X.end(), mintime = 1LL<<60, maxtime = 0, tottime = 0;
	for (auto start = X.begin(); start != X.end(); ++start) {
		multiset<int> pos = X;
		ll at = *start, time = 0;
		while (!pos.empty()) {
			auto it = pos.lower_bound(at);
			if (it == pos.end()) it = pos.begin();
			time += (*it-at+P)%P + R;
			at = (*it+R)%P;
			pos.erase(it);
		}
		mintime = min(mintime, time);
		ll gap = (*start - prev + P) % P;
		maxtime = max(maxtime, time + gap - 1);
		tottime = tottime + time*gap + gap*(gap-1)/2;
		prev = *start;
	}
	ll d = gcd(tottime, P);
	printf("%lld\n%lld\n%lld/%lld\n", mintime, maxtime, tottime/d, P/d);
	return 0;
}
