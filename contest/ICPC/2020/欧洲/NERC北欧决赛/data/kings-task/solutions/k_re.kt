fun main() {
    val n = readLine()!!.toInt()
    val p = readLine()!!.split(" ").map { it.toInt() }
    val sorted = p.sorted()
    var best = Int.MAX_VALUE
    for (i0 in 0..1) {
        val u = HashSet<List<Int>>()
        var c = p
        var cnt = 0
        while (true) {
            if (c == sorted) {
                best = minOf(best, cnt)
                break
            }
            if (!u.add(c)) break
            when ((i0 + cnt) % 2) {
                0 -> c = List(2  * n) { i -> c[i / 2 * 2 + (1 - i % 2)] }
                1 -> c = List(2  * n) { i -> c[i % n + (n - i / n * n)] }
            }
            cnt++
        }
    }
    if (best == Int.MAX_VALUE) {
        println(-1)
    } else {
        println(best)
    }
}