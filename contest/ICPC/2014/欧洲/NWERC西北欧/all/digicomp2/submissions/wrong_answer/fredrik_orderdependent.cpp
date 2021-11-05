#include <iostream>
#include <set>
#include <vector>
using namespace std;


struct Switch
{
	long long ballsin;
	char start;
	bool visited;
	int idx;
	int left;
	int right;
	set<int> inputs;

	void doit();
};

vector<Switch> switches;


void Switch::doit()
{
	visited = true;
	if (start == 'L')
	{
		switches[left].ballsin += (ballsin+1)/2;
		switches[right].ballsin += (ballsin)/2;
	}
	else
	{
		switches[left].ballsin += (ballsin)/2;
		switches[right].ballsin += (ballsin+1)/2;
	}
	switches[left].inputs.erase(idx);
	switches[right].inputs.erase(idx);
}

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
		switches[a].inputs.insert(i);
		switches[b].inputs.insert(i);
		switches[i].idx = i;
		switches[i].left = a;
		switches[i].right = b;
		switches[i].start = str[0];
		switches[i].visited = false;
		switches[i].ballsin = 0;
	}
	switches[1].ballsin = balls;
	for (int i = 1; i <= switchcount; ++i)
		switches[i].doit();
	for (int i = 1; i <= switchcount; ++i)
		cout << (char)((switches[i].ballsin & 1) == 0 ? switches[i].start : ('L' + 'R' - switches[i].start));
	cout << endl;
	return 0;
}
