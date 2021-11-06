import kotlin.random.*

fun main(args: Array<String>) {
    val mode = args.getOrNull(0) ?: "ACPQSB"
    val n = args.getOrNull(1)?.toInt() ?: 100
    val seed = args.getOrNull(2)?.toLong() ?: mode.hashCode().toLong() + n * 239
    val rnd = Random(seed)
    check(canExpr(n, mode))
    println(genExpr(rnd, n, mode))
}

fun canExpr(n: Int, mode: String): Boolean = canTerm(n, mode) || canExpr2(n, mode)

fun canExpr2(n: Int, mode: String): Boolean =
    n >= 3 && 'A' in mode && (
        canExpr((n - 1) / 2, mode) && canExpr(n / 2, mode) ||
        n >= 5 && canExpr((n - 1) / 2 - 1, mode) && canExpr(n / 2 + 1, mode)
    )

fun genExpr(rnd: Random, n: Int, mode: String): String {
    if (canExpr2(n, mode) && (!canTerm(n, mode) || rnd.nextBoolean())) {
        while (true) {
            val k = rnd.nextInt(1..n - 2)
            if (!canExpr(k, mode) || !canExpr(n - k - 1, mode)) continue
            return buildString {
                append(genExpr(rnd, k, mode))
                append("|")
                append(genExpr(rnd, n - k - 1, mode))
            }
        }
    }
    return genTerm(rnd, n, mode)
}

fun canTerm(n: Int, mode: String): Boolean = canAtom(n, mode) || canTerm2(n, mode)

fun canTerm2(n: Int, mode: String): Boolean =
    n >= 2 && 'C' in mode && canTerm(n / 2, mode) && canTerm((n + 1) / 2, mode)

fun genTerm(rnd: Random, n: Int, mode: String): String {
    if (canTerm2(n, mode) && (!canAtom(n, mode) || rnd.nextBoolean())) {
        while (true) {
            val k = rnd.nextInt(1 until n)
            if (!canTerm(k, mode) || !canTerm(n - k, mode)) continue
            return buildString {
                append(genTerm(rnd, k, mode))
                append(genTerm(rnd, n - k, mode))
            }
        }
    }
    return genAtom(rnd, n, mode)
}

fun canAtom(n: Int, mode: String): Boolean =
    n == 1 || 'P' in mode || 'Q' in mode || 'S' in mode || (n >= 3 && 'B' in mode && canExpr(n - 2, mode))

fun genAtom(rnd: Random, n: Int, mode: String): String {
    if (n == 1) return ('A' + rnd.nextInt(26)).toString()
    while (true) {
        return when (rnd.nextInt(if (n >= 3) 4 else 3)) {
            0 -> {
                if ('P' !in mode) continue
                genAtom(rnd, n - 1, mode) + "+"
            }
            1 -> {
                if ('Q' !in mode) continue
                genAtom(rnd, n - 1, mode) + "?"
            }
            2 -> {
                if ('S' !in mode) continue
                genAtom(rnd, n - 1, mode) + "*"
            }
            3 -> {
                if ('B' !in mode) continue
                "(" + genExpr(rnd, n - 2, mode) + ")"
            }
            else -> error("!!")
        }
    }
}
