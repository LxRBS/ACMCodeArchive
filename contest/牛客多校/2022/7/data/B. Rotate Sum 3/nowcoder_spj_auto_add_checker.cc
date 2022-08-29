#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#define MAX_LINE 110000

using namespace std;
int isNaN( float f )
{
    unsigned long x = *(unsigned long*)&f;
    return 0!=(x&0x7ffffful) && 0x7f800000ul==(x&0x7f800000ul);
}

int main(int argc, char* argv[]) {
    char output_line[MAX_LINE] = {0};
    char pout_line[MAX_LINE] = {0};
    //ifstream output(argv[2]);
    ifstream output("output");
    ifstream pout("user_output");
    int line_no = 1;
    int error_line_no = 0;
    double foutput = 0;
    double fpout = 0;
    while (output >> foutput) {
        pout >> fpout;
        //cout << foutput << " " <<  fpout << endl;
        if (isNaN(fpout) && error_line_no == 0) {
            //cout << "!1:" << error_line_no << endl;
            error_line_no = line_no;
        }
        // 浮点数的output规范是5位小数
        if (fabs(foutput - fpout)/max(1.0, fabs(foutput)) > 1e-6 && error_line_no == 0) {
            //cout << "!2:" << error_line_no << endl;
            error_line_no = line_no;
        }
        ++line_no;
    }

    while (error_line_no == 0 && pout >> fpout) {
    	error_line_no = line_no - 1;
        break;
    }

    if(error_line_no > 0){
        //cout << "err: " << error_line_no << endl;
        return 1;
    }
    //cout << "OK" << endl;
    return 0;
}