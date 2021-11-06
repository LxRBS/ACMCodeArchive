import java.util.*;
import java.io.*;
import javax.script.*;

public class tobi_js implements Runnable {
	public static void main(String[] args) throws Exception {
		new Thread(null, new tobi_js(), "whatever", 1<<28).start();
	}
	public void run() {
		try {
		ScriptEngineManager manager = new ScriptEngineManager();
		ScriptEngine engine = manager.getEngineByName("js");
		Scanner sc = new Scanner(System.in);
		String[] programs = new String[] { sc.next(), sc.next() };
    String intSort = "function sortNumber(a, b) { return a - b; } ";
		String concat = "function concat(left, right) { return left.concat(right); } ";
		String sorted = "function sorted(ints) { return ints.sort(sortNumber); } ";
		String[] shuffle = new String[] {
			"function shuffle(ints) { return ints.sort(sortNumber); } ",
			"function shuffle(ints) { return ints.sort(sortNumber).reverse(); } " 
		};

		String[] evals = new String[4];
		for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
			evals[i*2 + j] = engine.eval(intSort + concat + sorted + shuffle[i] + programs[j] + ".toString()").toString();

		System.out.println((evals[0].equals(evals[1]) && evals[2].equals(evals[3]) ? "" : "not ") + "equal");
		} catch (Exception e) { System.err.println(e); }
	}
}
