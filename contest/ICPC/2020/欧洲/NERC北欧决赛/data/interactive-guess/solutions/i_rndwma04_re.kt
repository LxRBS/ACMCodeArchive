import kotlin.random.*

fun main() {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    val w = DoubleArray(n) { 1.0 / n }
    val beta = 0.4
    val rnd = Random(1)
    repeat(m) {
        val s = readLine()!!
        require(s.length == n)
        val x = rnd.nextDouble()
        var k = 0
        var cs = 0.0
        while (cs + w[k] < x) {
            cs += w[k]
            k++
        }
        println(s[k])
        val sa = readLine()!![0]
        var sum = 0.0
        for (i in 0 until n) {
            if (s[i] != sa) w[i] *= beta
            sum += w[i]
        }
        val scale = 1 / sum
        for (i in 0 until n) {
            w[i] *= scale
        }
    }
}