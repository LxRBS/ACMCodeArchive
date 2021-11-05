#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
int n;
double p, s, v, a = 1E-9, b, c, d = 1E10, w;

double eval(double c) {
	return (n*pow(log(n)/log(2), c*sqrt(2)) / (p*1E9)) + (s*(1.+1./c)/v);
}

int main() {
	cin >> n >> p >> s >> v;
	for (int i = 0; i < 100; i++) {
		w = d - a;
		b = a + w/3.;
		c = a + w*2./3.;
		if (eval(b) > eval(c)) a = b;
		else d = c;
	}
	cout << setprecision(15) << eval((a + d) / 2) << " " << (a + d) / 2. << endl;
	return 0;
}
