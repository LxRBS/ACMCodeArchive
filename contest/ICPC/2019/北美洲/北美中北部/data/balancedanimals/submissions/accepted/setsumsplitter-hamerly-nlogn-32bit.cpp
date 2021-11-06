#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <numeric>
#include <cassert>

// solution with 32-bit signed integers

int main() {
    int m;
    std::cin >> m;

    std::vector<unsigned long long> weights(m);
    std::vector<int> multiplicity(20001, 0);
    for (auto &w : weights) {
        std::cin >> w;
        multiplicity[w]++;
    }

    std::sort(weights.begin(), weights.end());

    std::vector<int> unique_weights;
    for (auto w : weights)
        if ((unique_weights.size() == 0) || (unique_weights.back() != w))
            unique_weights.push_back(w);

    int sum = std::accumulate(weights.begin(), weights.end(), 0),
        left_sum = 0, answer = 0;
    bool has_answer = false;
    for (size_t i = 0; (!has_answer) && (i < unique_weights.size()); ++i) {
        auto w = unique_weights[i];
        // if w is a particular weight, ignore all copies of that weight
        if (left_sum == (sum - left_sum - w * multiplicity[w])) {
            answer = w;
            has_answer = true;
        // otherwise, if w+1 is not part of the original weights, consider
        // it (and don't ignore any weights)
        } else if ((i + 1 < unique_weights.size()) && ((w + 1) != unique_weights[i+1])) {
            auto ls = left_sum + w * multiplicity[w];
            if (ls == sum - ls) {
                answer = w + 1;
                has_answer = true;
            }
        }

        left_sum += w * multiplicity[w];
    }

    std::cout << answer << std::endl;
    assert(has_answer);

    return 0;
}
