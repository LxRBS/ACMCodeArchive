#include <iostream>
#include <string>
#include <sstream>
#include <regex>


using namespace std;

int main() {
	string input;
	getline(cin, input);
	
	stringstream ss(input);

	string encoded = "";

	regex e ("(u|m)+");

	while(ss) {
		string word;
		ss >> word;
		word.erase (remove_if (word.begin(), word.end(),::ispunct), word.end ());	
		if (regex_match(word, e)) {
			replace(word.begin(), word.end(), 'u', '1');
			replace(word.begin(), word.end(), 'm', '0');
			encoded += word;
		}	
	}


	for (int i = 0; i < encoded.length(); i += 7) {
		cout << char(stoi(encoded.substr(i, 7), nullptr, 2));
	}
    cout << endl;

	
	return 0;
}
