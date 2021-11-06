#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
 
int main() {
	int n;
	cin >> n;
	n /= 2;
	long double xDesired, yDesired;
	cin >> xDesired >> yDesired;
	long long den = llround(1e10);
	long long err = llround(1e-8 * den);
	long long xNum = llround(xDesired * den);
	long long yNum = llround(3 * yDesired * den);
	map<long long, long long> states0;
	states0[0] = 0;
	vector<map<long long, long long>> states;
	states.push_back(states0);
	for (int i = 1; i <= n; ++i) {
		map<long long, long long> newStates;
		for (int j = 0; j < i; j++) {
		    for (const auto& [stateLeft, sequenceLeft] : states[j]) {
				long long massLeft = stateLeft & ((1 << 16) - 1);
				long long xMassLeft = (stateLeft >> 16) & ((1 << 24) - 1);
				long long yMassLeft = (stateLeft >> 40);
	    	    for (const auto& [stateRight, sequenceRight] : states[i - j - 1]) {
					long long massRight = stateRight & ((1 << 16) - 1);
					long long xMassRight = (stateRight >> 16) & ((1 << 24) - 1);
					long long yMassRight = (stateRight >> 40);
					long long mass = 2 * j + 1 + massLeft + massRight;
					long long yMass = 3 * j + 1 + yMassLeft + massLeft * 3 + yMassRight;
					long long xMass = (j + 1) * (2 * j + 1) + xMassLeft + massLeft + xMassRight + massRight * (2 * j + 2);
					if (i == n) {
						if ((abs(xMass * den - xNum * mass) < err * mass) && (abs(yMass * den - yNum * mass) < err * mass)) {
							long long sequence = (sequenceLeft << 1) | (sequenceRight << (2 * j + 2)) | (1LL << (2 * j + 1));
							for (int k = 0; k < 2 * n; k++) {
								cout << (((sequence >> k) & 1) ? ")" : "(");
							}
							cout << endl;
							return 0;
						}
						continue;
					}
					long long sequence = (sequenceLeft << 1) | (sequenceRight << (2 * j + 2)) | (1LL << (2 * j + 1));
					newStates[(yMass << 40) | (xMass << 16) | mass] = sequence;
				}
			}
		}
		states.push_back(newStates);
	}
}
