import java.io.*;
import java.util.*;

public class BirthdayParadox2Arknave {
    static int MAXS = 365 * 100 + 5;
    static int MAX_FREQ = 101;

    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] collisions = new int[n];
        int[] freqs = new int[MAX_FREQ];
        int s = 0;
        for (int i = 0; i < n; i++) {
            collisions[i] = scan.nextInt();
            s += collisions[i];
            freqs[collisions[i]]++;
        }

        // log(n!) = log(n) + log(n - 1) + ...
        double[] logFactorial = new double[MAXS];
        for (int i = 2; i < MAXS; i++) {
            logFactorial[i] = logFactorial[i - 1] + Math.log10(i);
        }

        // There are 365^s possible outcomes.
        double outcomes = s * Math.log10(365.0);

        // 365 C n ways to choose the dates
        // 365! / n! / (365 - n)!
        double pickDates = logFactorial[365] - logFactorial[n] - logFactorial[365 - n];

        // Assign people to buckets
        // How many permutations are there of the form AABBBCC?
        double assignPeople = logFactorial[s];
        for (int i = 0; i < n; i++) {
            assignPeople -= logFactorial[collisions[i]];
        }

        // Second pass, how many ways can we assign dates to buckets?
        // AABBBCC is equivalent to CCBBBAA
        double assignDates = logFactorial[n];
        for (int i = 0; i < MAX_FREQ; i++) {
            assignDates -= logFactorial[freqs[i]];
        }

        // log(pickDates * assignPeople * assignDates / outcomes) =
        double answer = pickDates + assignPeople + assignDates - outcomes;
        System.out.printf("%.9f%n", answer);
    }
}
