// [NWERC'14] DigiComp II, by Jan Kuipers

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
  long long total_balls;
  int switches;
  cin >> total_balls >> switches;
  string state(switches+1, 0);
  vector<int> left(switches+1), right(switches+1);
  vector<int> indegree(switches+1, 0);
  vector<long long> balls(switches+1, 0);
  balls[1] = total_balls;
  for (int i=1; i<=switches; i++) {
    cin >> state[i] >> left[i] >> right[i];
    indegree[left[i]]++;
    indegree[right[i]]++;
  }
  queue<int> q;
  for (int i=1; i<=switches; i++) {
    if (indegree[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    if (i == 0) continue;
    if (state[i] == 'L') {
      balls[left[i]] += (balls[i] + 1) / 2;
      balls[right[i]] += balls[i] / 2;
      if (balls[i] % 2 == 1) state[i] = 'R';
    } else {
      balls[left[i]] += balls[i] / 2;
      balls[right[i]] += (balls[i] + 1) / 2;
      if (balls[i] % 2 == 1) state[i] = 'L';
    }
    indegree[left[i]]--;
    if (indegree[left[i]] == 0) q.push(left[i]);
    indegree[right[i]]--;
    if (indegree[right[i]] == 0) q.push(right[i]);
  }
  cout << state.substr(1) << endl;
  return 0;
}
