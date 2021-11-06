#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    setName("Interactor for Is It Rated?");
    registerInteraction(argc, argv);
    
    int n = inf.readInt();
    int m = inf.readInt();

    cout << n << " " << m << endl;

    for (int i = 0; i < m; i++)
    {
        setTestCase(i);
        string s = inf.readToken();
        int a = inf.readInt();

        cout << s << endl;

        tout << ouf.readInt() << endl;

        cout << a << endl;
    }
    unsetTestCase();

    quitf(_ok, "%d queries processed", m);
}