#include "testlib.h"
#include <stack>

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string output = ouf.readLine();
    string answer = ans.readLine();

    if (output == "Keine Loesung") {
        if (output != answer)
            quitf(_wa, "Solution exists, `Keine Loesung' found");
    }
    else {
        // Check, whether the output consists only of [ and ]
        for (int i = 0; i < output.size(); i++)
            if (output[i] != '[' && output[i] != ']')
               quitf(_wa, "Unexpected symbol `%c' in output `%s'", output[i], output.c_str());

        // Check, whether the output is of correct length
        string s = inf.readLine();
        if (s.size()/2 != output.size())
            quitf(_wa, "Wrong solution length: %lu instead of %lu", output.size(), s.size()/2);

        // Check, whether the output is the quotation structure of the input
        stack<char> brackets;
        for (int i = 0; i < s.size()/2; i++) {
            char sym = output[i];
            switch (sym) {
                case '[': 
                    brackets.push(s[2*i]); break;

                case ']': 
                    if (brackets.empty())
                        quitf(_wa, "`]' closes not opened quotes pair");
                    if (brackets.top() == s[2*i])
                        quitf(_wa, "`]' closes quote of the same type `%c'", s[2*i]);
                    brackets.pop();
                    break;

                default:
                    quitf(_wa, "Unexpected symbol `%c' instead of `[' or `]'", sym);
            }
        }

        if(!brackets.empty())
            quitf(_wa, "Non-matched brackets remain");

        if (answer == "Keine Loesung")
            quitf(_fail, "Jury: `Keine Loesung', contestant: acceptable solution.");
    }

    quitf(_ok, "Ok");
}