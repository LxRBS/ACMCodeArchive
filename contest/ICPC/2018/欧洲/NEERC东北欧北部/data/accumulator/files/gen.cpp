#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include "testlib.h"

using namespace std;

int cur_test = -1;
const int MAXT = 360;
const int MAXP = 99;

string itoa(int x) 
{
    stringstream ss;
    string s;
    ss << x;
    ss >> s;
    return s;
}

int atoi(string s) 
{
    stringstream ss;
    int x;
    ss << s;
    ss >> x;
    return x;
}

void write_test(int t, int p) 
{
    startTest(cur_test++);
    cerr << cur_test << endl;
    cout << t << ' ' << p << endl;
}


const int cntT = 4;
const int cntP = 6;
const int interestingT[cntT] = {1, MAXT, -1, -1};
const int interestingP[cntP] = {1, MAXP, 19, 20, 21, -1};

int main(int argc, char * argv[]) 
{
    registerGen(argc, argv, 1);
    cur_test = atoi(argv[1]);
    for (int i = 0; i < cntT; i++)
        for (int j = 0; j < cntP; j++)
        {
            int t = interestingT[i];
            int p = interestingP[j];
            if (t == -1)
                t = rnd.next(1, MAXT);
            if (p == -1)
                p = rnd.next(1, MAXP);
            write_test(t, p);
        }
    return 0;
}