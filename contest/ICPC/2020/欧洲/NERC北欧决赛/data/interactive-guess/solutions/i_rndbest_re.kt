import kotlin.random.*

fun main() {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    val a = IntArray(n) { 1 }
    val rnd = Random(1)
    repeat(m) {
        val s = readLine()!!
        require(s.length == n)
        val max = a.maxOrNull()!!
        val k = a.asSequence().withIndex().filter { it.value == max }.toList().random(rnd).index
        println(s[k])
        val sa = readLine()!![0]
        for (i in 0 until n) {
            if (s[i] == sa) {
                a[i]++
            }
        }
    }
}