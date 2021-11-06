import ru.ifmo.testlib.*;
import java.lang.*;
import java.math.BigInteger;

import ru.ifmo.testlib.Outcome.Type;

import static ru.ifmo.testlib.CheckerFramework.runChecker;

public final class Check implements Checker {

    public static final int MAX_K = 1000;

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int tests = inf.nextInt();
        for (int i = 1; i <= tests; i++) {
            try {
                String pass = inf.nextToken();
                boolean ja = parseAnswer(pass, ans);
                boolean pa = parseAnswer(pass, ouf);
                if (ja == pa) {
                    continue;
                }
                if (!ja) {
                    throw new Outcome(Type.FAIL, "Participant found answer while jury didn't");
                }
                throw new Outcome(Type.WA, "Participant didn't found answer while jury did");
            } catch (Outcome outcome) {
                return new Outcome(outcome.getType(), outcome.getComment() + " [test " + i + "]");
            }
        }
        return new Outcome(Type.OK, tests + " tests passed");
    }

    private boolean parseAnswer(String pass, InStream ouf) {
        String yes_no = ouf.nextToken().toUpperCase();
        if (yes_no.equals("NO")) {
            return false;
        }
        if (!yes_no.equals("YES")) {
            throw ouf.quit(Type.WA, "YES or NO expected");
        }
        int k = ouf.nextInt();
        if (k < 0 || k > MAX_K) {
            throw ouf.quit(Type.WA, "Expected 1 to " + MAX_K + " parts");
        }
        int[] codes = new int[pass.length()];
        for (int i = 1; i <= k; i++) {
            String part = ouf.nextToken();
            if (part.length() != pass.length()) {
                throw ouf.quit(Type.WA, "Part " + i + " should have length " + pass.length());
            }
            for (int j = 0; j < part.length(); j++) {
                codes[j] ^= part.charAt(j);
            }
            try {
                checkEquality(part);
            } catch (Outcome outcome) {
                throw ouf.quit(outcome.getType(), "Part " + i + ": " + outcome.getComment());
            }
        }
        for (int i = 0; i < codes.length; i++) {
            if (codes[i] != pass.charAt(i)) {
                throw ouf.quit(Type.WA, "Xor differs at position " + (i + 1));
            }
        }
        return true;
    }

    private void checkEquality(String equality) {
        int index = equality.indexOf('=');
        if (index == -1) {
            throw new Outcome(Type.WA, "No equality sign in equality");
        }
        BigInteger left = calcFullExpr(new Tokenizer(equality.substring(0, index)));
        BigInteger right = calcFullExpr(new Tokenizer(equality.substring(index + 1)));
        if (!left.equals(right)) {
            throw new Outcome(Type.WA, "Left and right equality sides are not equal: " + left + "!=" + right);
        }
    }

    private BigInteger calcFullExpr(Tokenizer tokenizer) {
        BigInteger res = calcExpr(tokenizer);
        if (!tokenizer.curToken.isEmpty()) {
            throw new Outcome(Type.WA, "Unexpected '" + tokenizer.curToken + "' expected end of expression");
        }
        return res;
    }

    static class Tokenizer {
        String curToken;
        String expr;
        int position;
        Tokenizer(String expr) {
            this.expr = expr;
            this.position = 0;
            nextToken();
        }

        void nextToken() {
            if (position == expr.length()) {
                curToken = "";
                return;
            }
            if (Character.isDigit(expr.charAt(position))) {
                int right = position;
                while (right < expr.length() && Character.isDigit(expr.charAt(right))) {
                    right++;
                }
                curToken = expr.substring(position, right);
                position = right;
            } else {
                curToken = expr.substring(position, position + 1);
                position++;
            }
        }
    }

    private BigInteger calcExpr(Tokenizer expr) {
        BigInteger res = calcTerm(expr);
        while (expr.curToken.equals("+") || expr.curToken.equals("-")) {
            boolean is_add = expr.curToken.equals("+");
            expr.nextToken();
            BigInteger next = calcTerm(expr);
            res = is_add ? res.add(next) : res.subtract(next);
        }
        return res;
    }

    private BigInteger calcTerm(Tokenizer expr) {
        BigInteger res = calcMultiplier(expr);
        while (expr.curToken.equals("*")) {
            expr.nextToken();
            BigInteger next = calcMultiplier(expr);
            res = res.multiply(next);
        }
        return res;
    }

    private BigInteger calcMultiplier(Tokenizer expr) {
        String expected = null;
        switch (expr.curToken) {
            case "(":
                expected = ")";
                break;
            case "[":
                expected = "]";
                break;
            case "{":
                expected = "}";
                break;
        }
        if (expected != null) {
            expr.nextToken();
            BigInteger res = calcExpr(expr);
            if (!expr.curToken.equals(expected)) {
                throw new Outcome(Type.WA, "Unexpected '" + expr.curToken + "' expected '" + expected + "'");
            }
            expr.nextToken();
            return res;
        }
        BigInteger res;
        try {
            for (int i = 0; i < expr.curToken.length(); i++) {
                if (!Character.isDigit(expr.curToken.charAt(i))) {
                    throw new NumberFormatException();
                }
            }
            if (expr.curToken.length() > 1 && expr.curToken.charAt(0) == '0') {
                throw new NumberFormatException();
            }
            res = new BigInteger(expr.curToken);
            expr.nextToken();
        } catch (NumberFormatException exception) {
            throw new Outcome(Type.WA, "Unexpected '" + expr.curToken + "' expected integer or open bracket");
        }
        return res;
    }

    public static void main(String[] args) {
        runChecker(Check.class, args);
    }
}