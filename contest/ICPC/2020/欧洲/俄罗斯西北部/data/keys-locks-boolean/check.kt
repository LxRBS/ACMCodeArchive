import jdk.nashorn.api.scripting.NashornScriptEngineFactory
import ru.ifmo.testlib.*

val heightRange = 1..50
val widthRange = 2..50

class Check : Checker {
	override fun test(inf: InStream, ouf: InStream, ans: InStream): Outcome {
		val f = inf.nextLine().replace("and", "&&").replace("or", "||").replace("not", "!")
		val ja = parseAnswer(f, ans)
		val pa = parseAnswer(f, ouf)
		if (ja == pa) return Outcome(Outcome.Type.OK, if (pa) "Correct system" else "Impossible indeed")
		if (pa) return Outcome(Outcome.Type.FAIL, "Participant found answer while jury didn't")
		return Outcome(Outcome.Type.WA, "Participant didn't found answer while jury did")
	}

	private fun parseAnswer(f: String, ouf: InStream): Boolean {
		val letters = f.filter { it in 'a'..'z' }.toSet().toList()
		val lines = generateSequence { if (ouf.isEoF) null else ouf.nextLine() }.toList()
		val height = lines.size
		if (height == 1 && lines[0] == "IMPOSSIBLE") return false
		if (height !in heightRange) throw ouf.quit(Outcome.Type.WA, "Height $height not in $heightRange")
		val width = lines[0].length
		val badLine = lines.indexOfFirst { it.length != width }
		if (badLine != -1) ouf.quit(Outcome.Type.WA, "Lines 0 and $badLine of different length")
		if (width !in widthRange) throw ouf.quit(Outcome.Type.WA, "Width $width not in $widthRange")
		if (!lines[0].startsWith("+") || !lines[0].endsWith("+")) throw ouf.quit(Outcome.Type.WA, "Invalid corners")
		val badChars = lines.joinToString("").toSet() - "+-| ".toSet() - letters
		if (badChars.isNotEmpty()) throw ouf.quit(Outcome.Type.WA, "Bad chars found: $badChars")
		
		for (x in 0 until height) {
		    for (y in 0 until width) {
		        if (lines[x][y] == ' ' || lines[x][y] in letters) continue;
		        val haveL = y != 0 && lines[x][y - 1] != ' '
		        val haveR = y != width - 1 && lines[x][y + 1] != ' '
		        val haveU = x != 0 && lines[x - 1][y] != ' '
		        val haveD = x != height - 1 && lines[x + 1][y] != ' '
		        var expected = when {
		            haveL && haveR && !haveU && !haveD -> '-'
		            !haveL && !haveR && haveU && haveD -> '|'
		            else -> '+'
		        }
		        if (lines[x][y] != expected) {
		            throw ouf.quit(Outcome.Type.WA, "(${x+1}, ${y+1}) should be ${expected}, but ${lines[x][y]} found");
		        }
		    }
		}

		for (subset in letters.subsets()) {
			val mark = List(height) { BooleanArray(width) }
			fun dfs(x: Int, y: Int) {
				mark[x][y] = true
				for (d in 0 until 4) {
					val xx = x + DX[d]; val yy = y + DY[d]
					if (xx !in 0 until height || yy !in 0 until width) continue
					val cell = lines[xx][yy]
					if (mark[xx][yy] || cell == ' ' || cell in subset) continue
					dfs(xx, yy)
				}
			}
			dfs(0, 0)
			val open = !mark[0].last()

			val substituted = f.map { when (it) {
				in subset -> "true"
				in letters -> "false"
				else -> it.toString()
			}}.joinToString("")
			val shouldBeOpen = eval(substituted).toBoolean()

			if (open != shouldBeOpen) throw ouf.quit(Outcome.Type.WA,
					"Should be ${if (shouldBeOpen) "open" else "closed"} for people $subset")
		}
		return true
	}
}

val DX = intArrayOf(1, 0, -1, 0)
val DY = intArrayOf(0, 1, 0, -1)

private fun <E> List<E>.subsets(): List<List<E>> =
		if (this.isEmpty()) listOf(this) else drop(1).subsets() + drop(1).subsets().map { it + this[0] }
private fun eval(code: String) = NashornScriptEngineFactory().scriptEngine.eval(code).toString()
fun main(args: Array<String>) = CheckerFramework.main(args)
