#include <iostream>
#include <algorithm>
#include <list>

using namespace std;
typedef long long ll;

ll N, jeff, vals[100000], steps = 0;
list<pair<ll, int>> valFrequency;
list<pair<ll, int>>::iterator getSecond() {
	auto it = valFrequency.begin();
	return ++it;
}

void step(ll todo) {
	auto it = getSecond();
	if (it == valFrequency.end() || it->first + 1 < valFrequency.front().first) {
		valFrequency.insert(it, make_pair(valFrequency.front().first - 1, 0));
		it = getSecond();
	}
	int curLargestCount = valFrequency.front().second;
	ll curLargestVal = valFrequency.front().first;
	if (it->second == 0) {
		int logtwo = 0, tmp = curLargestCount;
		while (tmp >>= 1) logtwo++;
		logtwo++;
		if (++it != valFrequency.end()) todo = min(todo, curLargestVal - it->first);
		if (curLargestCount == 1) todo = curLargestVal - it->first;
		ll howmuch = todo/logtwo - 1;
		if (howmuch > 0) { // combine steps
			steps += logtwo * howmuch;
			jeff -= logtwo * howmuch;
			valFrequency.pop_front();
			valFrequency.front().second += curLargestCount;
			valFrequency.front().first = curLargestVal - howmuch;
			return;
		}
	}
	// single step
	steps++; jeff--;
	if (curLargestCount == 1) {
		valFrequency.pop_front();
		valFrequency.front().second++;
	} else {
		int shift = valFrequency.front().second - valFrequency.front().second / 2;
		valFrequency.front().second /= 2;
		getSecond()->second += shift;
	}
}

int main() {
	cin >> N >> jeff;
	N--;
	for (ll i = 0; i < N; i++) cin >> vals[i];
	sort(vals, vals + N);
	reverse(vals, vals + N);
	ll lastVal = vals[0], count = 0;
	for (ll i = 0; i < N; i++, count++) if (lastVal != vals[i]) {
		valFrequency.push_back(make_pair(lastVal, count));
		lastVal = vals[i], count = 0;
	}
	valFrequency.push_back(make_pair(lastVal, count));
	while (jeff >= valFrequency.front().first) step(jeff - valFrequency.front().first);
	cout << steps-1 << endl;
	return 0;
}
