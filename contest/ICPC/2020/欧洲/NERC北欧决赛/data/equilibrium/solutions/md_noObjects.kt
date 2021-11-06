import java.lang.StringBuilder
import kotlin.math.hypot
import java.util.*
import kotlin.math.abs
import kotlin.math.roundToLong
import kotlin.system.measureTimeMillis

//fun main(args: Array<String>) = CheckerFramework.main(args)
//fun main(args: Array<String>) = Tests().run(args)
//fun main() = solveIO(::solveFullSearch)
//fun main() = solveIO(::solveMemo)
fun main() = solveIO(::solveOptimized)
//fun main() = println("${measureTimeMillis { solveIO(::solveOptimized) }} ms")
//fun main() = repeat(7) { research(it + 1) }
//private val debuggedTest = "6 3.4 0.6".also { System.setIn(it.byteInputStream()) }
//private val debuggedTest = "30 30 10".also { System.setIn(it.byteInputStream()) }
//private val debuggedTest = "36 18.0735294118 2.3088235294".also { System.setIn(it.byteInputStream()) }

private const val allowedError = 1.1e-7
private const val allowedInputError = 0.9e-9
val setLocale = Locale.setDefault(Locale.US)

private fun solveMemo(n: Int, xDesired: Double, yDesired: Double): String {
	val (xd, yd) = toDiagonal(xDesired to yDesired)
	val dp = List(n) { List(n) { mutableMapOf<State, LinkedList>() } }
	val stateInit = State(0, 0, 0)
	dp[0][0][stateInit] = LinkedList(0, null)
	for (x in 0..n - 2) for (y in 0..x + 1) for (z in 0..y) {
		dp[x][z].forEach { (state, linkedList) ->
			val newState = State(state.mass + y, state.xMass2 + (2 * x + 3) * y, state.yMass2 + y * y)
			dp[x + 1][y][newState] = LinkedList(y, linkedList)
		}
	}
	val all = mutableMapOf<State, LinkedList?>()
	for (x in dp.last()) all.putAll(x)
	val answerEntry = all.entries.firstOrNull { (state, linkedList) ->
		val (xc, yc) = state.centerOfMassBrackets(n)
//		println("$state ${toList(linkedList)} $xc $yc")
		dist(xc, yc, xd, yd) < allowedError / 2
	} ?: error("No solution")
//	println("$n:\t${all.size} out of ${dp(n).last().sum()}")
	val answer = toList(answerEntry.value).reversed().toIntArray()
	return youngDiagramToBrackets(answer)
}

data class State(val mass: Int, val xMass2: Int, val yMass2: Int) {
	fun centerOfMassYoung() = if (mass == 0) 0.0 to 0.0 else xMass2 * 0.5 / mass to yMass2 * 0.5 / mass
	fun centerOfMassBrackets(n: Int): Pair<Double, Double> {
		val (xy, yy) = centerOfMassYoung()
		return centerOfMassBrackets(n, mass, xy, yy)
	}
}

private fun solveFullSearch(n: Int, xDesired: Double, yDesired: Double): String {
	val dp = dp(n)
	val count = dp.last().sum()
	for (index in 0 until count) {
		val nth = nth(index, dp)
		val (xc, yc) = toNonDiagonal(centerOfMassBrackets(nth))
		if (dist(xc, yc, xDesired, yDesired) < allowedError) return youngDiagramToBrackets(nth)
	}
	error("Solution not found")
}

private fun solveOptimized(n: Int, xDesired: Double, yDesired: Double): String {
	val den = 1e10.toLong()
	val err = (1e-8 * den).roundToLong()
	val xNum = (xDesired * den).roundToLong()
	val yNum = (3 * yDesired * den).roundToLong()
	val states = mutableListOf(mapOf(0L to 0L))
	for (i in 1..n) {
		val newStates = mutableMapOf<Long, Long>()
		for (j in 0 until i) {
			for (entryLeft in states[j]) {
				val massLeft = entryLeft.key and ((1 shl 16) - 1)
				val xMassLeft = (entryLeft.key shr 16) and ((1 shl 24) - 1)
				val yMassLeft = (entryLeft.key shr 40)
				for (entryRight in states[i - 1 - j]) {
					val massRight = entryRight.key and ((1 shl 16) - 1)
					val xMassRight = (entryRight.key shr 16) and ((1 shl 24) - 1)
					val yMassRight = (entryRight.key shr 40)
					val mass = 2 * j + 1 + massLeft + massRight
					val yMass = 3 * j + 1 + yMassLeft + massLeft * 3 + yMassRight
					val xMass = (j + 1) * (2 * j + 1) + xMassLeft + massLeft + xMassRight + massRight * (2 * j + 2)
					if (i == n) {
						if ((abs(xMass * den - xNum * mass) < err * mass) and (abs(yMass * den - yNum * mass) < err * mass)) {
							val sequence = (entryLeft.value shl 1) or (entryRight.value shl (2 * j + 2)) or (1L shl (2 * j + 1))
							return sequence.toString(2).reversed().replace('0', '(').replace('1', ')')
						}
						continue
					}
					val sequence = (entryLeft.value shl 1) or (entryRight.value shl (2 * j + 2)) or (1L shl (2 * j + 1))
					newStates[(yMass shl 40) or (xMass shl 16) or mass] = sequence
					//println("$i\t${xMass * 1.0 / mass} ${yMass / 3.0 / mass}")
				}
			}
		}
		states.add(newStates)
	}
	error("Solution not found")
}

private fun solveIO(solution: (Int, Double, Double) -> String) {
	val (nIn, xIn, yIn) = readStrings()
	println(solution.invoke(nIn.toInt() / 2, xIn.toDouble(), yIn.toDouble()))
}

private fun dp(n: Int): List<LongArray> {
	val dp = List(n) { LongArray(n) }
	dp[0][0] = 1
	for (x in 1 until n) for (y in 0..x) {
		dp[x][y] = dp[x - 1].take(y + 1).sum()
	}
	return dp
}

private fun nth(index: Long, dp: List<LongArray>): IntArray {
	var m = index
	val a = IntArray(dp.size)
	for (x in a.indices.reversed()) {
		while (dp[x][a[x]] <= m) {
			m -= dp[x][a[x]]
			a[x]++
		}
	}
	return a
}

private fun research(n: Int) {
	val dp = dp(n)
	val count = dp.last().sum()
	println(n)
	println(count)
	println(dp.joinToString { it.contentToString() })
	var sumXB = 0.0
	var sumYB = 0.0
	for (index in 0 until count) {
		val seq = nth(index, dp)
		val (xb, yb) = centerOfMassBrackets(seq)
		sumXB += xb
		sumYB += yb
		println("$index\t${seq.contentToString()}\t($xb, $yb)\t${xb + yb - n - 1}")
//		solveGreedy(n, xb, yb)
	}
	val avgB = sumXB / count to sumYB / count
	println("AvgB: $avgB ${toNonDiagonal(avgB)}")
}

private fun solveGreedy(n: Int, xb: Double, yb: Double) {
	val a = IntArray(n)
	while (true) {
		val (x, y) = centerOfMassBrackets(a)
		val distBefore = dist(x, y, xb, yb)
		var bestImprovement = 1e-9
		var bestI = mapOf<Int, Int>()
		fun check(list: Map<Int, Int>) {
			val (xNew, yNew) = centerOfMassBrackets(a)
			val distNew = dist(xNew, yNew, xb, yb)
			val improvement = distBefore - distNew
			if (improvement > bestImprovement) {
				bestImprovement = improvement
				bestI = list
			}
		}
		fun canIncrease(i: Int) = a[i] + 1 <= i && a[i] < a.getOrElse(i + 1) { n + 1 }
		fun canDecrease(i: Int) = i > 0 && a[i] > a[i - 1]
		for (i in a.indices) {
			if (canIncrease(i)) {
				a[i]++
				check(mapOf(i to 1))
				for (j in a.indices) {
					if (canIncrease(j)) {
						a[j]++
						check(mapOf(i to 1, j to 1))
						a[j]--
					}
					if (canDecrease(j)) {
						a[j]--
						check(mapOf(i to 1, j to -1))
						a[j]++
					}
				}
				a[i]--
			}
			if (canDecrease(i)) {
				a[i]--
				check(mapOf(i to - 1))
				a[i]++
			}
		}
		if (bestI.isEmpty()) break
		bestI.forEach { a[it.key] += it.value }
	}
	val (xc, yc) = centerOfMassBrackets(a)
	println("$xc $yc should be $xb $yb")
	if (dist(xc, yc, xb, yb) > 1e-9) {
		error(a.contentToString()) // solveGreedy(n, xb, yb)
	}
}

private fun centerOfMassYoungDiagram(a: IntArray): Pair<Double, Double> {
	val mass = a.indices.sumBy { a[it] }
	val xMass = a.indices.sumByDouble { (it + 0.5) * a[it] }
	val yMass = a.indices.sumByDouble { a[it] * 0.5 * a[it] }
	return if (mass == 0) a.size.toDouble() to 0.0 else xMass / mass to yMass / mass
}

private fun centerOfMassBrackets(a: IntArray): Pair<Double, Double> {
	val n = a.size
	val (xYoung, yYoung) = centerOfMassYoungDiagram(a)
	val mass = a.sum()
	return centerOfMassBrackets(n, mass, xYoung, yYoung)
}

private fun centerOfMassBrackets(n: Int, mass: Int, xYoung: Double, yYoung: Double): Pair<Double, Double> {
	val massTriangle = 0.5 * n * n
	val xm = n * 2.0 / 3 * massTriangle - xYoung * mass
	val ym = n * 1.0 / 3 * massTriangle - yYoung * mass
	val m = massTriangle - mass
	return xm / m to ym / m
}

private fun toNonDiagonal(coord: Pair<Double, Double>): Pair<Double, Double> {
	val (x, y) = coord
	return x + y to x - y
}

private fun toDiagonal(coord: Pair<Double, Double>): Pair<Double, Double> {
	val (x, y) = coord
	return (x + y) / 2 to (x - y) / 2
}

private fun youngDiagramToBrackets(a: IntArray): String {
	val sb = StringBuilder()
	for (i in a.indices) sb.append("(").append(")".repeat(a.getOrElse(i + 1) { a.size } - a[i]))
	return sb.toString()
}

private fun bracketsToYoungDiagram(brackets: String): IntArray {
	var x = 0
	var y = 0
	val a = IntArray(brackets.length / 2)
	for (c in brackets) {
		if (c == ')') y++ else a[x++] = y
	}
	return a
}

private fun centerOfMass(brackets: String): Pair<Double, Double> {
	return toNonDiagonal(centerOfMassBrackets(bracketsToYoungDiagram(brackets)))
}

private fun checkBracketSequence(brackets: String, n: Int): String? {
	if (brackets.length != 2 * n) return "Wrong length of sequence: ${brackets.length} instead of ${2 * n}"
	val invalidCharacters = brackets.replace("(", "").replace(")", "")
	if (invalidCharacters.isNotEmpty()) return "Invalid character #" + invalidCharacters[0].toInt()
	var balance = 0
	for (c in brackets) {
		balance += if (c == '(') 1 else -1
		if (balance < 0) return "Negative balance"
	}
	if (balance != 0) return "Non-zero balance $balance in the end"
	return null
}

data class LinkedList(val head: Int, val tail: LinkedList?)
private fun toList(linkedList: LinkedList?): List<Int> =
		linkedList?.let { listOf(it.head) + toList(it.tail) } ?: listOf()

private fun dist(x: Double, y: Double, x2: Double, y2: Double) = hypot(x - x2, y - y2)
private fun readLn() = readLine()!!
private fun readStrings() = readLn().split(" ")

private class Tests {
	private val testsList = """
	"""
	fun byIndex(x: List<String>) {
		val n = x[0].toInt()
		val index = x[1].toLong()
		val dp = dp(n)
		val nth = nth(index, dp)
		val (xc, yc) = toNonDiagonal(centerOfMassBrackets(nth))
		test(n, xc, yc)
	}

	private fun format(x: Double) = String.format("%.10f", x)

	private fun test(n: Int, xc: Double, yc: Double) {
		val xPrinted = format(xc)
		val yPrinted = format(yc)
		validateTest(n, xPrinted.toDouble(), yPrinted.toDouble())
		println("${2 * n} $xPrinted $yPrinted")
	}

	private fun validateTest(n: Int, xc: Double, yc: Double) {
		val solution = solveMemo(n, xc, yc)
		checkBracketSequence(solution, n)?.let { error(it) }
		val (x, y) = centerOfMass(solution)
		dist(x, y, xc, yc).takeIf { it > allowedInputError }?.let { error(it) }
	}

	private fun runAll() {
		for (s in testsList.trimIndent().split("\n")) {
			measureTimeMillis {
				run(s.split(" ").drop(1).dropLast(2).toTypedArray())
			}.also { println("$it ms") }
		}
	}

	fun run(args: Array<String>) {
		if (args.isEmpty()) return runAll()
		Tests::class.java.getMethod(args[0], List::class.java).invoke(Tests(), args.drop(1))
	}
}

//class Check : Checker {
//	override fun test(inf: InStream, ouf: InStream, ans: InStream): Outcome {
//		val n = inf.nextInt() / 2
//		val xDesired = inf.nextDouble()
//		val yDesired = inf.nextDouble()
//		val brackets = ouf.nextLine()
//		checkBracketSequence(brackets, n)?.let { return Outcome(Outcome.Type.WA, it) }
//		val (x, y) = centerOfMass(brackets)
//		val error = dist(x, y, xDesired, yDesired)
//		if (error > allowedError) return Outcome(Outcome.Type.WA, "Too far from desired point, distance=$error")
//		return Outcome(Outcome.Type.OK, "Right in place, distance=$error")
//	}
//}
