import kotlin.random.*

fun main() {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    val MAXW = 1 shl 20
    val w = IntArray(n) { MAXW }
    val rnd = Random(1)
    repeat(m) {
        val s = readLine()!!
        require(s.length == n)
        val x = rnd.nextInt(w.sum())
        var k = 0
        var cs = 0
        while (cs + w[k] <= x) {
            cs += w[k]
            k++
        }
        println(s[k])
        val sa = readLine()!![0]
        var sum = 0
        var max = 0
        for (i in 0 until n) {
            if (s[i] != sa) w[i] = (w[i] + 1) / 2
            sum += w[i]
            if (w[i] > max) max = w[i]
        }
        if (max < MAXW) {
            for (i in 0 until n) {
                w[i] *= 2
            }
        }
    }
}