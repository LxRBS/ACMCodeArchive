import kotlin.math.*

const val DEBUG_SHAPE = false

fun main() {
    val (n, len) = readLine()!!.split(" ").map { it.toInt() }
    val original = Array(n) {
        val (x, y) = readLine()!!.split(" ").map { it.toInt() }
        Pt(x.toDouble(), y.toDouble())
    }
    val center = Pt(original.sumOf { it.x } / n, original.sumOf { it.y } / n)
    val p = original.map { it - center }
    val perimeter = (0 until n).sumOf { i -> dist(p[(i + 1) % n], p[i]) }
    val dl = len - perimeter
    val x0 = findX0(n, dl, p)
    if (DEBUG_SHAPE) println("${x0.ia} ${x0.ib} -> ${x0.p + center}")
    val start = findNext(n, p, x0)
    var cur = start
    var ans = 0.0
    var cnt = 0
    do {
        if (DEBUG_SHAPE) println("${cur.ia} ${cur.ib} -> ${cur.p + center}")
        val (_, ia, ib, dab) = cur
        val a = p[ia]
        val b = p[ib]
        val c = Pt((a.x + b.x) / 2, (a.y + b.y) / 2)
        val ab = dist(a, b)
        val v = b - a
        val u = v / ab
        val d = Pt(u.y, -u.x) * (sqrt(dab * dab - ab * ab) / 2)
        val e = u * (dab / 2)
        val next = findNext(n, p, cur)
        val w0 = angle(c, d, e, cur.p)
        val w1 = angle(c, d, e, next.p)
        ans += (det(c, e) * (sin(w1) - sin(w0)) + det(c, d) * (cos(w1) - cos(w0)) + det(d, e) * (w1 - w0)) / 2
        cur = next
    } while (dist(cur.p, start.p) > eps)
    println(ans)
}

const val eps = 1e-7

data class Pt(val x: Double, val y: Double)
operator fun Pt.plus(q: Pt) = Pt(x + q.x, y + q.y)
operator fun Pt.minus(q: Pt) = Pt(x - q.x, y - q.y)
operator fun Pt.div(a: Double) = Pt(x / a, y / a)
operator fun Pt.times(a: Double) = Pt(x * a, y * a)
operator fun Pt.times(q: Pt) = x * q.x + y * q.y
fun norm(x: Double, y: Double) = sqrt(x * x + y * y)
fun Pt.norm() = norm(x, y)
fun dist(a: Pt, b: Pt) = norm(a.x - b.x, a.y - b.y)
fun det(a: Pt, b: Pt) = a.x * b.y - a.y * b.x

data class Pos(val p: Pt, val ia: Int, val ib: Int, val dab: Double)

fun findX0(n: Int, dl: Double, p: List<Pt>): Pos {
    var l = 0.0
    for (i in 0 until n) {
        val a = p[i]
        val b = p[(i + 1) % n]
        if (a.y * b.y <= 0) {
            val x0 = a.x + (b.x - a.x) * a.y / (a.y - b.y)
            l = max(l, x0)
        }
    }
    var r = 1e6
    val ip = p.withIndex().toList()
    while (true) {
        val m = (r + l) / 2
        val mp = Pt(m, 0.0)
        val (ia, a) = ip.minByOrNull { it.value.y / dist(it.value, mp) }!!
        val (ib, b) = ip.maxByOrNull { it.value.y / dist(it.value, mp) }!!
        var dab = dl
        var j = ia
        do {
            val k = (j + 1) % n
            dab += dist(p[j], p[k])
            j = k
        } while (j != ib)
        if (r - l < eps) return Pos(Pt(m, 0.0), ia, ib, dab)
        val dm = dist(a, mp) + dist(b, mp)
        if (dm < dab) {
            l = m
        } else {
            r = m
        }
    }
}

fun findNext(n: Int, p: List<Pt>, q: Pos): Pos {
    val (cur, ia, ib, dab) = q
    val a = p[ia]
    val b = p[ib]
    val v = b - a
    val ab = dist(a, b)
    val d2 = dab * dab - ab * ab
    val g = p[(ia + 1) % n]
    var nextca = -1.0
    var next = cur
    var nia = ia
    var nib = ib
    var ndab = dab
    if (g != b) {
        val ag = dist(a, g)
        val abcosg = (g - a) * v / ag
        val t = d2 / (2 * (dab - abcosg))
        val g1 = a + (g - a) * (t / ag)
        if (det(cur, g1) > eps) {
            val ca = cur * g1 / cur.norm() / g1.norm()
            nextca = ca
            next = g1
            nia = (ia + 1) % n
            ndab = dab - ag
        }
    }
    val h = p[(ib + 1) % n]
    val bh = dist(b, h)
    val abcosh = (h - b) * v / bh
    val t = d2 / (2 * (dab - abcosh))
    val h1 = b + (b - h) * (t / bh)
    if (det(cur, h1) > eps) {
        val ca = cur * h1 / cur.norm() / h1.norm()
        if (ca > nextca) {
            next = h1
            nia = ia
            nib = (ib + 1) % n
            ndab = dab + bh
        }
    }
    return Pos(next, nia, nib, ndab)
}

// r = c + d * cos(w) + e * sin(w)
fun angle(c: Pt, d: Pt, e: Pt, p: Pt): Double {
    val f = p - c
    val cos = det(f, e)
    val sin = det(d, f)
    return atan2(sin, cos)
}

