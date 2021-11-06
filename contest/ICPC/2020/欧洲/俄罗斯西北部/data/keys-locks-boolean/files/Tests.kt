import kotlin.random.Random

const val testsDraft = """
Tests veryNested > $
Tests veryNestedNonTrivial > $
Tests randomMonotoneNF 3 9 1 8 > $
Tests randomMonotoneNF 3 9 3 6 > $
Tests randomMonotoneNF 8 100 3 6 > $
Tests randomMonotoneNF 8 80 1 8 > $
Tests randomMonotoneNF 8 150 1 5 > $
Tests randomMonotoneNF 8 500 6 7 > $
Tests randomMonotoneNested 8 50 > $
Tests randomMonotoneNested 7 999 > $
Tests randomMonotoneNested 8 2020 > $
Tests randomMonotoneNested 1 2020 > $
Tests linearThreshold 3 50 100 > $
Tests linearThreshold 4 50 100 > $
Tests linearThreshold 5 70 100 > $
Tests linearThreshold 6 20 100 > $
Tests linearThreshold 7 80 100 > $
Tests linearThreshold 8 70 100 > $
Tests linearThreshold 8 40 50 > $
Tests linearThreshold 6 10 40 > $
Tests popCountFull 3 1 0 > $
Tests popCountFull 3 2 0 > $
Tests popCountFull 3 3 1 > $
Tests popCountFull 7 5 0 > $
Tests popCountFull 7 5 1 > $
Tests popCountFull 8 7 1 > $
Tests popCount 4 2 0 > $
Tests popCount 4 3 1 > $
Tests popCount 8 1 0 > $
Tests popCount 8 2 0 > $
Tests popCount 8 3 0 > $
Tests popCount 8 3 1 > $
Tests popCount 8 4 0 > $
Tests popCount 8 4 1 > $
Tests popCount 8 5 0 > $
Tests popCount 8 5 1 > $
Tests popCount 8 6 0 > $
Tests popCount 8 6 1 > $
Tests popCount 8 7 0 > $
Tests popCount 8 7 1 > $
Tests popCount 8 8 0 > $
Tests popCount 8 8 1 > $
"""
const val MAX_LENGTH = 2020
const val MAX_LETTERS = 8
val LETTERS = ('a'..'z').take(MAX_LETTERS)
val operations = listOf(" and ", " or ")

@Suppress("unused")
class Tests {
	val random = Random(56623930_22304985)

	fun veryNested(@Suppress("UNUSED_PARAMETER") x: List<String>) {
		val m = (MAX_LENGTH - 1) / 2
		println("(".repeat(m) + "a" + ")".repeat(m))
	}

	fun veryNestedNonTrivial(@Suppress("UNUSED_PARAMETER") x: List<String>) {
		val m = (MAX_LENGTH - 16) / 2
		println("(".repeat(m) + "a or b" + ")".repeat(m) + " and c")
	}

	fun randomMonotoneNF(x: List<String>) {
		val (n, m, sizeLow, sizeHigh) = x.map { it.toInt() }
		val letters = LETTERS.shuffled(random).take(n)
		val clauses = List(m) { letters.filter { random.nextBoolean() } }.filter { it.size in sizeLow until sizeHigh }
		val ops = operations.shuffled(random)
		val test = clauses.joinToString(ops[0]) { "(" + it.joinToString(ops[1]) + ")" }
		println(test)
	}

	fun randomMonotoneNested(x: List<String>) {
		val (n, m) = x.map { it.toInt() }
		val letters = LETTERS.shuffled(random).take(n)
		fun generate(m: Int): String {
			if (m < 7) return letters.random(random).toString()
			val terms = List(2) { generate((m - 3) / 2) }
			return "(" + terms[0] + operations.random(random) + terms[1] + ")"
		}
		println(generate(m))
	}

	fun linearThreshold(x: List<String>) {
		val (n, low, high) = x.map { it.toInt() }
		val letters = LETTERS.shuffled(random).take(n)
		val coef = letters.associateWith { random.nextDouble() }
		val thresholdLow = low * coef.values.sum() / 100.0
		val thresholdHigh = high * coef.values.sum() / 100.0
		val subsets = letters.subsets().filter { subset ->
			coef.filter { it.key in subset }.values.sum() in thresholdLow..thresholdHigh && subset.isNotEmpty()
		}
		val test = subsets.joinToString(" or ") { "(" + it.joinToString(" and ") + ")" }
		println(test)
	}

	fun popCountFull(x: List<String>) {
		val (n, m, doTrash) = x.map { it.toInt() }
		val letters = LETTERS.shuffled(random).take(n)
		val subsets = letters.subsets().filter { it.size >= m }.toMutableList()
		if (doTrash > 0) subsets.add(letters.subsets().shuffled(random).first { it.size == m - 2 })
		val test = subsets.joinToString(" or ") { subset ->
			"(" + letters.joinToString(" and ") { (if (it in subset) "" else "not ") + it } + ")"
		}
		println(test)
	}

	fun popCount(x: List<String>) {
		val (n, m, doTrash) = x.map { it.toInt() }
		val letters = LETTERS.shuffled(random).take(n)
		val subsets = letters.subsets().filter { it.size == m }.toMutableList()
		var test = subsets.joinToString(" or ") { "(" + it.joinToString(" and ") + ")" }
		if (doTrash > 0) {
			val subset = letters.subsets().shuffled(random).first { it.size == m - 2 }
			test = "(" + letters.joinToString(" and ") { (if (it in subset) "" else "not ") + it } + ") or $test"
		}
		println(test)
	}
}

private fun <E> List<E>.subsets(): List<List<E>> =
		if (this.isEmpty()) listOf(this) else drop(1).subsets() + drop(1).subsets().map { it + this[0] }

fun main(args: Array<String>) {
	if (args.isEmpty()) {
		for (s in testsDraft.trimIndent().split("\n")) main(s.split(" ").drop(1).dropLast(2).toTypedArray())
		return
	}
	Tests::class.java.getMethod(args[0], List::class.java).invoke(Tests(), args.drop(1))
}
