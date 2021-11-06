#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

const char * const NO_SOLUTION = "-1";

enum cell_t : char {
  BLACK = '#',
  EMPTY = '_',
};

bool mask_is_dense(const std::string &mask) {
  if (mask.front() != cell_t::BLACK || mask.back() != cell_t::BLACK) {
    return false;
  }
  for (size_t i = 0; i + 1 < mask.size(); i++) {
    if (mask[i] != cell_t::BLACK && mask[i + 1] != cell_t::BLACK) {
      return false;
    }
  }
  return true;
}

bool mask_is_empty(const std::string &mask) {
  return std::all_of(mask.begin(), mask.end(), [](char x) {
    return x == cell_t::EMPTY;
  });
}

void print_profile(const std::string &cells) {
  std::vector<size_t> profile;
  for (size_t i = 0; i < cells.size();) {
    if (cells[i] != cell_t::BLACK) {
      i++;
      continue;
    }
    size_t j = i;
    while (j < cells.size() && cells[j] == cell_t::BLACK) {
      j++;
    }
    profile.push_back(j - i);
    i = j;
  }
  std::cout << profile.size() << '\n';
  for (auto i : profile) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

std::optional<std::string> append_mask(std::string mask, size_t by_length) {
  std::reverse(mask.begin(), mask.end());
  size_t more_blacks = 0;
  for (char &cell : mask) {
    if (cell == cell_t::BLACK) {
      more_blacks = by_length;
    } else {
      if (more_blacks > 0) {
        cell = cell_t::BLACK;
        more_blacks--;
      }
    }
  }
  if (more_blacks > 0) {
    return std::nullopt;
  }
  std::reverse(mask.begin(), mask.end());
  for (size_t i = 0; i < by_length; i++) {
    if (mask.back() != cell_t::EMPTY) {
      return std::nullopt;
    }
    mask.pop_back();
  }
  return mask;
}

std::optional<std::string> try_fill_gaps(std::string cells, bool allow_two) {
  for (size_t i = 0; i < cells.size();) {
    if (cells[i] != cell_t::EMPTY) {
      i++;
      continue;
    }
    size_t j = i;
    while (j < cells.size() && cells[j] == cell_t::EMPTY) {
      j++;
    }
    const size_t gap_length  = j - i;
    assert(gap_length > 0);
    const bool at_begin = i == 0;
    const bool at_end = j == cells.size();
    const size_t from = i + (at_begin ? 0 : 1);
    const size_t to = j - (at_end ? 0 : 1);
    i = j;
    if (gap_length == 1) {
      if (at_begin || at_end) {
        return std::nullopt;
      }
      continue;
    }
    if (gap_length == 2) {
      if (at_begin) {
        cells.front() = cell_t::BLACK;
        continue;
      }
      if (at_end) {
        cells.back() = cell_t::BLACK;
        continue;
      }
      return std::nullopt;
    }
    assert(from < to);
    for (size_t pos = from; pos < to; pos += 2) {
      cells[pos] = cell_t::BLACK;
    }
    if ((to - from) % 2 == 0) {
      if (allow_two) {
        cells[to - 1] = cell_t::BLACK;
      } else {
        return std::nullopt;
      }
    }
  }
  return cells;
}

int main() {
  const std::string mask = ({
    std::string s;
    std::cin >> s;
    s;
  });

  std::cerr << "mask: " << mask << std::endl;

  assert(!mask.empty());
  assert(std::all_of(mask.begin(), mask.end(), [](char x) {
    return x == cell_t::BLACK || x == cell_t::EMPTY;
  }));

  if (mask_is_dense(mask) || mask_is_empty(mask)) {
    print_profile(mask);
    return 0;
  }

  std::cerr << "  not dense, not empty" << std::endl;

  for (size_t empty_suff_len = 1; empty_suff_len <= 3; empty_suff_len++) {
    std::cerr << "  go " << empty_suff_len << std::endl;
    const auto mid_result = append_mask(mask, empty_suff_len);
    std::cerr << "    mid result = " << mid_result.value_or("(none)") << std::endl;
    const bool allow_two = empty_suff_len > 1;
    std::cerr << "    allow_two = " << allow_two << std::endl;
    const auto result = mid_result ? try_fill_gaps(mid_result.value(), allow_two) : std::nullopt;
    std::cerr << "    result = " << result.value_or("(none)") << std::endl;
    if (result.has_value()) {
      print_profile(result.value());
      return 0;
    }
  }

  std::cout << NO_SOLUTION << std::endl;
}
