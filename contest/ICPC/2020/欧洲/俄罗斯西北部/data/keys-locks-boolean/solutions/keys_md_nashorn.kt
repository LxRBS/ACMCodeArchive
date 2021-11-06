import jdk.nashorn.api.scripting.NashornScriptEngineFactory
import kotlin.math.ceil
import kotlin.math.sqrt

fun main() {
	val f = readLine()!!.replace("and", "&&").replace("or", "||").replace("not", "!")
	val letters = f.filter { it in 'a'..'z' }.toSet().toList()
	val toEval = "[" + letters.subsets().joinToString(",") { subset ->
		f.map { when (it) {
			in subset -> "true"
			in letters -> "false"
			else -> it.toString()
		}}.joinToString("")
	} + "] + ''"
	val areFalse = letters.subsets().zip(eval(toEval).split(",")).filter { it.second != "true" }.map { it.first }
	val needed = mutableSetOf<List<Char>>()
	for (subset in areFalse) {
		needed.add(subset)
		val minusOne = subset.map { subset - it }
		if (!areFalse.containsAll(minusOne)) return println("IMPOSSIBLE")
		needed.removeAll(minusOne)
	}
	val width = letters.size + 3
	val columns = maxOf(1, ceil(sqrt(2.0 * needed.size / width)).toInt())
	val rows = needed.size / columns + 1
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
	needed.forEachIndexed { index, subset ->
		val c = index % columns
		val r = index / columns
		val wire = "+" + letters.joinToString("") { if (it in subset) "-" else it.toString() } + "+"
		for (i in wire.indices) {
			ans[2 * r + 2][c * width + i] = wire[i]
		}
	}
	println(ans.joinToString("\n") { it.joinToString("") })
}

private fun <E> List<E>.subsets(): List<List<E>> =
		if (this.isEmpty()) listOf(this) else drop(1).subsets() + drop(1).subsets().map { it + this[0] }
private fun eval(code: String) = NashornScriptEngineFactory().scriptEngine.eval(code).toString()
