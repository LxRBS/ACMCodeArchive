#include <iostream>
#include <iomanip>

using namespace std;

double euler(int n) {
  double val = 0;

  long fact = 1;
  
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
  
  cout << fixed << setprecision(16);
  
  cout << euler(n) << endl;
  
  return 0;
}
