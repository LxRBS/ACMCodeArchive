import java.math.BigInteger
import java.util.*
import kotlin.math.exp
import kotlin.random.Random

fun main() {
	val random = Random(56623930_349786239)
	val n = 26
	val m = 10
	val nonterminals = (('S'..'Z') + ('A' until 'S')).take(26)
	val terminals = ('a'..'z').take(nonterminals.size)
	val p1 = nonterminals.drop(1).zip(terminals) { a, b -> a to "" + b }
	val p = 100 - p1.size
	val e = List(m) { Array<Char?>(m) { 'a' } }
	val pLeft = MutableList(p) { 'S' }
	val pRight = MutableList(p) { "a" }

	fun eval(): BigInteger = solve(pLeft.zip(pRight) { a, b -> a to b } + p1, e, 0, 1) ?: (-1).toBigInteger()
	fun output() {
		println(p + p1.size)
		println((pLeft.zip(pRight) + p1).joinToString("\n") { "${it.first} -> ${it.second}" })
		println("$n ${n * n} 1 2")
		for (i in 0 until n) for (j in 0 until n) println("${i + 1} ${j + 1} ${e[i % m][j % m]}")
	}
	fun randomInstance() {
		for (i in pLeft.indices) {
			pLeft[i] = nonterminals.random(random)
			pRight[i] = "" + nonterminals.random(random) + nonterminals.random(random)
		}
		for (i in e.indices) for (j in e.indices) {
			e[i][j] = if (i >= m || j >= m) terminals[(i + j) % terminals.size] else terminals.random(random)
		}
	}
	var typeLast = 0
	var iLast = 0
	var jLast = 0
	var cLast: Char? = 'a'
	var lhsLast = 'a'
	var rhsLast = "AA"
	fun vary() {
		typeLast = random.nextInt(2)
		if (typeLast == 0) {
			iLast = (0 until m).random(random)
			jLast = (0 until m).random(random)
			cLast = e[iLast][jLast]
			e[iLast][jLast] = terminals.random(random)
		} else {
			iLast = pLeft.indices.random(random)
			lhsLast = pLeft[iLast]
			rhsLast = pRight[iLast]
			pLeft[iLast] = nonterminals.random(random)
			pRight[iLast] = "" + nonterminals.random(random) + nonterminals.random(random)
		}
	}
	fun undo() {
		if (typeLast == 0) {
			e[iLast][jLast] = cLast
		} else {
			pLeft[iLast] = lhsLast
			pRight[iLast] = rhsLast
		}
	}

	var best = 10.toBigInteger()
	if (false) while (true) {
		randomInstance()
		val eval = eval()
		if (eval <= best) continue
		output()
		println(eval)
		best = eval
	}

	val settings = Settings()
	val stepBack = true
	var energy = eval()
	var answerEnergy = 0.toBigInteger()
	randomInstance()
	for (glob in 0 until settings.globalIterations) {
		if (glob > 0 && random.nextDouble() >= settings.probStartWithPrevious) {
			randomInstance()
			energy = eval()
		}
		var end = settings.iterations
		var iter = 1
		var recession = 0
		while (true) {
//			println("$energy $iter")
			if (energy > answerEnergy) {
				answerEnergy = energy
				output()
				println(answerEnergy)
				end = end.coerceAtLeast(iter + settings.iterations)
			}
			if (iter > end) {
				break
			}
			vary()
			val nextEnergy = eval()
			val dEnergy = energy - nextEnergy
			var accept: Boolean
			if (dEnergy < 0.toBigInteger()) {
				accept = true
				recession = 0
			} else {
				recession++
				if (recession == settings.recessionLimit) {
					break
				}
				val barrier = exp(-1.0 * dEnergy.toDouble() * iter / settings.temp0)
				accept = random.nextDouble() < barrier
			}
			if (accept) {
				energy = nextEnergy
			} else {
				if (stepBack) {
					undo()
				}
			}
			iter++
		}
	}
}

class Settings @JvmOverloads constructor(var globalIterations: Int = 1 shl 20, var iterations: Int = 1 shl 17, var probStartWithPrevious: Double = 1 - 1.0 / 1600, var recessionLimit: Int = Int.MAX_VALUE, var temp0: Double = 1.0)

private fun solve(productions: List<Pair<Char, String>>, label: List<Array<Char?>>, s: Int, t: Int): BigInteger? {
	val (productions1, productions2) = (1..2).map { len -> productions.filter { it.second.length == len } }
	val queue = TreeMap<BigInteger, MutableList<Reachable>>()
	val dist = mutableMapOf<Reachable, BigInteger>()
	fun register(reachable: Reachable, distance: BigInteger) {
		val prevDist = dist[reachable]
		if (prevDist != null && prevDist <= distance) return
		queue.computeIfAbsent(distance) { mutableListOf() }.add(reachable)
		dist[reachable] = distance
	}
	for (u in label.indices) for (v in label.indices) for (p in productions1) if (label[u][v] == p.second[0]) {
		register(Reachable(u, v, p.first), 1.toBigInteger())
	}
	while (queue.isNotEmpty()) {
		val distance = queue.firstKey()
		val reachable = queue[distance]!!.pop()
		if (queue[distance]!!.isEmpty()) queue.remove(distance)
		if (dist[reachable]!! < distance) continue
		fun relax(other: Reachable, sum: Reachable) {
			register(sum, distance + (dist[other] ?: return))
		}
		for (w in label.indices) for (p in productions2) {
			if (p.second[0] == reachable.symbol) relax(Reachable(reachable.to, w, p.second[1]), Reachable(reachable.from, w, p.first))
			if (p.second[1] == reachable.symbol) relax(Reachable(w, reachable.from, p.second[0]), Reachable(w, reachable.to, p.first))
		}
	}
	return dist[Reachable(s, t, 'S')]
}

private data class Reachable(val from: Int, val to: Int, val symbol: Char)
private fun <T> MutableList<T>.pop() = removeAt(lastIndex)
