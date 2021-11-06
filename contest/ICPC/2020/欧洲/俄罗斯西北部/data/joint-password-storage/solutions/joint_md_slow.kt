import java.lang.StringBuilder
import kotlin.experimental.xor
import kotlin.random.Random

fun solve(s: String, maxK: Int = 1000) {
	val random = Random(s.hashCode() + 56623930)
	val pool = mutableListOf<String>()
	while (pool.size < maxK) {
		val pLeft = random.nextDouble()
		val terms = List(2) { StringBuilder() }
		var diff = 0
		while (true) {
			val number = random.nextInt(16)
			val parentheses = listOf("  ", "()", "{}", "[]").random(random)
			val token = ("" + parentheses[0] + number + parentheses[1]).trim()
			val part = if (random.nextDouble() < pLeft) 0 else 1
			if (terms[part].isNotEmpty()) terms[part].append("+")
			terms[part].append(token)
			diff += (if (part == 0) 1 else -1) * number
			if (terms[0].length + terms[1].length + 5 < s.length) continue
			fun register(equation: String) {
				if (equation.length == s.length) pool.add(equation)
			}
			if (terms[0].length + terms[1].length > s.length) break
			if (terms[0].isEmpty()) {
				register("${-diff}=${terms[1]}")
				continue
			}
			if (terms[1].isEmpty()) {
				register("${terms[0]}=$diff")
				continue
			}
			val eq = if (diff >= 0) "=$diff+" else "+${-diff}="
			val extra = s.length - terms[0].length - terms[1].length - eq.length
			if (extra == 0)	register("${terms[0]}$eq${terms[1]}")
			if (extra == 2) {
				register("${terms[0]}$eq[${terms[1]}]")
				register("{${terms[0]}}$eq${terms[1]}")
			}
		}
	}
	solveGauss(s, pool)
}

fun toColumn(s: String) = s.flatMap { c -> (0..6).map { ((c.toInt() shr it) and 1).toByte() } }

fun solveGauss(s: String, pool: List<String>) {
	val aTransposed = pool.map { toColumn(it) }
	val a = List(aTransposed[0].size) { i -> aTransposed.map { it[i] }.toByteArray() }
	val b = toColumn(s).toByteArray()
	val ans = gauss(a, b)
	val selected = pool.filterIndexed { index, _ -> ans[index] == 1.toByte() }
	val test = s.map { 0.toChar() }.toMutableList()
	for (r in selected) for (i in test.indices) test[i] = (test[i].toInt() xor r[i].toInt()).toChar()
	if (test.joinToString("") != s) return println("NO") // ${test.joinToString("")} not $s")
	println("YES\n${selected.size}")
	println(selected.joinToString("\n"))
}

fun gauss(a: List<ByteArray>, b: ByteArray): ByteArray {
	val m = a.size
	val n: Int = a[0].size
	val pos = IntArray(m)
	loop@for (i in 0 until m) {
		var s = 0
		for (j in 1 until n) {
			if (a[i][j] != 0.toByte()) {
				s = j
				break
			}
		}
		if (a[i][s] == 0.toByte()) {
			pos[i] = -1
			continue
		}
		pos[i] = s
		for (k in 0 until m) {
			if (k == i || a[k][s] * a[i][s] == 0) continue
			for (j in 0 until n) a[k][j] = a[k][j].xor(a[i][j])
			b[k] = b[k].xor(b[i])
		}
	}
	val ans = ByteArray(n)
	for (i in 0 until m) {
		if (pos[i] == -1) continue
		ans[pos[i]] = b[i]
	}
	return ans
}

fun main() = repeat(readInt()) { solve(readLn()) }

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
