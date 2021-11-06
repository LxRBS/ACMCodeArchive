#include <bits/stdc++.h>
#include "validate.h"

using ll = long long;
using namespace std;

pair<ll, std::string> extractJudgeinput(){
	ll n, e, b;
	judge_in >> n >> e >> b;
	std::string pattern(n, '?');
	for(ll i = 0; i < b; i++){
		ll t;
		judge_in >> t;
		pattern[t-1] = '0';
	}

	return {e, pattern};
}

void sanitize_teamAnswer(std::string &teamAnswer, std::string &startPattern) {
	if(teamAnswer.size() != startPattern.size()){
		wrong_answer("Wrong answer, expected answer length of %d, but was %d\n", startPattern.size(), teamAnswer.size());
	}

	for(unsigned int i = 0; i < teamAnswer.size(); i++){
		if(teamAnswer[i] != '0' && teamAnswer[i] != '1'){
			wrong_answer("Wrong answer, answer of team contains the character %c\n", teamAnswer[i]);
		}
		if(startPattern[i] == '0' && teamAnswer[i] != '0'){
			wrong_answer("Wrong answer, expected a fixed zero at position %d, but is a %c\n", i, teamAnswer[i]);
		}
	}
}

void correctEntropy(std::string &teamAnswer, ll expectedEntropy) {
	int constructedEntropy = 0;
	for(unsigned int i = 0; i < teamAnswer.size()-1; i++){
		constructedEntropy += abs(teamAnswer[i+1] - teamAnswer[i]);
	}
	if(constructedEntropy != expectedEntropy){
		wrong_answer("Wrong answer, expected entropy %d, but was %d\n", expectedEntropy, constructedEntropy);
	}
}

int main(int argc, char **argv) {
	init_io(argc,argv);

	ll expected_entropy;
	string start_pattern;
	tie(expected_entropy, start_pattern) = extractJudgeinput();

	std::string teamAnswer;
	if(author_out >> teamAnswer){
		sanitize_teamAnswer(teamAnswer, start_pattern);
		correctEntropy(teamAnswer, expected_entropy);

		if(author_out >> teamAnswer) {
			wrong_answer("Wrong answer, additional output %s after correct answer\n", teamAnswer.c_str());
		} else {
			accept();
		}

	} else {
      wrong_answer("Wrong answer, team produced no output\n");
	}


	assert(false);
	return 43;
}
