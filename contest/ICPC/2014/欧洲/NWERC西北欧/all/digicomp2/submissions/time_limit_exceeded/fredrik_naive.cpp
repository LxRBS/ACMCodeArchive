#include <iostream>
#include <set>
#include <vector>
using namespace std;


struct Switch
{
	int dir;
	int ends[2];
};

vector<Switch> switches;


int main()
{
	long long balls;
	int switchcount;
	cin >> balls >> switchcount;
	switches.resize(switchcount+1);
	for (int i = 1; i <= switchcount; ++i)
	{
		char str[4];
		int a, b;
		cin >> str >> a >> b;
		switches[i].dir = str[0] == 'R';
		switches[i].ends[0] = a;
		switches[i].ends[1] = b;
	}
	for (int i = 0; i < balls; ++i)
	{
		for (int k = 1; k != 0; )
		{
			Switch &s = switches[k];
			k = s.ends[s.dir];
			s.dir = 1 - s.dir;
		}
	}
	for (int i = 1; i <= switchcount; ++i)
		cout << ((switches[i].dir == 0) ? 'L' : 'R');
	cout << endl;
	return 0;
}
