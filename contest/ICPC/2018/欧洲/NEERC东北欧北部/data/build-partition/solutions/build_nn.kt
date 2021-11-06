import java.util.*

fun main(args: Array<String>) = with(Scanner(System.`in`)) {
    val n = nextInt()
    if (n == 2) {
        println(-1)
        return
    }
    val x = (n + 1) / 2
    println(x)
    for (i in 1..x) {
        for (j in 1..x) {
            if (n % 2 == 0 && i == x - 1 && j == 2) {
                print('o')
                continue
            }
            if (j == 1 || i == x) {
                print('o')
            } else {
                print('.')
            }
        }
        println()
    }
}
