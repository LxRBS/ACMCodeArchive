#include <cstdio>

int N;
long long L;
long long d[14][14];
int p[15];

int main() {
  scanf ("%d %lld", &N, &L);
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      scanf ("%lld", &d[i][j]);
  bool possible = false;
  for (int i=0; i<N; i++) p[i]=i;
  p[N]=0;
  long long D=0;
  for (int i=0; i<N; i++) 
    D += d[p[i]][p[i+1]];
  // Loop over permutations.
  while (1) {
    if (D == L) {
      possible = true;
      break;
    }
    int j=-1;
    for (int i=N-2; i>=1; i--) {
      if (p[i] < p[i+1]) {
	j = i;
	break;
      }
    }
    if (j==-1) {
      // Last permutation.
      break;
    }
    for (int i=j-1; i<N; i++)
      D -= d[p[i]][p[i+1]];
    int k = 0;
    for (int i=N-1; i>=0; i--) {
      if (p[i] > p[j]) {
	k = i;
	break;
      }
    }
    p[j] ^= p[k] ^= p[j] ^= p[k];  // Swap.
    for (int i=0; j+1+i < N-1-i; i++)
      p[j+1+i] ^= p[N-1-i] ^= p[j+1+i] ^= p[N-1-i];  // Swap.
    for (int i=j-1; i<N; i++)
      D += d[p[i]][p[i+1]];

    // verify
    long long correct = 0;
    for (int i=0; i<N; i++)
      correct += d[p[i]][p[i+1]];
    if (D != correct) {
      printf ("error %lld != %lld\n", D, correct);
    }
  }
  printf ("%s\n", (possible ? "possible" : "impossible"));
  return 0;
}
