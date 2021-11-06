#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

const char * const NO_SOLUTION = "-1";

enum cell_t : char {
  BLACK = '#',
  EMPTY = '_',
};

std::vector<size_t> get_profile(const std::string &mask) {
  std::vector<size_t> profile;
  for (size_t i = 0; i < mask.size();) {
    if (mask[i] != cell_t::BLACK) {
      i++;
      continue;
    }
    size_t j = i;
    while (j < mask.size() && mask[j] == cell_t::BLACK) {
      j++;
    }
    profile.push_back(j - i);
    i = j;
  }
  return profile;
}

std::string get_mask(size_t length, const std::vector<size_t> &profile) {
  std::string res(length, cell_t::EMPTY);
  if (profile.empty()) {
    return res;
  }
  const size_t profile_length = std::accumulate(profile.begin(), profile.end(), 0LU) + profile.size() - 1U;
  assert(profile_length <= length);
  bool first = true;
  size_t i = 0;
  for (auto block : profile) {
    if (!first) {
      i++;
    }
    for (size_t iter = 0; iter < length - profile_length; iter++) {
      if (block == 0) {
        break;
      }
      block--;
      i++;
    }
    while (block > 0) {
      res[i++] = cell_t::BLACK;
      block--;
    }
    first = false;
  }
  assert(i <= length);
  return res;
}

int main() {
  const std::string mask = ({
    std::string s;
    std::cin >> s;
    s;
  });

  for (size_t cells_bits = 0; cells_bits < (1 << mask.size()); cells_bits++) {
    std::string cells(mask.size(), cell_t::EMPTY);
    for (size_t i = 0; i < mask.size(); i++) {
      if ((cells_bits >> i) & 1) {
        cells[i] = cell_t::BLACK;
      }
    }
    const auto profile = get_profile(cells);
    const auto profile_mask = get_mask(mask.size(), profile);
    if (profile_mask == mask) {
      std::cout << profile.size() << '\n';
      for (auto i : profile) {
        std::cout << i << ' ';
      }
      std::cout << std::endl;
      return 0;
    }
  }

  std::cout << NO_SOLUTION << std::endl;
}
