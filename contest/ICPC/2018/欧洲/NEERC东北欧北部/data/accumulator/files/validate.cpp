#include "testlib.h"
#include <string>
using namespace std;

const int MAXT = 360;
const int MAXP = 99;

int main(int argc, char* argv[]) 
{
    registerValidation(argc, argv);
    inf.readInt(1, MAXT, "t");
    inf.readSpace();
    inf.readInt(1, MAXP, "p");
    inf.readEoln();
    inf.readEof();
    return 0;
}