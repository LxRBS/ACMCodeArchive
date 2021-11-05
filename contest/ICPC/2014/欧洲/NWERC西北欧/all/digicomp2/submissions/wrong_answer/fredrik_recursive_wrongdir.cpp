#include <iostream>
#include <vector>
using namespace std;


struct Switch
{
	long long ballsin;
	char start;
	bool visited;
	int left;
	int right;
	vector<int> inputs;

	void doit();
};

vector<Switch> switches;


void Switch::doit()
{
	if (visited)
		return;
	visited = true;
	for (size_t i = 0; i < inputs.size(); ++i)
		switches[inputs[i]].doit();
	if (start == 'R')
	{
		switches[left].ballsin += (ballsin+1)/2;
		switches[right].ballsin += (ballsin)/2;
	}
	else
	{
		switches[left].ballsin += (ballsin)/2;
		switches[right].ballsin += (ballsin+1)/2;
	}
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
		switches[a].inputs.push_back(i);
		switches[b].inputs.push_back(i);
		switches[i].left = a;
		switches[i].right = b;
		switches[i].start = str[0];
		switches[i].visited = false;
		switches[i].ballsin = 0;
	}
	switches[1].ballsin = balls;
	switches[0].left = 0;
	switches[0].right = 0;
	switches[0].visited = false;
	switches[0].ballsin = 0;
	switches[0].doit();
	for (int i = 1; i <= switchcount; ++i)
		cout << (char)((switches[i].ballsin & 1) == 0 ? switches[i].start : ('L' + 'R' - switches[i].start));
	cout << endl;
	return 0;
}
