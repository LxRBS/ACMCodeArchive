#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
vector<pair<long long, long long>> coords, balls;
map<char, pair<pair<int, int>, int>> dirs;

main() {
	dirs['L'] = {{-1, 0}, 1};
	dirs['R'] = {{+1, 0}, 1};
	dirs['U'] = {{0, +1}, 2};
	dirs['D'] = {{0, -1}, 2};
	string moves;
	cin >> moves;
	long long step = 3, lastMoved = -1;
	pair<long long, long long> ball = {0, 0};
	for (unsigned int i = 0; i < moves.length(); i++) {
		char c = moves[i];
		auto move = dirs[c].first;
		if (dirs[c].second == lastMoved && i >= 2 && moves[i] == moves[i - 2]) {
			ball = balls[i-2];
		} else {
			ball.first += move.first * step;
			ball.second += move.second * step;
			coords.push_back({ball.first + move.first, ball.second + move.second});
		}
		step = step*2 + 3;
		lastMoved = dirs[c].second;
		balls.push_back(ball);
	}
	balls.pop_back();
	if (find(balls.begin(), balls.end(), ball) != balls.end()) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << -ball.first << " " << -ball.second << endl;
	random_shuffle(coords.begin(), coords.end());
	cout << coords.size() << endl;
	for (pair<long long, long long> &p : coords) {
		cout << (p.first - ball.first) << " " << (p.second - ball.second) << endl;
	}
}
