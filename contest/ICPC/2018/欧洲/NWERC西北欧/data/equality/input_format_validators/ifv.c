#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_expression(char **s);

void assume_(const char *reason, int condition, int lineno) {
  if (!condition) {
    printf("assume failed at line %d: %s\n", lineno, reason);
    exit(1);
  }
}
#define assume(reason,condition) assume_((reason), (condition), (__LINE__))

void parse_int(char **s) {
  ssize_t length = 0;
  char first = **s;
  while (**s >= '0' && **s <= '9') {
    length += 1;
    ++*s;
  }
  assume("Numbers should not start with '0' (0 < x < 10^9)", first != '0');
  assume("Number is too large (0 < x < 10^9)", 1 <= length && length <= 9);
}

void parse_array(char **s) {
  ++*s;
  while (1) {
    parse_int(s);
    if (**s == ',') ++*s;
    else break;
  }
  assume("Array should end with ']'", **s == ']');
  ++*s;
}

void parse_unary(char **s) {
  ++*s;
  parse_expression(s); assume("Unary expression should end with ')'", **s == ')'); ++*s;
}

void parse_binary(char **s) {
  ++*s;
  parse_expression(s); assume("Binary argument param_1 should be followed by ','", **s == ','); ++*s;
  parse_expression(s); assume("Binary argument param_2 should be followed by ')'", **s == ')'); ++*s;
}

void parse_expression(char **s) {
  if (!strncmp(*s, "[", 1)) return parse_array(s);
  if (!strncmp(*s, "sorted(", 7))  return *s += 6, parse_unary(s);
  if (!strncmp(*s, "shuffle(", 8)) return *s += 7, parse_unary(s);
  if (!strncmp(*s, "concat(", 7))  return *s += 6, parse_binary(s);
  assume("Expression should constitute an array or function call", 0);
}

void validate(void) {
  static char buf[1<<20];
  assume("Input should contain at least two lines", fgets(buf, sizeof buf, stdin) != NULL);

  char *ptr = buf;
  parse_expression(&ptr);
  assume("Input should end with a newline character", *ptr == '\n');
}

int main(int argc, char **argv) {
  validate();
  validate();
  assume("Input should not contain more than two lines", fgetc(stdin) == EOF);
  return 42;
}
