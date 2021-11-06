#include <bits/stdc++.h>
using namespace std;

const int N = 100100;
int num_people;
long long score[N]; // initial scores

int log2(int x) {
	return 31-__builtin_clz(x);
}

struct state {
	long long steps;      // number of rounds so far
	long long max_score;  // highest_score
	int max_count;        // number of people with score max_score
	int almost_max_count; // number of people with score max_score-1
	long long next_score; // next lower score
	int next;             // index of person with that score

	state(): steps(-1), max_score(score[1]), max_count(1), almost_max_count(0), next(2) {
		while (score[next] == max_score) {
			max_count++;
			next++;
		}
		while (score[next] == max_score-1) {
			almost_max_count++;
			next++;
		}
		next_score = score[next];
	}

	void advance() {
		if (max_score > score[0]) {
			cout << steps << endl;
			exit(0);
		}
		
		steps++;
		almost_max_count += (max_count+1)/2;
		max_count /= 2;
		if (max_count == 0) swap(max_count,almost_max_count);
		else max_score++;
		next_score++;
		
		while (next_score == max_score-1) {
			almost_max_count++;
			next_score -= score[next]-score[next+1];
			next++;
		}
	}

	void advance_fast() {
		while (almost_max_count > 0) advance();
		
		int steps_per_round = log2(max_count)+1;
		long long number_of_rounds = max_score - next_score - 2;
		if (steps_per_round > 1) {
			number_of_rounds = min(number_of_rounds, (score[0]-max_score)/(steps_per_round-1));
		}

		steps += number_of_rounds * steps_per_round;
		max_score += number_of_rounds * (steps_per_round - 1);
		next_score += number_of_rounds * steps_per_round;
		
		while (steps_per_round--) advance();
	}
};

int main() {
	cin >> num_people;
	for (int i = 0; i < num_people; i++) cin >> score[i];
	sort(score, score+num_people, greater<long long>());
	score[num_people] = -1e16; // choosing this value for 'negative infinity' is a bad idea...
	
	state st;
	while (true) st.advance_fast();
}
