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
	long long xNum = llround(xDesired * den);
	long long yNum = llround(3 * yDesired * den);
	map<long long, long long> states0;
	states0[0] = 0;
	vector<map<long long, long long>> states;
	states.push_back(states0);
	for (int i = 1; i <= n; ++i) {
		map<long long, long long> newStates;
		for (int j = 0; j < i; j++) {
			long long addMass = 2 * j + 1, addXMass = (j + 1) * (2 * j + 1), addYMass = 3 * j + 1, len = 2 * j + 2, addBit = 1LL << (2 * j + 1);
			for (const auto& [stateLeft, sequenceLeft] : states[j]) {
				long long massLeft = stateLeft << 48 >> 48;
				long long xMassLeft = stateLeft << 24 >> 40;
				long long yMassLeft = stateLeft >> 40;
				for (const auto& [stateRight, sequenceRight] : states[i - j - 1]) {
					long long massRight = stateRight << 48 >> 48;
					long long xMassRight = stateRight << 24 >> 40;
					long long yMassRight = stateRight >> 40;
					long long mass = addMass + massLeft + massRight;
					long long yMass = addYMass + yMassLeft + massLeft * 3 + yMassRight;
					long long xMass = addXMass + xMassLeft + massLeft + xMassRight + massRight * len;
					if (i < n) {
						newStates[(yMass << 40) | (xMass << 16) | mass] = (sequenceLeft << 1) | (sequenceRight << len) | addBit;
						continue;
					}
					if ((abs(xMass * den - xNum * mass) < mass << 6) && (abs(yMass * den - yNum * mass) < mass << 6)) {
						long long sequence = (sequenceLeft << 1) | (sequenceRight << len) | addBit;
						for (int k = 0; k < 2 * n; k++) {
							cout << (((sequence >> k) & 1) ? ")" : "(");
						}
						cout << endl;
						return 0;
					}
				}
			}
		}
		states.push_back(newStates);
	}
}
