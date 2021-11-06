#include "japanese-game.h"

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  const auto mask_pattern = format("[%c%c]{%zu,%zu}", cell_t::EMPTY, cell_t::BLACK, MIN_MASK_LENGTH, MAX_MASK_LENGTH);

  inf.readToken(mask_pattern, "mask");
  inf.readEoln();
  inf.readEof();
}
