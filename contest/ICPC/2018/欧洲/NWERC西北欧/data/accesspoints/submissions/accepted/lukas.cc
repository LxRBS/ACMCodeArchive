//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <cstdio>

#define rep(i,a,b) for(__typeof(b) i=(a); (i)<(b); ++(i))

struct Cluster {
  Cluster() : count(0), sum(0), sum_squares(0) {}
  Cluster(int el) : Cluster() { AddElement(el); }
  void AddElement(int a) {
    ++count;
    sum += a;
    sum_squares += int64_t(a) * a;
  }
  double Average() const {
    return sum / double(count);
  }
  double Distance() const {
    double avg = Average();
    return avg * avg * count + sum_squares - 2 * avg * sum;
  }
  void Merge(const Cluster & cluster) {
    count += cluster.count;
    sum += cluster.sum;
    sum_squares += cluster.sum_squares;
  }
  int64_t count;
  int64_t sum, sum_squares;
};

double calc(const std::vector<int> & x) {
  std::vector<Cluster> res;
  for (int a : x) {
    if (res.empty()) {
      res.emplace_back(a);
    } else {
      Cluster & cluster = res.back();
      if (cluster.sum >= cluster.count * a) {
        cluster.AddElement(a);
        while (res.size() >= 2 && res.back().Average() < res[res.size() - 2].Average()) {
          res[res.size() - 2].Merge(res.back());
          res.pop_back();
        }
      } else {
        res.emplace_back(a);
      }
    }
  }

  double result = 0;
  for (const auto & c : res) {
    result += c.Distance();
  }
  return result;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n), y(n);
  rep(i,0,n) {
    scanf("%d %d", &x[i], &y[i]);
  }

  double res = calc(x) + calc(y);
  printf("%.9lf\n", res);
}
