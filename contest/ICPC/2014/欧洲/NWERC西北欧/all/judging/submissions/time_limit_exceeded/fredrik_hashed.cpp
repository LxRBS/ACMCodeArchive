#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;


int main()
{
	int n;
	cin >> n;
	hash<string> str_hash;
	list<pair<size_t, string>> judges;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		judges.push_back(make_pair(str_hash(s), s));
	}
	int res = 0;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		size_t h = str_hash(s);
		for (auto it = judges.begin(); it != judges.end(); ++it)
		{
			if (it->first == h && it->second == s)
			{
				++res;
				judges.erase(it);
				break;
			}
		}
	}
	cout << res << endl;
	return 0;
}
