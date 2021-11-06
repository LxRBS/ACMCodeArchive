import jdk.nashorn.api.scripting.NashornScriptEngineFactory

fun main() {
	val f = readLine()!!.replace("and", "&&").replace("or", "||").replace("not", "!")
	val letters = f.filter { it in 'a'..'z' }.toSet().toList()
	val ans = mutableListOf("+" + " ".repeat(letters.size) + "+")
	val areFalse = mutableSetOf<List<Char>>()
	for (subset in letters.subsets()) {
		val substituted = f.map { when (it) {
			in subset -> "true"
			in letters -> "false"
			else -> it.toString()
		}}.joinToString("")
		if (eval(substituted) == "true") continue
		if (subset.any { subset - it !in areFalse }) return println("IMPOSSIBLE")
		areFalse.add(subset)
		ans.add("|" + " ".repeat(letters.size) + "|")
		ans.add("+" + letters.joinToString("") { if (it in subset) "-" else it.toString() } + "+")
	}
	println(ans.joinToString("\n"))
}

private fun <E> List<E>.subsets(): List<List<E>> =
		if (this.isEmpty()) listOf(this) else drop(1).subsets() + drop(1).subsets().map { it + this[0] }

private fun eval(code: String) = NashornScriptEngineFactory().scriptEngine.eval(code).toString()
