#include <iostream>
#include <string>

using namespace std;

int main(){
  string line;
  getline(cin, line);
  int space_pos = line.find(' ');
  if(space_pos == string::npos) {
    cout << "ERROR: Less than 2 numbers on line!" << endl; return 0;
  }
  int new_space_pos = line.find(' ', space_pos+1);
  if(new_space_pos != string::npos) {
    cout << "ERROR: Too many spaces!" << endl; return 0;
  }
  int n = atoi(line.substr(0, space_pos).c_str());
  if(n <= 0) {
    cout << "ERROR: n too low!" << endl; return 0;
  }
  if(n > 5000) {
    cout << "ERROR: n too high!" << endl; return 0;
  }
  int m = atoi(line.substr(space_pos+1, line.size()-space_pos-1).c_str());
  if(m <= 0) {
    cout << "ERROR: m too low!" << endl; return 0;
  }
  if(m > 20) {
    cout << "ERROR: m too high!: " << m << endl; return 0;
  }
  return 42;
}
