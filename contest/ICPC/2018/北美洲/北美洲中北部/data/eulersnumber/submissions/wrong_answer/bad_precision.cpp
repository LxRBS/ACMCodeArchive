#include <iostream>
#include <iomanip>

using namespace std;

double euler(int n) {
  double val = 0;

  long fact = 1;

  if(17 <= n+1)
    n = 17;
  
  for(int i=0; i<n+1; i++) {
    if(i != 0)
      fact *= i;
    val += double(1)/fact;
  }
  
  return val;
}

int main() {
  int n;
  cin >> n;
  
  cout << euler(n) << endl;
  
  return 0;
}
