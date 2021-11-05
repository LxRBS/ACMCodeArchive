#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<long long> vi;

#define MAXN 14
#define MAXL 1000000000000000LL

long long d[MAXN][MAXN];

/**** Use Per's solution to verify ****/
vi genpartial(int s, int M, int t, long long L) {
	vi W, R;
	W.push_back(s);
	for (int i = 0; (1<<i) <= M; ++i)
		if (M & (1<<i))	W.push_back(i);
	W.push_back(t);
	do {
		long long l = 0;
		int p = s;
		for (auto v: W)	{
			l += d[p][v];
			p = v;
			if (l > L) break;
		}
		R.push_back(l);
	} while (next_permutation(W.begin()+1, W.end()-1));
	sort(R.begin(), R.end());
	return R;
}

bool hastour(int N, long long L) {
	int all = (1<<(N-1))-1;
	for (int S = 1; S <= all; ++S) {
		int w = 0;
		for (int i = 0; i < N-1; ++i) if (S & (1<<i)) ++w;
		if (w == N/2)
			for (int mid = 0; mid < N-1; ++mid)
				if (S & (1<<mid)) {
					vi A = genpartial(N-1, S^(1<<mid), mid, L);
					vi B = genpartial(mid, S^all, N-1, L);
					int a = 0, b = B.size()-1;
					while (a < A.size() && b >= 0) {
						if (A[a]+B[b] == L) return true;
						if (A[a]+B[b] < L) ++a;
						else if (A[a]+B[b] > L) --b;
					}
				}
	}
	return false;
}


void writeCase(const char *casename, const char *answer, int N, long long L) {
	int i, j;
	char name[1000];
	FILE *out;

	fprintf(stderr, "writing case %s (N = %d, L = %lld, ans %s)\n", casename, N, L, answer);
	// Write input
	sprintf(name, "secret/%s.in", casename);
	out = fopen(name, "w");
	fprintf(out, "%d %lld\n", N, L);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(j > 0) fprintf(out, " ");
			fprintf(out, "%lld", d[i][j]);
		}
		fprintf(out, "\n");
	}
	fclose(out);

	// Write output
	sprintf(name, "secret/%s.ans", casename);
	out = fopen(name, "w");
	fprintf(out, "%s\n", answer);
	fclose(out);
}

void writeCase(const char *casename, int N, long long L) {
	writeCase(casename, hastour(N,L) ? "possible" : "impossible", N, L);
}

// Inclusive bounds
long long randInt(long long min, long long max) {
	return (long long)floor(((double) rand() / (double)RAND_MAX) * (max-min+1)) + min;
}

// Scramble the order
void scramble(int N) {
	int i, j, p1, p2;
	long long k;
	assert(N > 1); // otherwise infinite loop -- problem guarantees N >= 2
	// swap two positions 100 times
	for(i = 0; i < 100; i++) {
		p1 = randInt(0, N-1);
		do { p2 = randInt(0, N-1); } while (p1 == p2);
		for(j = 0; j < N; j++) {
			if(j == p1 || j == p2) continue;
			k = d[j][p1];
			d[j][p1] = d[p1][j] = d[j][p2];
			d[j][p2] = d[p2][j] = k;
		}
	}
}

void fillRandoms(long long min, long long max) {
	int i, j;
	for(i = 0; i < MAXN; i++)
		for(j = 0; j < i; j++)
			d[i][j] = d[j][i] = randInt(min, max);
}

void floyd(int n) {
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}

void setZeros() {
	int i;
	for(i = 0; i < MAXN; i++)
		d[i][i] = 0;
}

int main() {
	int i, n;
	long long j, k, sum;
	char name[100];

	// Set seed to constant
	srand(31337);

	// Smallest possible
	setZeros();
	d[0][1] = d[1][0] = 1;
	writeCase("15-small-possible", "possible", 2, 2);

	// Smallest impossible
	setZeros();
	d[0][1] = d[1][0] = 1;
	writeCase("16-small-impossible", "impossible", 2, 1);

	// Case where length works out exactly with int overflow
	fillRandoms(705032699, 1000000000);
	setZeros();
	d[0][1] = d[1][0] = 999999999;
	d[1][2] = d[2][1] = 999999999;
	d[2][3] = d[3][2] = 999999999;
	d[3][4] = d[4][3] = 999999999;
	d[4][5] = d[5][4] = 999999999;
	d[5][0] = d[0][5] = 294967301;
	scramble(6);
	writeCase("10-int-overflow", "impossible", 6, 1000000000);

	// Seconds case that works out with int oveflow
	fillRandoms(705032699, 1000000000);
	setZeros();
	for(i = 0; i < 12; i++)
		d[i][(i+1)%12] = d[(i+1)%12][i] = 799161216;
	scramble(12);
	writeCase("11-int-overflow2", "impossible", 12, 1000000000);

	// Big case with single solution
	sum = 0;
	fillRandoms(1 << 25, 1 << 26);
	setZeros();
	for(i = 0; i < MAXN; i++) {
		d[i][(i+1)%MAXN] = d[(i+1)%MAXN][i] = (1 << 25) + (1 << i);
		sum += (1 << 25) + (1 << i);
	}
	scramble(MAXN);
	writeCase("12-single-solution", "possible", MAXN, sum);

	// Big case without solution
	setZeros();
	for(i = 0; i < MAXN; i++) {
		for(j = 0; j < MAXN; j++) {
			if(i == j) continue;
			d[i][j] = (i < MAXN/2) == (j < MAXN/2) ? 1 : 2;
		}
	}
	scramble(MAXN);
	writeCase("13-big-no-solution", "impossible", MAXN, MAXN+1);

	// Second big case without solution
	setZeros();
	sum = 0;
	k = 0;
	for(i = 0; i < MAXN; i++) {
		for(j = 0; j < MAXN; j++) {
			if(i == j) continue;
			d[i][j] = d[j][i] = ++k;
		}
		sum += d[i][(i+1)%MAXN];
	}
	scramble(MAXN);
	writeCase("14-big-no-solution", "impossible", MAXN, sum+1);

	// Big case without solution, large distances
	long long d_lo = MAXL/(2*MAXN);
	fillRandoms(d_lo, 2*d_lo);
	sum = 0;
	k = 0;
	printf("%lld\n", d_lo);
	for(i = 0; i < MAXN; i++) {
		d[i][(i+1)%MAXN] = d[(i+1)%MAXN][i] = 2*d_lo - k++;
		sum += d[i][(i+1)%MAXN];
	}
	scramble(MAXN);
	writeCase("17-big-no-solution", "impossible", MAXN, sum+1);

	// Same as before but with a unique solution (whp)
	writeCase("18-big-single-solution", "possible", MAXN, sum);

	// Some big random cases with solution
	for(i = 19; i < 26; i++) {
		n = randInt(MAXN-3,MAXN);
		setZeros();
		fillRandoms(MAXL / (2 * n), MAXL / n);
		sum = 0;
		for(j = 0; j < n; j++)
			sum += d[j][(j+1)%n];
		scramble(n);
		sprintf(name, "%02d-big-random", i);
		writeCase(name, "possible", n, sum);
	}

	// Some more random cases
	for(i = 26; i <= 36; i++) {
		n = randInt(2,MAXN);
		setZeros();
		j = MAXL / (2*n);
		k = min(MAXL/n,j+100);
		fillRandoms(j,k);
		scramble(n);
		sprintf(name, "%02d-random", i);
		writeCase(name, n, randInt(j*n,k*n)); // Check if solvable, should be quite often
	}

	// Per's ideas for killing branch-and-bound
	setZeros();
	for(i = 0; i < MAXN; i++)
		for(j = i+1; j < MAXN; j++)
			d[i][j] = d[j][i] = randInt(1,2) * 2; // 2 or 4
	j = (MAXN*3) | 1;
	writeCase("03-kill-branchbound1", "impossible", MAXN, j);
	
	setZeros();
	k = MAXL/20; // MAXD
	for(i = 0; i < MAXN; i++)
		for(j = i+1; j < MAXN; j++)
			d[i][j] = d[j][i] = randInt(1,2) * k / 2 - randInt(0,k/2000)*2;
	j = (3*MAXN*k/4) | 1;
	floyd(MAXN);
	writeCase("04-kill-branchbound2", "impossible", MAXN, j);

	// More random uniques
	for(k = 5; k <= 9; k++) {
		sum = 0;
		j = randInt(1LL << 30, MAXL/MAXN);
		fillRandoms(j/2, j);
		setZeros();
		for(i = 0; i < MAXN; i++) {
			d[i][(i+1)%MAXN] = d[(i+1)%MAXN][i] = j/2 + (1 << i);
			sum += d[i][(i+1)%MAXN];
		}
		scramble(MAXN);
		sprintf(name, "%02d-random-unique", (int)k);
		writeCase(name, "possible", MAXN, sum);
	}

	setZeros();
	int P = 23053;
	k = P * (MAXL/P / (3*MAXN/2)); // MAXD
	for(i = 0; i < MAXN; i++)
		for(j = i+1; j < MAXN; j++) {
			long long dist = randInt(1,2) * k;
			long long noise = randInt(0,k/(200*P))*P;
			if (dist == k) dist += noise;
			else dist -= noise;
			d[i][j] = d[j][i] = dist;
		}
	j = (3*MAXN*k/2)/P*P + P/2;
	writeCase("01-kill-branchbound2-crt", "impossible", MAXN, j);

	setZeros();
	d_lo = MAXL/(3*MAXN/2);
	for(i = 0; i < MAXN; i++)
		for(j = i+1; j < MAXN; j++) {
			if (randInt(1,2) == 1)
				d[i][j] = d[j][i] = d_lo + randInt(0, d_lo/10);
			else 
				d[i][j] = d[j][i] = 2*d_lo - randInt(0, d_lo/10);
		}
	long long L;
	do {
		L = randInt(3*d_lo/2*MAXN - d_lo/10, 3*d_lo/2*MAXN + d_lo/10);
	} while (hastour(MAXN, L));
	writeCase("02-big-random-impossible", "impossible", MAXN, L);

	return 0;
}
