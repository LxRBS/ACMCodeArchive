import jdk.nashorn.api.scripting.NashornScriptEngineFactory
import kotlin.math.ceil
import kotlin.math.sqrt

//(h and f and d and a and g) or (h and f and d and a and c) or (h and f and d and g and c) or (h and f and a and g and c) or (h and d and a and g and c) or (f and d and a and g and c) or (h and f and d and a and e) or (h and f and d and g and e) or (h and f and a and g and e) or (h and d and a and g and e) or (f and d and a and g and e) or (h and f and d and c and e) or (h and f and a and c and e) or (h and d and a and c and e) or (f and d and a and c and e) or (h and f and g and c and e) or (h and d and g and c and e) or (f and d and g and c and e) or (h and a and g and c and e) or (f and a and g and c and e) or (d and a and g and c and e) or (h and f and d and a and b) or (h and f and d and g and b) or (h and f and a and g and b) or (h and d and a and g and b) or (f and d and a and g and b) or (h and f and d and c and b) or (h and f and a and c and b) or (h and d and a and c and b) or (f and d and a and c and b) or (h and f and g and c and b) or (h and d and g and c and b) or (f and d and g and c and b) or (h and a and g and c and b) or (f and a and g and c and b) or (d and a and g and c and b) or (h and f and d and e and b) or (h and f and a and e and b) or (h and d and a and e and b) or (f and d and a and e and b) or (h and f and g and e and b) or (h and d and g and e and b) or (f and d and g and e and b) or (h and a and g and e and b) or (f and a and g and e and b) or (d and a and g and e and b) or (h and f and c and e and b) or (h and d and c and e and b) or (f and d and c and e and b) or (h and a and c and e and b) or (f and a and c and e and b) or (d and a and c and e and b) or (h and g and c and e and b) or (f and g and c and e and b) or (d and g and c and e and b) or (a and g and c and e and b)
fun main() {
	val f = readLine()!!.replace("and", "&&").replace("or", "||").replace("not", "!")
	val letters = f.filter { it in 'a'..'z' }.toSet().toList()
	val areFalse = mutableSetOf<List<Char>>()
	val needed = mutableSetOf<List<Char>>()
	for (subset in letters.subsets()) {
		val substituted = f.map { when (it) {
			in subset -> "true"
			in letters -> "false"
			else -> it.toString()
		}}.joinToString("")
		if (eval(substituted) == "true") continue
		needed.add(subset)
		val minusOne = subset.map { subset - it }
		if (!areFalse.containsAll(minusOne)) return println("IMPOSSIBLE")
		needed.removeAll(minusOne)
		areFalse.add(subset)
	}
	val wires = needed.map { subset -> "+" + letters.joinToString("") { if (it in subset) "-" else it.toString() } + "+" }
	val width = letters.size + 3
	val columns = maxOf(1, ceil(sqrt(2.0 * wires.size / width)).toInt())
	val rows = wires.size / columns + 1
	val ans = List(2 * rows + 3) { MutableList(columns * width - 1) { ' ' } }
	for (i in 0..(columns - 1) * width) {
		ans[0][i] = '-'
		ans[ans.lastIndex][i + letters.size + 1] = '-'
	}
	repeat (columns) { c ->
		for (i in 0..rows * 2) {
			val char = if (i == 0 || i == rows * 2) '+' else '|'
			ans[i][c * width] = char
			ans[i + 2][c * width + letters.size + 1] = char
		}
	}
	"+||".forEachIndexed { i, c -> ans[i][ans[i].lastIndex] = c }
	wires.forEachIndexed { index, wire ->
		val c = index % columns
		val r = index / columns
		for (i in wire.indices) {
			ans[2 * r + 2][c * width + i] = wire[i]
		}
	}
	println(ans.joinToString("\n") { it.joinToString("") })
}

private fun <E> List<E>.subsets(): List<List<E>> =
		if (this.isEmpty()) listOf(this) else drop(1).subsets() + drop(1).subsets().map { it + this[0] }
private fun eval(code: String) = NashornScriptEngineFactory().scriptEngine.eval(code).toString()
