#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

// use an O(m^2) approach rather than O(m log m)

int main() {
    int m;

    std::cin >> m;

    std::vector<int> weights(m);
    std::vector<int> multiplicity(65536, 0);
    for (auto &w : weights) {
        std::cin >> w;
        multiplicity[w]++;
    }

    int answer = -1;
    for (auto w0 : weights) {
        auto upper = multiplicity[w0+1] == 0 ? w0 + 1 : w0;
        for (auto target = w0; target <= upper; ++target) {
            int lower_weight = 0, higher_weight = 0;
            for (auto w : weights) {
                if (w < target) {
                    lower_weight += w;
                } else if (target < w) {
                    higher_weight += w;
                }
            }

            if (lower_weight == higher_weight) {
                answer = target;
                break;
            }
        }

        if (answer != -1) {
            break;
        }
    }

    assert(answer != -1);
    std::cout << answer << std::endl;

    return 0;
}

