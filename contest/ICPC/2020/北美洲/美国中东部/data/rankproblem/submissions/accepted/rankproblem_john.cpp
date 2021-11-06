#include <iostream>
using namespace std;

const int MAXTEAMS = 100;
const int MAXGAMES = 100;

int order[MAXTEAMS];

int find(int val, int size)
{
    for(int i=0; i<size; i++) {
        if (order[i] == val)
            return i;
    }
    cout << "ERROR: can't find team " << val << endl;
    exit(-1);
}
int main()
{
    int n, m;

    cin >> n >> m;
    for(int i=0; i<n; i++) {
        order[i] = i+1;
    }
    string s1, s2;
    for(int i=0; i<m; i++) {
        cin >> s1 >> s2;
//        cout << s1 << ' ' << s1.substr(1)
        int t1 = stoi(s1.substr(1));
        int t2 = stoi(s2.substr(1));
        int i1 = find(t1, n);
        int i2 = find(t2, n);
        if (i1 > i2) {
            for(int j=i2+1; j<=i1; j++)
                order[j-1] = order[j];
            order[i1] = t2;
        }
    }
    cout << "T" << order[0];
    for(int i=1; i<n; i++)
        cout << " T" << order[i];
    cout << endl;
}
