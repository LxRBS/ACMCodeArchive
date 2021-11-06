#include "testlib.h"

int MAX_N = 100;
int MAX_K = 100;
int MAX_LEN = 10;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(1, MAX_N, "n");
  inf.readSpace();
  int k = inf.readInt(1, n, "k");
  inf.readEoln();

  std::set<std::string> subjects;
  for (int i = 0; i < k; i++) {
    std::string subj = inf.readLine();
    ensure(subjects.count(subj) == 0);
    subjects.insert(subj);
    int len = subj.find_last_of(" ") + 1;
    ensure(len % 4 == 0);
    int re = len / 4;
    for (int i = 0; i < re; i++){
//      ensure(subject.substr(4 * i, 4 * i + 4) == "Re: ");
      ensure(subj[4 * i] == 'R');
      ensure(subj[4 * i + 1] == 'e');
      ensure(subj[4 * i + 2] == ':');
      ensure(subj[4 * i + 3] == ' ');
    }
    for (int i = len; i < subj.length(); i++) {
      ensure('a' <= subj[i] && subj[i] <= 'z');
    }
    ensure(subj.length() - len >= 1);
    ensure(subj.length() - len <= 10);
    ensure(subj.length() <= 500);
  }
  inf.readEof();
}