#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int n;

inline int readAndCheckAnswer(InStream& in) {
    int m = in.readInt(-1, 100);
    if (m == -1) {
    	return -1;
    }
    if (m == 0) {
        in.quitf(_wa, "Size of picture can not be equal to zero");
    }
    in.readEoln();
    vector<string> graph;
    for (int i = 0; i < m; i++) {
    	graph.push_back(in.readLine(format("[\\.o]{%d}", m), format("result[%d]", i + 1)));
    }
    reverse(graph.begin(), graph.end());
    int cnt = 0;
    for (int i = 0; i < m; i++) {
    	for (int j = 0; j < m; j++) {
    	    if (graph[i][j] != graph[j][i]) {
                in.quitf(_wa, "Picture is not symmetric: (%d, %d) = %c != %c = (%d, %d)", i + 1, j + 1, graph[i][j], graph[j][i], j + 1, i + 1);
            }
    		if (graph[i][j] == 'o') {
    			cnt++;
    			if (i > 0 && graph[i - 1][j] != 'o') {
    				in.quitf(_wa, "Position (%d, %d) contains 'o', but position (%d, %d) doesn't", i + 1, j + 1, i, j + 1);
    			}
    			if (j > 0 && graph[i][j - 1] != 'o') {
    				in.quitf(_wa, "Position (%d, %d) contains 'o', but position (%d, %d) doesn't", i + 1, j + 1, i + 1, j);
    			}
    		}
    	}
    }
    if (cnt != n) {
    	in.quitf(_wa, "Wrong number of o's: needed %d, but got %d", n, cnt);
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();

    int ja = readAndCheckAnswer(ans);
    int pa = readAndCheckAnswer(ouf);

    if(ja != -1 && pa == -1)
        quitf(_wa, "Jury has the answer but participant has not");
    if(ja == -1 && pa != -1)
        quitf(_fail, "Participant has the answer but jury has not");

    quitf(_ok, "n=%d", n);
}