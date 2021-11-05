// [NWERC'14] Double Edge, by Jan Kuipers

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > conn;
int next_freq;
vector<int> freq1, freq2;

void solve(int n, int freq, int parent) {
  freq1[n] = next_freq++;
  freq2[n] = freq;
  for (int i=0; i<conn[n].size(); i++) {
    int j = conn[n][i];
    if (j == parent)
      continue;
    solve(j, freq1[n], n);
    swap(freq1[n], freq2[n]);
  }
}

int main() {
  int N;
  cin >> N;
  conn = vector<vector<int> >(N);
  freq1 = freq2 = vector<int>(N);
  for (int i=0; i<N-1; i++) {
    int a,b;
    cin >> a >> b;
    a--; b--;
    conn[a].push_back(b);
    conn[b].push_back(a);
  }
  if (N == 2) {
    cout << "0 1" << endl;
    cout << "0 1" << endl;
  } else {
    next_freq = 1;
    solve(0, 0, N-1);
    for (int i=0; i<N; i++) {
      cout << freq1[i] << " " << freq2[i] << endl;
    }
  }
  return 0;
}
