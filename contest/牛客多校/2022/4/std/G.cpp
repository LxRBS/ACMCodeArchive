#include <algorithm>
#include <cstdio>

const int MAXN = 100000;
long long P[4][MAXN], tmpP[4][MAXN];
int tot[4], tmpTot[4];

/*
 *      1
 *   -------
 * 0 |      | 2
 *   --------
 *      3
 */
int main() {
  int totCases = 0;
  scanf("%d", &totCases);
  for (int cas = 0; cas < totCases; ++cas) {
    int N;
    long long A, B;
    scanf("%d%lld%lld", &N, &A, &B);
    for (int i = 0; i < 4; ++i) {
      tot[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
      long long x, y;
      scanf("%lld%lld", &x, &y);
      if (x == 0) {
        P[0][tot[0]++] = y;
      } else if (x == A) {
        P[2][tot[2]++] = y;
      } else if (y == 0) {
        P[3][tot[3]++] = x;
      } else if (y == B) {
        P[1][tot[1]++] = x;
      }
    }
    for (int i = 0; i < 4; ++i) {
      std::sort(P[i], P[i] + tot[i]);
    }

    long long answer = 0;
    
    for (int rotation = 0; rotation < 4; ++rotation) {
      long long gap1 = 0, gap1Mid = 0;
      if (tot[1] == 0) {
        gap1 = A;
      } else {
        gap1 = std::max(P[1][0], A - P[1][tot[1] - 1]);
        for (int i = 1; i < tot[1]; ++i) {
          gap1 = std::max(gap1, P[1][i] - P[1][i - 1]);
          gap1Mid = std::max(gap1Mid, P[1][i] - P[1][i - 1]);
        }
      }
      long long gap3 = 0, gap3Mid = 0;
      if (tot[3] == 0) {
        gap3 = A;
      } else {
        gap3 = std::max(P[3][0], A - P[3][tot[3] - 1]);
        for (int i = 1; i < tot[3]; ++i) {
          gap3 = std::max(gap3, P[3][i] - P[3][i - 1]);
          gap3Mid = std::max(gap3Mid, P[3][i] - P[3][i - 1]);
        }
      }
      // First cut
      for (int i = 0; i < tot[0]; ++i) {
        // Up
        long long b0 = P[0][i];
        long long b1 = (i + 1 == tot[0]) ? B : P[0][i + 1];

        long long b2 = B;
        if (tot[2] > 0 && P[2][tot[2] - 1] > b0) {
          int L = 0;
          int R = tot[2] - 1;
          while (L < R) {
            int mid = (L + R) / 2;
            if (P[2][mid] < b0) {
              L = mid + 1;
            } else {
              R = mid;
            }
          }
          b2 = P[2][L];
        }

        // printf("b0 = %lld, b1 = %lld, b2 = %lld\n", b0, b1, b2);
        if (b1 == B && b2 == B) {
          answer = std::max(answer, gap1 * (B - b0));
        } else if (b1 < b2) {
          answer = std::max(answer, A * (b1 - b0));
          if (tot[1] > 0) {
            if (b2 < B) {
              answer = std::max(answer, (A - P[1][0]) * (b2 - b0));
            } else {
              answer = std::max(answer, (A - P[1][tot[1] - 1]) * (b2 - b0));
            }
            // if (tot[1] == 1 || b2 < B) {
            //   answer = std::max(answer, (A - P[1][0]) * (b2 - b0));
            // }
          }
        } else {
          answer = std::max(answer, A * (b2 - b0));
          if (tot[1] > 0) {
            if (b1 < B) {
              answer = std::max(answer, P[1][tot[1] - 1] * (b1 - b0));
            } else {
              answer = std::max(answer, P[1][0] * (b1 - b0));
            }
          }
        }
        if (tot[1] > 1) {
          answer = std::max(answer, gap1Mid * (B - b0));
        }
          // printf("answer Up = %lld\n", answer);

        // Other direction
        b1 = (i == 0) ? 0 : P[0][i - 1];
        b2 = 0;
        if (tot[2] > 0 && P[2][0] < b0) {
          int L = 0;
          int R = tot[2] - 1;
          while (L < R) {
            int mid = (L + R + 1) / 2;
            if (P[2][mid] < b0) {
              L = mid;
            } else {
              R = mid - 1;
            }
          }
          b2 = P[2][L];
        }

        // printf("A = %lld, gap3Mid = %lld, b0 = %lld, b1 = %lld, b2 = %lld\n", A, gap3Mid, b0, b1, b2);
        if (b1 == 0 && b2 == 0) {
          answer = std::max(answer, gap3 * b0);
        } else if (b1 > b2) {
          answer = std::max(answer, A * (b0 - b1));
          if (tot[3] > 0) {
            if (b2 > 0) {
              answer = std::max(answer, (A - P[3][0]) * (b0 - b2));
            } else {
              answer = std::max(answer, (A - P[3][tot[3] - 1]) * (b0 - b2));
            }
          }
        } else {
          answer = std::max(answer, A * (b0 - b2));
          if (tot[3] > 0) {
            if (b1 > 0) {
              answer = std::max(answer, P[3][tot[3] - 1] * (b0 - b1));
            } else {
              answer = std::max(answer, P[3][0] * (b0 - b1));
            }
          }
        }
        if (tot[3] > 1) {
          answer = std::max(answer, gap3Mid * b0);
        }
          // printf("answer Down = %lld\n", answer);
      }

      // Rotate
      // printf("Before:\n");
      // for (int i = 0; i < 4; ++i) {
      //   printf("i = %d: ", i);
      //   for (int j = 0; j < tot[i]; ++j) {
      //     printf("%lld ", P[i][j]);
      //   }
      //   printf("\n");
      // }
      tmpTot[0] = tot[1];
      for (int i = 0; i < tot[1]; ++i) {
        tmpP[0][i] = P[1][i];
      }
      tmpTot[1] = tot[2];
      for (int i = 0; i < tot[2]; ++i) {
        tmpP[1][i] = B - P[2][i];
      }
      tmpTot[2] = tot[3];
      for (int i = 0; i < tot[3]; ++i) {
        tmpP[2][i] = P[3][i];
      }
      tmpTot[3] = tot[0];
      for (int i = 0; i < tot[0]; ++i) {
        tmpP[3][i] = B - P[0][i];
      }
      for (int i = 0; i < 4; ++i) {
        tot[i] = tmpTot[i];
        for (int j = 0; j < tmpTot[i]; ++j) {
          P[i][j] = tmpP[i][j];
        }
        std::sort(P[i], P[i] + tot[i]);
      }
      std::swap(A, B);
      // for (int i = 0; i < 4; ++i) {
      //   printf("i = %d: ", i);
      //   for (int j = 0; j < tot[i]; ++j) {
      //     printf("%lld ", P[i][j]);
      //   }
      //   printf("\n");
      // }
    }

    printf("%lld\n", answer);
  }
  return 0;
}