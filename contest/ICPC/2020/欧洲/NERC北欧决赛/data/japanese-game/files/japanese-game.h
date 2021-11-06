#ifndef NERC_2021_JAPANESE_GAME_H
#define NERC_2021_JAPANESE_GAME_H

#include <numeric>
#include <string>
#include <vector>

#include "testlib.h"

const size_t MIN_MASK_LENGTH = 1;
const size_t MAX_MASK_LENGTH = 100'000;

enum cell_t : char {
  BLACK = '#',
  EMPTY = '_',
};

static inline unsigned long long get_profile_required_length(const std::vector<size_t> &profile) {
  return profile.empty() ? 0 : std::accumulate(profile.begin(), profile.end(), 0ULL) + profile.size() - 1;
}

static inline std::string get_mask(size_t length, const std::vector<size_t> &profile) {
  std::string res(length, cell_t::EMPTY);
  if (profile.empty()) {
    return res;
  }
  const auto profile_length = get_profile_required_length(profile);
  ensure(profile_length <= length);
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
  ensure(i <= length);
  return res;
}

#endif //NERC_2021_JAPANESE_GAME_H
