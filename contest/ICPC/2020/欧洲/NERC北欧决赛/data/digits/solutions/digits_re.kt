fun main() {
    val (n, d) = readLine()!!.split(" ").map { it.toInt() }
    val a = readLine()!!.split(" ").map { it.toInt() }.toList()
    val b = solveDigits(d, a)
    if (b == null || b.isEmpty()) {
        println(-1)
    } else {
        println(b.size)
        println(b.joinToString(" "))
    }
}

object DT {
    val ds = listOf(1, 2, 3, 4, 6, 7, 8, 9)
    val odd: Array<IntArray> = Array(10) { IntArray(10) }
    val even: Array<IntArray> = Array(10) { IntArray(10) }
    init {
        for (x in ds) {
            for (y in ds) {
                val z = (x * y) % 10
                if (y % 2 == 0) even[z][x] = y else odd[z][x] = y
            }
        }
    }
}

fun solveDigits(d: Int, a: List<Int>): List<Int>? = when {
    d == 0 -> if (a.any { it % 10 == 2 } && a.any { it % 10 == 5 } || a.any { it % 10 == 0 }) a else null
    d == 5 -> if (a.any { it % 10 == 5 }) a.filter { it % 2 != 0 } else null
    else -> {
        val even = d % 2 == 0
        val b = a.filter { (if (even) (it % 10 != 0) else (it % 2 != 0)) && it % 10 != 5 }
        val p = b.fold(1) { x, y -> (x * y) % 10 }
        findNumbers(p, d, b, if (even) DT.even else DT.odd) { c ->
            !even || c.any { it % 2 == 0 }
        }
    }
}

fun findNumbers(p: Int, d: Int, b: List<Int>, dt: Array<IntArray>, isValid: (List<Int>) -> Boolean): List<Int>? {
    if (p == d) return b
    var best = Int.MAX_VALUE
    var ans: List<Int>? = null
    val maxNums = 3
    val md = DT.ds.associateWith { d0 ->
        b.filter { it % 10 == d0 }.sorted().take(maxNums)
    }
    val used = DT.ds.associateWith { 0 }.toMutableMap()
    fun scan(ns: Int, rem: Int, prod: Int, prev: List<Int>) {
        for (d1 in DT.ds) {
            val n1 = md[d1]?.getOrNull(used[d1]!!) ?: continue
            val r1 = dt[rem][d1].takeIf { it != 0 } ?: continue
            val p1 = prod * n1
            if (r1 == d && p1 < best) {
                val c = b.toMutableList().apply {
                    remove(n1)
                    for (n2 in prev) remove(n2)
                }
                if (isValid(c)) {
                    best = p1
                    ans = c
                }
            }
            if (ns > 1) {
                used[d1] = used[d1]!! + 1
                scan(ns - 1, r1, p1, prev + n1)
                used[d1] = used[d1]!! - 1
            }
        }
    }
    scan(maxNums, p, 1, emptyList())
    return ans
}