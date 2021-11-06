import java.io.PrintWriter;
import java.util.*;

public class solution_sm_wa {

    private HashMap<Integer, Deque<Cas>> es;

    class Cas {
        int a, b, s, id;

        public Cas(int id, int a, int b, int s) {
            this.a = a;
            this.b = b;
            this.s = s;
            this.id = id;
        }
    }

    void solve() {
        int n = in.nextInt();
        int c = in.nextInt();
        es = new HashMap<>();
        ArrayList<Cas> failedC = new ArrayList<>();
        ArrayList<Cas> failedNotC = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            Cas cas = new Cas(i + 1, in.nextInt(), in.nextInt(), in.nextInt());
            if (cas.s == 1) {
                if (!es.containsKey(cas.a)) {
                    es.put(cas.a, new ArrayDeque<>());
                }
                es.get(cas.a).addLast(cas);
            } else {
                if (cas.a == c) {
                    failedC.add(cas);
                } else {
                    failedNotC.add(cas);
                }
            }
        }
        order = new ArrayList<>();
        dfs(c);
        Collections.reverse(order);
        ArrayList<Integer> answer = new ArrayList<>();
        for (Cas f : failedNotC) {
            answer.add(f.id);
        }
        for (Cas cas : order) {
            if (cas.a != c) {
                for (Cas f : failedC) {
                    answer.add(f.id);
                }
                failedC.clear();
            }
            answer.add(cas.id);
        }
        if (answer.size() == n) {
            out.println("Yes");
            for (int i : answer) {
                out.print(i + " ");
            }
            out.println();
        } else {
            out.println("No");
        }
    }

    ArrayList<Cas> order;

    void dfs(int v) {
        if (!es.containsKey(v) || es.get(v).isEmpty()) {
            return;
        }
        Cas cas = es.get(v).removeLast();
        dfs(cas.b);
        order.add(cas);
    }

    Scanner in;
    PrintWriter out;

    void run() {
        in = new Scanner(System.in);
        out = new PrintWriter(System.out);
        solve();
        out.close();
    }

    public static void main(String[] args) {
        new solution_sm_wa().run();
    }
}
