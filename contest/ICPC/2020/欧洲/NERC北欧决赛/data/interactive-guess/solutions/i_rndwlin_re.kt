import kotlin.random.*

fun main() {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    val a = IntArray(n) { 1 }
    var sum = n
    val rnd = Random(1)
    repeat(m) {
        val s = readLine()!!
        require(s.length == n)
        val x = rnd.nextInt(sum)
        var k = 0
        var cs = 0
        while (cs + a[k] <= x) {
            cs += a[k]
            k++
        }
        println(s[k])
        val sa = readLine()!![0]
        for (i in 0 until n) {
            if (s[i] == sa) {
                a[i]++
                sum++
            }
        }
    }
}