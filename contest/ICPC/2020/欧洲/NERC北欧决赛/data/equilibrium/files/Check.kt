import kotlin.math.hypot

import ru.ifmo.testlib.*
import java.lang.StringBuilder

fun main(args: Array<String>) = CheckerFramework.main(args)
//fun main(args: Array<String>) = Tests().run(args)
//fun main() = solve()
//fun main() = repeat(7) { research(it + 1) }

const val allowedError = 1e-7

private fun dp(n: Int): List<IntArray> {
	val dp = List(n) { IntArray(n) }
	dp[0][0] = 1
	for (x in 1 until n) for (y in 0..x) {
		dp[x][y] = dp[x - 1].take(y + 1).sum()
	}
	return dp
}

private fun nth(index: Int, dp: List<IntArray>): IntArray {
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
	repeat(count) { index ->
		val seq = nth(index, dp)
		val (xc, yc) = centerOfMassYoungDiagram(seq)
		val (xb, yb) = centerOfMassBrackets(seq)
		sumXB += xb
		sumYB += yb
		println("$index\t${seq.contentToString()}\t($xb, $yb)\t${xb + yb - n - 1}")
		solveGreedy(n, xb, yb)
	}
	val avgB = sumXB / count to sumYB / count
	println("AvgB: $avgB ${toNonDiagonal(avgB)}")
}

fun solveGreedy(n: Int, xb: Double, yb: Double) {
	val a = IntArray(n)
	while (true) {
		val (x, y) = centerOfMassBrackets(a)
		val distBefore = dist(x, y, xb, yb)
		var bestImprovement = 1e-9
		var bestI = -1
		for (i in a.indices) {
			if (a[i] + 1 > i) continue
			if (i + 1 in a.indices && a[i] == a[i + 1]) continue
			a[i]++
			val (xNew, yNew) = centerOfMassBrackets(a)
			val distNew = dist(xNew, yNew, xb, yb)
			val improvement = distBefore - distNew
			if (improvement > bestImprovement) {
				bestImprovement = improvement
				bestI = i
			}
			a[i]--
		}
		if (bestI == -1) break
		a[bestI]++
	}
	val (xc, yc) = centerOfMassBrackets(a)
	println("$xc $yc should be $xb $yb")
	if (dist(xc, yc, xb, yb) > 1e-9) {
		solveGreedy(n, xb, yb)
	}
}

fun centerOfMassYoungDiagram(a: IntArray): Pair<Double, Double> {
	val mass = a.indices.sumBy { a[it] }
	val xMass = a.indices.sumByDouble { (it + 0.5) * a[it] }
	val yMass = a.indices.sumByDouble { a[it] * 0.5 * a[it] }
	return if (mass == 0) a.size.toDouble() to 0.0 else xMass / mass to yMass / mass
}

fun centerOfMassBrackets(a: IntArray): Pair<Double, Double> {
	val n = a.size
	val (xc, yc) = centerOfMassYoungDiagram(a)
	val mass = a.sum()
	val massTriangle = 0.5 * n * n
	val xm = n * 2.0 / 3 * massTriangle - xc * mass
	val ym = n * 1.0 / 3 * massTriangle - yc * mass
	val m = massTriangle - mass
	return xm / m to ym / m
}

fun toNonDiagonal(coord: Pair<Double, Double>): Pair<Double, Double> {
	val (x, y) = coord
	val xa = (x + y)
	val ya = (x - y)
	return xa to ya
}

fun youngDiagramToBrackets(a: IntArray): String {
	val sb = StringBuilder()
	for (i in a.indices) sb.append("(").append(")".repeat(a.getOrElse(i + 1) { a.size } - a[i]))
	return sb.toString()
}

fun bracketsToYoungDiagram(brackets: String): IntArray {
	var x = 0
	var y = 0
	val a = IntArray(brackets.length / 2)
	for (c in brackets) {
		if (c == ')') y++ else a[x++] = y
	}
	return a
}

private fun solve() {
	val (nIn, xIn, yIn) = readStrings()
	println(solve(nIn.toInt() / 2, xIn.toDouble(), yIn.toDouble()))
}

private fun solve(n: Int, xDesired: Double, yDesired: Double): String {
	val dp = dp(n)
	val count = dp.last().sum()
	repeat(count) { index ->
		val nth = nth(index, dp)
		val (xc, yc) = toNonDiagonal(centerOfMassBrackets(nth))
		if (dist(xc, yc, xDesired, yDesired) < allowedError) return youngDiagramToBrackets(nth)
	}
	error("Solution not found")
}

fun centerOfMass(brackets: String): Pair<Double, Double> {
	return toNonDiagonal(centerOfMassBrackets(bracketsToYoungDiagram(brackets)))
}

fun checkBracketSequence(brackets: String, n: Int): String? {
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

fun dist(x: Double, y: Double, x2: Double, y2: Double) = hypot(x - x2, y - y2)
private fun readLn() = readLine()!!
private fun readStrings() = readLn().split(" ")

class Check : Checker {
	override fun test(inf: InStream, ouf: InStream, ans: InStream): Outcome {
		val n = inf.nextInt() / 2
		val xDesired = inf.nextDouble()
		val yDesired = inf.nextDouble()
		val brackets = ouf.nextLine()
		checkBracketSequence(brackets, n)?.also { return Outcome(Outcome.Type.WA, it) }
		val (x, y) = centerOfMass(brackets)
		val error = dist(x, y, xDesired, yDesired)
		if (error > allowedError) return Outcome(Outcome.Type.WA, "Too far from desired point, distance=$error")
		return Outcome(Outcome.Type.OK, "Right in place, distance=$error")
	}
}
