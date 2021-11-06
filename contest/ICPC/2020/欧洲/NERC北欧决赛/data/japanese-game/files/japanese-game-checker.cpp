#include "japanese-game.h"

bool read_solution(InStream &out, const std::string &mask) {
  const int cnt = out.readInt(-1, mask.size(), "profile size");
  if (cnt == -1) {
    return false;
  }

  std::vector<size_t> profile(cnt);
  for (size_t &i : profile) {
    i = out.readInt(1, mask.size(), "profile[i]");
  }

  const auto profile_requires_length = get_profile_required_length(profile);
  if (profile_requires_length > mask.size()) {
    out.quitf(_wa, "profile is too long: it requires %llu mask length",
              profile_requires_length);
  }

  const auto profile_mask = get_mask(mask.size(), profile);
  if (profile_mask != mask) {
    out.quit(_wa, "profile's mask does not match expected mask\n");
  }

  return true;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  const std::string mask = inf.readString();

  const bool ans_result = read_solution(ans, mask);
  const bool ouf_result = read_solution(ouf, mask);

  if (ans_result && !ouf_result) {
    quitf(_wa, "jury has found the solution, but participant hasn't");
  } else if (!ans_result && ouf_result) {
    quitf(_fail, "participant has found the solution, but jury hasn't");
  } else {
    quitf(_ok, "OK");
  }
}
