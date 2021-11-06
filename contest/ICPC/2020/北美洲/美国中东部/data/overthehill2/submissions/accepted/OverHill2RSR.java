import java.util.*;

public class OverHill2RSR {
  public static int mult[][];
  public static int div[][];
  public static int p;
  public static int n,z2;
  public static String plain,cipher;
  public static int[] pl, ci;
  public static String alph;
  public static int[][] answer;

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    n = in.nextInt();
    in.nextLine();
    plain = in.nextLine();
    cipher = in.nextLine();
    int z = plain.length();
    int pad = 0;
    if (z%n != 0) pad = n-z%n;
    for (int i = 0; i < pad; i++) {
      plain = plain+" ";
      cipher = cipher +" ";
    }
    z2 = z+pad; // length of inputs expanded to a multiple of n
    int n2 = z2/n; // Number of equations in each system to be solved

    // Check for inconsistencies in input--same inputs, different outputs.
    // Check for "easy" no solution: map zero to non-zero:
    HashMap<String,String> enc = new HashMap<String,String>();
    boolean allzero = true; // see if entire input is all zeros
    for (int i = 0; i < n2; i++) { // look at each column vector
      String s1 = plain.substring(n*i,n*i+n); // s1 is one input column vector
      String s2 = cipher.substring(n*i,n*i+n); // corresponding output column
      String map = enc.get(s1); // have we already found an encoding for s1?
      if (map != null) {
        if (!s2.equals(map)) { // do encodings of duplicate inputs agree?
          System.out.println("No solution");
          System.exit(0);
        }
      } else {
        enc.put(s1,s2); // remember how s1 is encoded for later comparisons
      }
      if ("AAAAAAAAAA".contains(s1) && !"AAAAAAAAAA".contains(s2)) {
        // can't map a zero vector to a nonzero vector
        System.out.println("No solution");
        System.exit(0);
      }
      if (!"AAAAAAAAAA".contains(s1) || !"AAAAAAAAAA".contains(s2))
        allzero = false;
    }

    if (allzero) {
      System.out.println("Too many solutions");
      System.exit(0);
    }



    alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    pl = new int[z2]; // map plaintext letters to integers
    ci = new int[z2]; // map ciphertext letters to integers
    for (int i = 0; i < z2; i++) {
       pl[i] = alph.indexOf(plain.charAt(i));
       ci[i] = alph.indexOf(cipher.charAt(i));
    }

    // Set up multiplication and division, mod p (= 37)
    p = 37;
    mult = new int[p][p];
    div = new int[p][p];
    for (int i = 0; i < p; i++) {
      for (int j = 0; j < p; j++) {
        int k = (i*j)%p;
        mult[i][j] = k;
        div[k][j] = i;
      }
    }

    answer = new int[n][n];
    // Need to solve n systems of equations. For the i-th system,
    // find X = {x(i,0), x(i,1), ..., x(i,n-1)}, such that X*A = B, where:
    //     A = {pl[i],pl[i+n],...,pl[i+n2-n),..., pl[i+n2-1]}
    // and B = {ci[i],ci[i+n],...,ci[i+n2-n],..., ci[i+n2-1]}.
    int code = 1; // assume there is a unique solution

    for (int i = 0; i < n; i++) { // Solve for row i of matrix
      code = solve(i); // if undertermined on any row, can't be unique elsewhere
      if (code == 0) {
        System.out.println("No solution");
        System.exit(0);
      }
    }

    if (code == 2) {
      System.out.println("Too many solutions");
      System.exit(0);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         if (j > 0) System.out.print(" ");
         System.out.print(answer[i][j]);
      }
      System.out.println();
    }
  }


  public static int solve(int row) {
    int n2 = z2/n; // n2 = number of equations in system; could be <, ==, or > n
    int[][] mat = new int[n2][n+1];
    for (int i = 0; i < n2; i++) {
      for (int j = 0; j < n; j++) {
        mat[i][j] = pl[n*i+j];
      }
      mat[i][n] = ci[row+n*i];
    }

    boolean overflag = false;
    for (int r = 0; r < Math.min(n,n2); r++) {
      // search for non-zero entry in column r
      int s = r;
      while (s < n2 && mat[s][r] == 0) s++;
       if (s == n2) {
         overflag = true;
         // could still be inconsistent, so just move on to next column
         continue;
       }
       int[] temp = mat[s];
       mat[s] = mat[r];
       mat[r] = temp;

      // divide each element in row r by mat[r][r]
      int d = mat[r][r];
      for (int c = r; c <= n; c++) {
         mat[r][c] = div[mat[r][c]][d];
      }

      // subtract mat[r2][r]*mat[r][c] from mat[r2][c]
      for (int r2 = r+1; r2 < n2; r2++) {
         if (r2 == r) continue;
         int m = mat[r2][r];
         for (int c = r; c <= n; c++) {
            mat[r2][c] = (mat[r2][c] - mult[m][mat[r][c]]+p)%p;
         }
      }
    }
    // if system overdetermined, look for inconsistencies:
    int l = n2-1;
    while (l >= 0 && mat[l][n-1] == 0) {
      if (mat[l][n] != 0) {
        return 0;// code for inconsistent
      }
      l--;
    }
    // Not inconsistent; see if underdetermined:
    if (n2 < n || overflag) return 2;

    // See if rows are all non-zero:
    if (n2 >= n && mat[n-1][n-1]==0) return 2; // I think this is not needed
    // Back solve:
    for (int i = Math.min(n-1,n2-1); i >= 0; i--) {
      int ans = mat[i][n];
      for (int j = i+1; j < n; j++) {
        ans = (p+ans-mult[mat[i][j]][answer[row][j]])%p;
      }
      answer[row][i] = ans;
    }
    return 1;
  }
}
