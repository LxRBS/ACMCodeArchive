import java.util.*

val MAXN = 200001
val MAXP = 500
val MOD = 998244353

fun main(args: Array<String>) = with(Scanner(System.`in`)) {
    val partitions = Array(MAXN) { IntArray(MAXP) }
    partitions[0].fill(1)
    for (i in 1 until MAXN) {
        val cur = partitions[i]
        for (j in 1 until MAXP) {
            cur[j] = cur[j - 1]
            if (i - j >= 0) {
                cur[j] += partitions[i - j][j]
                if (cur[j] >= MOD) cur[j] -= MOD
            }
        }
    }
    val t = nextInt()
    (1..t).forEach {
        val n = nextInt()
        var ans = 0
        for (x in 1..n) {
            if (x * x > n) break
            val left = n - x * x
            if (left % 2 == 1) continue
            val add = partitions[left / 2][x]
            ans += add
            if (ans >= MOD) ans -= MOD
        }
        println(ans)
    }
}
