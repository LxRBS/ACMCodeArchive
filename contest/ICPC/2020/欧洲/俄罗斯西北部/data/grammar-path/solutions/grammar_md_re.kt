import java.math.BigInteger
import java.util.*

fun main() {
	val productions = List(readInt()) { val (lhs, rhs) = readLn().split(" -> "); lhs[0] to rhs }
	val productions1 = productions.filter { it.second.length == 1 }
	val productions2 = productions.filter { it.second.length == 2 }
	val (n, m, sIn, tIn) = readInts()
	val s = sIn - 1; val t = tIn - 1
	val label = List(n) { Array<Char?>(n) { null } }
	repeat(m) {
		val (uIn, vIn, x) = readStrings()
		val u = uIn.toInt() - 1; val v = vIn.toInt() - 1
		label[u][v] = x[0]
	}
	data class Reachable(val from: Int, val to: Int, val nonterminal: Char)
	val queue = TreeMap<BigInteger, MutableList<Reachable>>()
	val dist = mutableMapOf<Reachable, BigInteger>()
	fun register(reachable: Reachable, distance: BigInteger) {
		val prevDist = dist[reachable]
		if (prevDist != null && prevDist <= distance) return
		queue.computeIfAbsent(distance) { mutableListOf() }.add(reachable)
		dist[reachable] = distance
	}
	for (u in label.indices) for (v in label.indices) for (p in productions1) if (label[u][v] == p.second[0]) {
		val reachable = Reachable(u, v, p.first)
		register(reachable, 1.toBigInteger())
	}
	while (queue.isNotEmpty()) {
		val distance = queue.firstKey()
		val reachable = queue[distance]!!.pop()
		if (dist[reachable]!! < distance) continue
		if (queue[distance]!!.isEmpty()) queue.remove(distance)
		for (w in label.indices) for (p in productions2) {
			if (p.second[0] == reachable.nonterminal) {
				val r = Reachable(reachable.to, w, p.second[1])
				val rDistance = dist[r]
				if (rDistance != null) register(Reachable(reachable.from, w, p.first), distance + rDistance)
			}
			if (p.second[1] == reachable.nonterminal) {
				val r = Reachable(w, reachable.from, p.second[0])
				val rDistance = dist[r]
				if (rDistance != null) register(Reachable(w, reachable.to, p.first), distance + rDistance)
			}
		}
	}
	println(dist[Reachable(s, t, 'S')] ?: "NO")
}

private fun <T> MutableList<T>.pop() = removeAt(lastIndex)
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
