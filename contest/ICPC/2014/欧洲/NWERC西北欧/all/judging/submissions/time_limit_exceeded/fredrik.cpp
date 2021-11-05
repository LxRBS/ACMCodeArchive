#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;


int main()
{
	int n;
	cin >> n;
	list<string> judges;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		judges.push_back(s);
	}
	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		auto it = find(judges.begin(), judges.end(), s);
		if (it != judges.end())
		{
			++res;
			judges.erase(it);
		}
	}
	cout << res << endl;
	return 0;
}
