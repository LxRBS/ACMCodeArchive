#include "japanese-game.h"

const size_t DEFAULT_EMPTY_SUFFIX = 0;
const size_t DEFAULT_ATTEMPTS = 10;

const size_t SQRT_MAGIC = 400;
const size_t TAKE_TOPS = 10;

const double EPS = 1e-5;

std::optional<std::vector<size_t>> get_rand_partition(size_t sum, const std::vector<size_t> &values) {
  ensure(values.size() <= SQRT_MAGIC);

  std::vector<std::vector<double>> dps(values.size() + 1, std::vector<double>(sum + 1));
  dps[0][0] = 1;

  for (size_t i = 0; i < values.size(); i++) {
    const auto x = values[i];
    const auto &dp = dps[i];
    auto &next_dp = dps[i + 1];

    next_dp = dp;
    for (size_t n = x; n <= sum; n++) {
      next_dp[n] += next_dp[n - x];
    }
  }

  size_t i = values.size();
  size_t n = sum;
  if (dps[i][n] < EPS) {
    return std::nullopt;
  }

  std::vector<size_t> result;
  while (n > 0) {
    ensure(i > 0);
    const auto all = dps[i][n];
    ensure(all > EPS);
    const auto x = values[i - 1];
    const auto take = n >= x ? dps[i][n - x] : 0;
    const auto no = dps[i - 1][n];
    ensure(doubleCompare(take + no, all, EPS));
    if (rnd.next(all) < take) {
      ensure(n >= x);
      n -= x;
      result.push_back(x);
    } else {
      ensure(i > 0);
      i--;
    }
  }

  shuffle(result.begin(), result.end());

  return result;
}

std::optional<std::vector<size_t>> try_get_rand_partition(size_t sum, size_t min, size_t max, size_t attempts) {
  std::vector<size_t> values(max - min + 1);
  std::iota(values.begin(), values.end(), min);
  ensure(values.back() == max);

  if (values.size() <= SQRT_MAGIC) {
    return get_rand_partition(sum, values);
  }

  std::vector<size_t> edges(values.begin(), values.begin() + TAKE_TOPS);
  edges.insert(edges.end(), values.end() - TAKE_TOPS, values.end());

  values.erase(values.begin(), values.begin() + TAKE_TOPS);
  values.erase(values.end() - TAKE_TOPS, values.end());

  for (size_t i = 0; i < attempts; i++) {
    shuffle(values.begin(), values.end());
    std::vector<size_t> cut_values(values.begin(), values.begin() + SQRT_MAGIC - 2 * TAKE_TOPS);
    cut_values.insert(cut_values.end(), edges.begin(), edges.end());
    auto maybe_partition = get_rand_partition(sum, cut_values);
    if (maybe_partition.has_value()) {
      return maybe_partition;
    }
  }

  return std::nullopt;
}

std::vector<size_t> partition_to_profile(std::vector<size_t> partition) {
  for (auto &x : partition) {
    ensure(x >= 2);
    x--;
  }
  return partition;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const auto length = opt<size_t>("length");
  const auto min = opt<size_t>("min");
  const auto max = opt<size_t>("max");
  const auto empty_suffix = has_opt("empty") ? opt<size_t>("empty") : DEFAULT_EMPTY_SUFFIX;
  const auto attempts = has_opt("attempts") ? opt<size_t>("attempts") : DEFAULT_ATTEMPTS;

  ensure(length >= 1);
  ensure(empty_suffix <= length);
  ensure(1 <= min && min <= max && max <= length - empty_suffix);
  ensure(attempts >= 1);

  const auto maybe_partition =
          length == empty_suffix
          ? std::vector<size_t>()
          : try_get_rand_partition(length - empty_suffix + 1, min + 1, max + 1, attempts);

  ensure(maybe_partition.has_value());

  const auto profile = partition_to_profile(maybe_partition.value());

  ensure(get_profile_required_length(profile) == length - empty_suffix);
  if (!profile.empty()) {
    ensure(*std::min_element(profile.begin(), profile.end()) >= min);
    ensure(*std::max_element(profile.begin(), profile.end()) <= max);
  } else {
    ensure(length == empty_suffix);
  }

  const auto mask = get_mask(length, profile);

  std::cout << mask << std::endl;
}
