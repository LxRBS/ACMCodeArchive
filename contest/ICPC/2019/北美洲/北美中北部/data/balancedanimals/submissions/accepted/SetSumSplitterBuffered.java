import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.*;
/**
 * class SetSumSplitter
 *
 * is the solution to Problem M at the 2019 North American Qualifiers for the
 * ICPC.
 *
 * Expected input (stdin):
 *
 * 1. The first line of input contains an integer $n$ indicating the number of
 *    cases that follow, where 1 <= n <= 100.
 * 2. Each of the following $n$ lines has one case which consists of m positive
 *    integers, where 1 <= m <= 100.  No integer will be larger than 65,535.
 *
 * Expected output (stdout):
 * 
 * For each case, the program will output a single integer value that is the
 * smallest integer, s, such that the sum of all the numbers in the input
 * set that are greater than s is equal to sum of all the numbers in the input
 * that are less than s.
 */
public class SetSumSplitterBuffered {

    public static final void main(String[] args) throws Exception {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));

        int m = Integer.parseInt(stdin.readLine());
        int[] set = new int[m];
        for (int j = 0; j < m; ++j)
        {
            set[j] = Integer.parseInt(stdin.readLine());
        }

        //Sorting the array makes the problem a lot easier
        Arrays.sort(set);

        //Find the balance point of the sorted list
        long leftSum = 0;
        long rightSum = 0;
        int leftIndex = 0;
        int rightIndex = set.length - 1;
        int answer = -1; //flag
        while(leftIndex <= rightIndex)
        {
            //Special case:  if the sums are equal it's possible that all
            //the remaining numbers belong in neither side of the split
            if (leftSum == rightSum && set[leftIndex] == set[rightIndex]) {
                answer = set[leftIndex];
                break;
            }//if

            //Increase the smaller sum
            if (leftSum <= rightSum) {
                leftSum += set[leftIndex];
                leftIndex++;
            } else {
                rightSum += set[rightIndex];
                rightIndex--;
            }
        }//while

        //If there is no answer yet, then the answer is the smallest int
        //that's greater that the last number added to the leftSum
        if (answer == -1) {
            answer = set[leftIndex - 1] + 1;
        }

        //Ta da!
        System.out.println(answer);

        stdin.close();

    }//main
}//class SetSumSplitter
