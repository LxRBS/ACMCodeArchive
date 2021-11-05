// [NWERC'14] Gathering, by Jan Kuipers

#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N;

vector<long long> get_distances(vector<long long>& x) {
  vector<long long> dist(N);
  for (int i=0; i<N; i++) {
    dist[0] += x[i] - x[0];
  }
  for (int i=1; i<N; i++) {
    dist[i] = dist[i-1] + (x[i]-x[i-1]) * (2*i-N);
  }
  return dist;
}

long long get_distance(long long X, vector<long long>& x, vector<long long>& dist) {
  if (X > x.back()) {
    return dist.back() + x.size() * (X - x.back());
  }
  int i = lower_bound(x.begin(), x.end(), X) - x.begin();
  return dist[i] + (X-x[i]) * (2*i-N);
}

void add_off_by_one(vector<long long>& posx, vector<long long>& posy,
		    long long x, long long y) {
  posx.push_back(x); posy.push_back(y);
  posx.push_back(x+1); posy.push_back(y);
  posx.push_back(x); posy.push_back(y+1);
  posx.push_back(x+1); posy.push_back(y+1);
}

int main() {
  cin >> N;
  vector<long long> x(N), y(N);
  for (int i=0; i<N; i++) {
    cin >> x[i] >> y[i];
  }
  long long D;
  cin >> D;
  long long mind1 = -LONG_LONG_MAX, maxd1 = LONG_LONG_MAX;
  long long mind2 = -LONG_LONG_MAX, maxd2 = LONG_LONG_MAX;
  
  for (int i=0; i<N; i++) {
    mind1 = max(mind1, x[i]+y[i]-D);
    maxd1 = min(maxd1, x[i]+y[i]+D);
    mind2 = max(mind2, x[i]-y[i]-D);
    maxd2 = min(maxd2, x[i]-y[i]+D);
  }
  if (mind1>maxd1 || mind2>maxd2) {
    cout << "impossible" << endl;
    return 0;
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  vector<long long> x_distance = get_distances(x);
  vector<long long> y_distance = get_distances(y);

  long long X=x[N/2], Y=y[N/2];
  long long d1=X+Y, d2=X-Y;
  if (d1>=mind1 && d1<=maxd1 && d2>=mind2 && d2<=maxd2) {
    cout << (get_distance(X, x, x_distance) + get_distance(Y, y, y_distance)) << endl;
    return 0;
  }

  vector<long long> posx, posy;
  for (int i=0; i<N; i++) {
    posx.push_back(x[i]); posy.push_back(mind1-x[i]);
    posx.push_back(x[i]); posy.push_back(maxd1-x[i]);
    posx.push_back(x[i]); posy.push_back(x[i]-mind2);
    posx.push_back(x[i]); posy.push_back(x[i]-maxd2);
    posy.push_back(y[i]); posx.push_back(mind1-y[i]);
    posy.push_back(y[i]); posx.push_back(maxd1-y[i]);
    posy.push_back(y[i]); posx.push_back(y[i]+mind2);
    posy.push_back(y[i]); posx.push_back(y[i]+maxd2);
  }
  add_off_by_one(posx, posy, (mind1+mind2)/2, (mind1-mind2)/2);
  add_off_by_one(posx, posy, (mind1+maxd2)/2, (mind1-maxd2)/2);
  add_off_by_one(posx, posy, (maxd1+mind2)/2, (maxd1-mind2)/2);
  add_off_by_one(posx, posy, (maxd1+maxd2)/2, (maxd1-maxd2)/2);
  long long result = LONG_LONG_MAX;
  for (int i=0; i<posx.size(); i++) {
    long long d1=posx[i]+posy[i], d2=posx[i]-posy[i];
    if (d1>=mind1 && d1<=maxd1 && d2>=mind2 && d2<=maxd2) {
      long long distance =
	get_distance(posx[i], x, x_distance) + get_distance(posy[i], y, y_distance);
      result = min(result, distance);
    }
  }
  cout << result << endl;
  return 0;
}
