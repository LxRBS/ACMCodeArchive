#include "japanese-game.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  const auto length = opt<size_t>("length");
  const auto profile_str = split(opt<std::string>("profile"), ',');

  std::vector<size_t> profile;
  profile.reserve(profile_str.size());
  for (const auto &x : profile_str) {
    profile.push_back(atoi(x.c_str()));
  }

  const auto mask = get_mask(length, profile);

  std::cout << mask << std::endl;
}
