// usage: ./a.out input_file correct_output output_dir < contestants_output
// See specification there:
// http://www.problemarchive.org/wiki/index.php/Output_validator

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "validate.h"

using namespace std;
int main(int argc, char **argv) {
    init_io(argc, argv);

    int K;
    int L;
    judge_in >> K;
    judge_in >> L;

    char answer[11];
    char output[11];
    judge_ans >> answer;
    if (!(author_out >> output)) {
	wrong_answer("Unexpected token in output\n");
    }
    if (strcmp(output,"IMPOSSIBLE")) {
	bool target[K][L];
        for (int i = 0; i < K; ++i) {
           for(int j = 0; j < L; ++j) {
               char line;
               judge_in >> line;
               target[i][j] = (line == 'B');
           }
        }
	char short_ans;
	for (int i = 0; i < K; ++i) {
           for (int j = 0; j < L; ++j) {
              if (i != 0 || j != 0) {
                 if (!(author_out >> short_ans)) {
                    wrong_answer("Unexpected token in output\n");
		 }
              } else {
                 short_ans = output[0];
              }
              if (short_ans == 'P') {
                 target[i][j] = !target[i][j];
                 if (j > 0) {target[i][j-1] = !target[i][j-1];}
                 if (j < L-1) {target[i][j+1] = !target[i][j+1];}
                 if (i > 0) {target[i-1][j] = !target[i-1][j];}
                 if (i < K-1) {target[i+1][j] = !target[i+1][j];}
              } else if (short_ans != 'A') {
	         wrong_answer("Unexpected token in output\n");
              }
           }
        }
        
	for (int i = 0; i < K; ++i) {
           for (int j = 0; j < L; ++j) {
              if (target[i][j]) {
                 wrong_answer("Team drawing is incorrect\n");
              }
           }
        }
    } else if (strcmp(answer,"IMPOSSIBLE")) {
        wrong_answer("Team incorrectly states that the drawing cannot be displayed\n");
    }
    accept();
}
