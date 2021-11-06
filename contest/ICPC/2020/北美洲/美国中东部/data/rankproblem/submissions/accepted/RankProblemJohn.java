import java.util.*;

public class RankProblemJohn
{
    public static final int MAXTEAMS = 100;
    public static final int MAXGAMES = 100;

    public static int[] order = new int[MAXTEAMS];

    public static int find(int val, int size)
    {
        for(int i=0; i<size; i++) {
            if (order[i] == val)
                return i;
        }
        return -1;      // should never happen
    }

    public static void main(String [] args)
    {
        Scanner in = new Scanner(System.in);
        int n, m;

        n = in.nextInt();
        m = in.nextInt();
        for(int i=0; i<n; i++) {
            order[i] = i+1;
        }
        String s1, s2;
        for(int i=0; i<m; i++) {
            s1 = in.next();
            s2 = in.next();
            int t1 = Integer.parseInt(s1.substring(1));
            int t2 = Integer.parseInt(s2.substring(1));
            int i1 = find(t1, n);
            int i2 = find(t2, n);
            if (i1 > i2) {
                for(int j=i2+1; j<=i1; j++)
                    order[j-1] = order[j];
                order[i1] = t2;
            }
        }
        System.out.print("T" + order[0]);
        for(int i=1; i<n; i++)
            System.out.print(" T" + order[i]);
        System.out.println();
    }
}
