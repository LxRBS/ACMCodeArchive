import java.util.*;
import java.io.*;

public class RestroomRSR {
  public static int s,n; // number of stalls; number of customers
  public static ArrayList<Integer> yes,no; // need/don't need t.p.

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(in.readLine());
    s = Integer.parseInt(st.nextToken());
    n = Integer.parseInt(st.nextToken());
    yes = new ArrayList<Integer>();
    no = new ArrayList<Integer>();
    int max = 0; // largest deadline
    for (int i = 0; i < n; i++) {
      st = new StringTokenizer(in.readLine());
      int d = Integer.parseInt(st.nextToken());
      String a = st.nextToken();
      if (a.equals("y")) yes.add(d);
      else no.add(d);
      max = Math.max(max,d);
    }
    Collections.sort(yes);
    Collections.sort(no);

    // List of times that t.p. stalls are used by "yes" people:
    ArrayList<Integer> stall = new ArrayList<Integer>();

    // Arrange the "yes" people:
    int next = max;
    for (int i = yes.size()-1; i >= 0;  i--) {
      if (next < 1) { // can't meet deadline for a "yes" person
        System.out.println("No");
        System.exit(0);
      }
      int d = yes.get(i);
      if (d < next) {
        next = d;
      }
      stall.add(next);
      next--;
    }

    // Now process the "no" list.

    next = 1; // next available time slot
    int avail = s; // number of stalls available at a given time
    int j = stall.size()-1; // points to list of times when t.p. stall is used
    if (j >= 0 && next == stall.get(j)) {
      avail--; // t.p. stall is in use
      j--;
    }

    for (int i: no) {
      if (avail == 0) {
        next++;
        avail = s;
        if (j>= 0 && next == stall.get(j)) {
          avail--;
          j--;
        }
      }
      if (i >= next) avail--;
      else {
        System.out.println("No");
        System.exit(0);
      }
    }
    System.out.println("Yes");
  }
}
