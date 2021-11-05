#include <iostream>
#include <map>
#include <string>
using namespace std;


int main()
{
	int n;
	cin >> n;
	map<string, int> judges;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		++judges[s];
	}
	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		int existing = judges[s];
		if (existing > 0)
		{
			++res;
			judges[s] = existing-1;
		}
	}
	cout << res << endl;
	return 0;
}
