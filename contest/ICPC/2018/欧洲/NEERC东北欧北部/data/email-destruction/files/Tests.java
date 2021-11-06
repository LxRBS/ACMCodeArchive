import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

/**
 * Created by Meepo on 9/30/2018.
 */
public class Tests {
    public int tests = 1;
    Random rnd = new Random(239);

    int MAX_N = 100;
    int MAX_K = 100;
    int MAX_LEN = 10;

    public void writeTest(int n, List<String> letters) {
        try {
            PrintWriter out = new PrintWriter(String.format("%02d", tests++));

            Collections.shuffle(letters, rnd);
            
            n = Math.max(n, letters.size());
            
            out.println(n + " " + letters.size());
            letters.forEach(out::println);

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void samples() {
        writeTest(7, Arrays.asList("hello", "Re: Re: Re: hello", "Re: world"));
        writeTest(3, Arrays.asList("Re: Re: pleasehelp", "me"));
    }

    public class Chain {
        String subject;
        int cnt;

        public Chain(String subject, int cnt) {
            this.subject = subject;
            this.cnt = cnt;
        }
    }

    public String genRandomString() {
        String subject = "";
        int len = rnd.nextInt(MAX_LEN) + 1;
        for (int i = 0; i < len; i++) {
            subject += (char) ('a' + rnd.nextInt(26));
        }
        return subject;
    }

    public Chain[] genChains(int subjects, int m) {
        int[] splits = new int[subjects + 1];
        for (int i = 1; i <= subjects - 1; i++) {
            splits[i] = rnd.nextInt(m - subjects + 1);
        }
        Arrays.sort(splits, 1, subjects);
        for (int i = 1; i <= subjects - 1; i++) {
            splits[i] += i;
        }
        splits[subjects] = m;

        HashSet<String> subs = new HashSet<>();
        Chain[] chains = new Chain[subjects];
        for (int i = 0; i < chains.length; i++) {
            String subject = genRandomString();
            while (subs.contains(subject)) {
                subject = genRandomString();
            }
            chains[i] = new Chain(subject, splits[i + 1] - splits[i]);
            subs.add(subject);
        }
        return chains;
    }

    public void genTest(int subjects, int before, int prediction, int after) {
        Chain[] chains = genChains(subjects, before);

        List<String> subs = new ArrayList<>();
        for (int i = 0; i < chains.length; i++) {
            String subject = chains[i].subject;
            if (chains[i].cnt <= 0) {
                throw new AssertionError();
            }
            for (int j = 0; j < chains[i].cnt - 1; j++) {
                subs.add(subject);
                subject = "Re: " + subject;
            }
        }

        Collections.shuffle(subs, rnd);
        subs = subs.subList(0, after - subjects);
        for (int i = 0; i < chains.length; i++) {
            String subject = chains[i].subject;
            for (int j = 0; j < chains[i].cnt - 1; j++) {
                subject = "Re: " + subject;
            }
            subs.add(subject);
        }

        writeTest(prediction, subs);
    }

    public void gen() {
        samples();

        genTest(1, 1, 1, 1);
        genTest(1, 3, 2, 1);
        genTest(1, 2, 1, 2);
        genTest(2, 2, 2, 2);
        genTest(1, MAX_K, MAX_N, 1);
        genTest(1, MAX_K + 1, MAX_N, 1);
        genTest(1, 1, MAX_N, 1);
        genTest(1, MAX_K, MAX_N, MAX_K);
        genTest(1, 51, 52, 25);
        genTest(1, 52, 51, 25);

        genTest(rnd.nextInt(MAX_N) + 1, MAX_K, 1, MAX_K);

        for (int i = 0; i < 2; i++) {
            int subs = rnd.nextInt(MAX_N) + 1;
            genTest(subs, subs, MAX_N, subs);
        }

        genTest(MAX_N, MAX_N, MAX_N, MAX_N);
        genTest(MAX_N, MAX_N + 1, MAX_N, MAX_N);

        for (int i = 0; i < 20; i++) {
            int before = rnd.nextInt(MAX_N - 1) + 2;
            int after = rnd.nextInt(before) + 1;
            int subjects = rnd.nextInt(after) + 1;
            int prediction;
            if (rnd.nextBoolean()) { // "YES"
                prediction = rnd.nextBoolean() ? before : rnd.nextInt(MAX_N - before + 1) + before;
            } else { // "NO"
                prediction = rnd.nextBoolean() ? rnd.nextInt(before - after + 1) + after : rnd.nextInt(before - 1) + 1;
            }
            genTest(subjects, before, prediction, after);
        }

        // gen huge tests
        genTest(1, (500 - 10 + 4) / 4, MAX_N, 1);
        genTest(1, (500 - 10 + 4) / 4, MAX_K, MAX_K);
    }

    public static void main(String[] args) {
        new Tests().gen();
    }
}