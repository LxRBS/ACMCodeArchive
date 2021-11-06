#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
  int n;
  cin >> n;
  if(n <= 0) {
    cout << "ERROR: n is too low!" << endl; return 0; }
  if(n > 100)
    {cout << "ERROR: n is too high!" << endl;return 0;}
  vector<string> has(n);
  vector<string> wants(n);
  vector<string> names(n);
  for(int i = 0; i < n; i++){

    cin >> names[i];
    cin >> has[i];
    cin >> wants[i];
    for(int j = 0; j < i; j++){
      if(names[i] == names[j])
{	cout << "ERROR: " << names[i] << " appears twice in names list!" << endl;return 0;}
      if(has[i] == has[j])
{	cout << "ERROR: " << has[i] << " appears twice in has list!" << endl;return 0;}
      if(wants[i] == wants[j])
{	cout << "ERROR: " << wants[i] << " appears twice in wants list!" << endl;return 0;}

    }
  }
  return 42;
}
