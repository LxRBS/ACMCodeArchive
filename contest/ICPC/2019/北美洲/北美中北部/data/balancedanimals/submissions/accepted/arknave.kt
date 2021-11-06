import java.io.*
import java.util.*

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()

const val MAXW: Int = 20001

fun main(args: Array<String>) {
    val n = readInt()
    val a = IntArray(n)
    for (i in 0 until n) {
        a[i] = readInt()
    }

    val freq = IntArray(MAXW) { 0 }
    for (x in a) {
        freq[x] += x
    }

    for (i in 1 until MAXW) {
        freq[i] += freq[i - 1]
    }

    for (i in 1 until MAXW) {
        val before = freq[i - 1]
        val after = freq[MAXW - 1] - freq[i]
        if (before == after) {
            println(i)
            break
        }
    }
}
