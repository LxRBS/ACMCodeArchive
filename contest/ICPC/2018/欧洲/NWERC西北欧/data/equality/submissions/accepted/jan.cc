// [NWERC'18] Equality Control, by Jan Kuipers

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> parse_flat(const string& s, int& i) {
  int open = 0;
  vector<int> result;
  do {
    if (s[i]=='(' || s[i]=='[') {
      open++;
      i++;
    } else if (s[i]==')' || s[i]==']') {
      open--;
      i++;
    } else if (isdigit(s[i])) {
	int n=0;
	while (isdigit(s[i])) {
	  n = 10*n+s[i]-'0';
	  i++;	
	}
	result.push_back(n);
    } else {
      i++;
    }
  } while (open > 0);
  return result;
}

vector<pair<vector<int>, bool>> parse(const string& s) {
  vector<pair<vector<int>, bool>> result;
  int i=0;
  while (i < s.size()) {
    if (s[i]=='c') {
      i+=7;
    } else if (s[i]==',' || s[i]==')') {
      i++;
    } else if (s[i]=='[') {
      result.push_back(make_pair(parse_flat(s,i), false));
    } else if (s[i]=='s') {
      bool shuffle = s[i+1]=='h';
      i += (shuffle ? 7 : 6);
      result.push_back(make_pair(parse_flat(s,i), false));
      sort(result.back().first.begin(), result.back().first.end());
      if (shuffle) {
	for (int i : result.back().first) {
	  if (i != result.back().first[0]) {
	    result.back().second = true;
	    break;
	  }
	}
      }
    }
  }
  vector<pair<vector<int>, bool>> merged;
  for (pair<vector<int>,bool> item : result) {
    if (!merged.empty() && !merged.back().second && !item.second) {
      merged.back().first.insert(merged.back().first.end(),
				 item.first.begin(), item.first.end());
    } else {
      merged.push_back(item);
    }
  }
  return merged;
}

int main() {
  string s1, s2;
  cin >> s1 >> s2;
  cout << (parse(s1) == parse(s2) ? "equal" : "not equal") << endl;
  return 0;
}
