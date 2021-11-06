import java.util.*

fun main(args: Array<String>) = with(Scanner(System.`in`)) {
    val t = nextInt()
    val p = nextInt()
    val velocity = when {
        p >= 20 -> 1.0 * (100 - p) / t
        else -> 1.0 * (80 + (20 - p) * 2) / t
    }
    val timeLeft = Math.min(p, 20) / (velocity * 0.5) + Math.max(0, p - 20) / velocity
    println(timeLeft)
}