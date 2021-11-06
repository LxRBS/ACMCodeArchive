#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>

typedef double FLOAT;

FLOAT log_factorial(int x) { return lgamma(x + 1); }

FLOAT log_nchoosek(int n, int k) {
    return log_factorial(n) - log_factorial(n-k) - log_factorial(k);
}

FLOAT log_multinomial_norm(std::vector<int> const &x) {
    FLOAT mn = log_factorial(std::accumulate(x.begin(), x.end(), 0.0));
    for (auto xi : x)
        mn -= log_factorial(xi);
    return mn;
}

FLOAT log_num_orders(std::vector<int> const &x) {
    std::vector<int> counter(*std::max_element(x.begin(), x.end()) + 1, 0);
    for (auto xi : x)
        counter[xi]++;
    return log_multinomial_norm(counter);
}

FLOAT log_multinomial(std::vector<int> const &x, int k) {
    auto n = std::accumulate(x.begin(), x.end(), 0);
    return log_multinomial_norm(x) - n * log(k);
}

int main() {
    int d;
    std::cin >> d;

    std::vector<int> x(d);
    for (auto &xi : x)
        std::cin >> xi;

    // probability of seeing these birthday collisions on the first d days, out
    // of all 365 days in the year -- this is a multinomial
    FLOAT lm = log_multinomial(x, 365);

    // number of ways of choosing b days out of 365
    FLOAT lnk = log_nchoosek(365, x.size());

    // number of unique ways of ordering the values of x (which may include
    // duplicates)
    FLOAT lno = log_num_orders(x);

    // answer: multinomial * (365 choose b) * (# orderings)
    FLOAT ans = (lm + lnk + lno) / log(10);
    std::cout << std::fixed << std::setprecision(15) << ans << std::endl;

    return 0;
}

