#include <iostream>
#include <string>
using namespace std;

int main(){
	int n, m; cin >> n >> m;
	string e, b; cin >> e >> b;
	string a(m, '.');
	for(int i = 0; i < n; ++i) a[i+m-n] = e[i];
	for(int i = m-n-1; i >= 0; --i) a[i] = (b[i+n] - a[i+n] + 26)%26 + 'a';
	cout << a << endl;
}
