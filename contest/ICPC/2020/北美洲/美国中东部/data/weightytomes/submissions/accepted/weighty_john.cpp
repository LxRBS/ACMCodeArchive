#include <iostream>
using namespace std;

const int MAXHEIGHT = 10000;
const int MAXPALLETS = 100;

int table[MAXPALLETS+1][MAXHEIGHT+1] = {0};

int main()
{
    int h, nP;

    cin >> h >> nP;
    for(int j=0; j<=h; j++)
        table[1][j] = j;

    for(int i=2; i<=nP; i++) {
        for(int j=1; j<=h; j++) {
            int minVal = h+1;
            for(int x=1; x<=j; x++) {
                int v1 = table[i-1][x-1];       // pallet collapses
                int v2 = table[i][j-x];         // pallet doesn't collapse
                if (v2 > v1)
                    v1 = v2;
                if (v1 < minVal)
                    minVal = v1;
            }
            table[i][j] = 1+ minVal;
        }
    }
                                                // redo last pass to get range of values
    int start = -1, stop = MAXHEIGHT+1;
    for(int x=1; x<=h; x++) {
        int v1 = table[nP-1][x-1];       // pallet collapses
        int v2 = table[nP][h-x];         // pallet doesn't collapse
        if (v2 > v1)
            v1 = v2;
        if (v1 + 1 == table[nP][h]) {
            stop = x;
            if (start == -1)
                start = x;
        }

    }
    cout << table[nP][h] << ' ' << start;
    if (stop > start)
        cout << '-' << stop;
    cout << endl;
}
